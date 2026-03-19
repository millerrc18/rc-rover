#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

namespace config {
constexpr int PIN_LEFT_PWM = 25;
constexpr int PIN_LEFT_DIR = 26;
constexpr int PIN_RIGHT_PWM = 27;
constexpr int PIN_RIGHT_DIR = 14;
constexpr int PIN_BATTERY_ADC = 34;

constexpr int PWM_CHANNEL_LEFT = 0;
constexpr int PWM_CHANNEL_RIGHT = 1;
constexpr int PWM_FREQUENCY_HZ = 18000;
constexpr int PWM_RESOLUTION_BITS = 8;
constexpr int PWM_MAX = (1 << PWM_RESOLUTION_BITS) - 1;
constexpr int PWM_FLOOR = 0;
constexpr float TURN_SCALING = 1.0f;
constexpr float FUTURE_RAMP_LIMIT_PER_SEC = 99.0f;  // Placeholder for Stage 1 tuning.

constexpr uint32_t DEADMAN_TIMEOUT_MS = 300;
constexpr uint32_t SERIAL_TELEMETRY_MS = 500;
constexpr uint32_t ADC_SAMPLE_MS = 100;

constexpr float ADC_REFERENCE_V = 3.3f;
constexpr float ADC_MAX_COUNTS = 4095.0f;
constexpr float BATTERY_DIVIDER_RATIO = 3.2f;  // R1=22kΩ / R2=10kΩ as built (20kΩ was specified; 22kΩ substituted)
constexpr float BATTERY_CALIBRATION = 1.0f;

constexpr char BLE_DEVICE_NAME[] = "rc-rover-stage1";
constexpr char BLE_SERVICE_UUID[] = "f0001000-0451-4000-b000-000000000000";
constexpr char BLE_COMMAND_CHAR_UUID[] = "f0001001-0451-4000-b000-000000000000";
constexpr char BLE_STATUS_CHAR_UUID[] = "f0001002-0451-4000-b000-000000000000";
}  // namespace config

struct TeleopCommand {
  float throttle = 0.0f;
  float turn = 0.0f;
  uint32_t heartbeat = 0;
  bool estop = false;
  bool estopClear = false;
};

// ---------------------------------------------------------------------------
// Global state
// NOTE: g_latest, g_lastCommandMs, etc. are written from the BLE callback
// (which runs on the BLE FreeRTOS task) and read from loop() (Arduino task).
// On ESP32, aligned 32-bit writes are atomic, and float/uint32_t are 32-bit,
// so this is safe for single-writer scenarios. If multi-writer access is ever
// added, proper synchronization (e.g. portMUX) will be needed.
// ---------------------------------------------------------------------------
BLECharacteristic* g_statusChar = nullptr;
bool g_bleConnected = false;
bool g_estopLatched = false;
uint32_t g_lastCommandMs = 0;
uint32_t g_lastHeartbeat = 0;
float g_lastBatteryV = 0.0f;

float clampUnit(float value) {
  if (value > 1.0f) return 1.0f;
  if (value < -1.0f) return -1.0f;
  return value;
}

class MotorOutput {
 public:
  void begin() {
    pinMode(config::PIN_LEFT_DIR, OUTPUT);
    pinMode(config::PIN_RIGHT_DIR, OUTPUT);

    ledcSetup(config::PWM_CHANNEL_LEFT, config::PWM_FREQUENCY_HZ, config::PWM_RESOLUTION_BITS);
    ledcSetup(config::PWM_CHANNEL_RIGHT, config::PWM_FREQUENCY_HZ, config::PWM_RESOLUTION_BITS);
    ledcAttachPin(config::PIN_LEFT_PWM, config::PWM_CHANNEL_LEFT);
    ledcAttachPin(config::PIN_RIGHT_PWM, config::PWM_CHANNEL_RIGHT);

    safeStop();
  }

  void writeMixed(float throttle, float turn) {
    const float t = clampUnit(throttle);
    const float r = clampUnit(turn * config::TURN_SCALING);
    const float left = clampUnit(t + r);
    const float right = clampUnit(t - r);

    writeSide(config::PIN_LEFT_DIR, config::PWM_CHANNEL_LEFT, left);
    writeSide(config::PIN_RIGHT_DIR, config::PWM_CHANNEL_RIGHT, right);
  }

  void safeStop() {
    digitalWrite(config::PIN_LEFT_DIR, LOW);
    digitalWrite(config::PIN_RIGHT_DIR, LOW);
    ledcWrite(config::PWM_CHANNEL_LEFT, 0);
    ledcWrite(config::PWM_CHANNEL_RIGHT, 0);
  }

 private:
  void writeSide(int dirPin, int pwmChannel, float command) {
    const bool forward = command >= 0.0f;
    const float magnitude = fabsf(command);

    int pwm = static_cast<int>(magnitude * config::PWM_MAX);
    if (pwm > 0 && pwm < config::PWM_FLOOR) {
      pwm = config::PWM_FLOOR;
    }
    pwm = constrain(pwm, 0, config::PWM_MAX);

    digitalWrite(dirPin, forward ? HIGH : LOW);
    ledcWrite(pwmChannel, pwm);
  }
};

class BatteryAdc {
 public:
  void begin() {
    analogReadResolution(12);
    pinMode(config::PIN_BATTERY_ADC, INPUT);
    for (int i = 0; i < AVG_WINDOW; i++) samples_[i] = 0.0f;
  }

  void sample() {
    const int raw = analogRead(config::PIN_BATTERY_ADC);
    const float pinVoltage = (static_cast<float>(raw) / config::ADC_MAX_COUNTS) * config::ADC_REFERENCE_V;
    const float batteryV = pinVoltage * config::BATTERY_DIVIDER_RATIO * config::BATTERY_CALIBRATION;

    samples_[sampleIdx_] = batteryV;
    sampleIdx_ = (sampleIdx_ + 1) % AVG_WINDOW;
    if (sampleCount_ < AVG_WINDOW) sampleCount_++;

    float sum = 0.0f;
    for (int i = 0; i < sampleCount_; i++) sum += samples_[i];
    g_lastBatteryV = sum / static_cast<float>(sampleCount_);
  }

 private:
  static constexpr int AVG_WINDOW = 8;
  float samples_[AVG_WINDOW] = {};
  int sampleIdx_ = 0;
  int sampleCount_ = 0;
};

MotorOutput g_motor;
BatteryAdc g_battery;
TeleopCommand g_latest;

void publishStatus(const String& status) {
  Serial.println(status);
  if (g_statusChar) {
    g_statusChar->setValue(status.c_str());
    g_statusChar->notify();
  }
}

bool parseField(const String& payload, const char* key, float& outValue) {
  const String tag = String(key) + ":";
  const int start = payload.indexOf(tag);
  if (start < 0) return false;

  const int valueStart = start + tag.length();
  int valueEnd = payload.indexOf(',', valueStart);
  if (valueEnd < 0) valueEnd = payload.length();
  outValue = payload.substring(valueStart, valueEnd).toFloat();
  return true;
}

bool parseCommand(const std::string& raw, TeleopCommand& cmd) {
  const String payload(raw.c_str());
  float throttle = 0.0f;
  float turn = 0.0f;
  float heartbeat = 0.0f;
  float estop = 0.0f;
  float estopClear = 0.0f;

  if (!parseField(payload, "T", throttle)) return false;
  if (!parseField(payload, "R", turn)) return false;
  if (!parseField(payload, "H", heartbeat)) return false;

  parseField(payload, "E", estop);
  parseField(payload, "C", estopClear);

  cmd.throttle = clampUnit(throttle);
  cmd.turn = clampUnit(turn);
  cmd.heartbeat = static_cast<uint32_t>(heartbeat);
  cmd.estop = estop > 0.5f;
  cmd.estopClear = estopClear > 0.5f;
  return true;
}

class CommandCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* characteristic) override {
    const std::string value = characteristic->getValue();
    TeleopCommand parsed;

    if (!parseCommand(value, parsed)) {
      publishStatus("CMD_PARSE_ERROR");
      return;
    }

    if (parsed.estop) {
      g_estopLatched = true;
      g_motor.safeStop();
      publishStatus("ESTOP_LATCHED");
    }

    if (g_estopLatched && parsed.estopClear && fabsf(parsed.throttle) < 0.01f && fabsf(parsed.turn) < 0.01f) {
      g_estopLatched = false;
      publishStatus("ESTOP_CLEARED");
    }

    g_latest = parsed;
    g_lastHeartbeat = parsed.heartbeat;
    g_lastCommandMs = millis();
  }
};

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer*) override {
    g_bleConnected = true;
    publishStatus("BLE_CONNECTED");
  }

  void onDisconnect(BLEServer* server) override {
    g_bleConnected = false;
    g_motor.safeStop();
    server->startAdvertising();
    publishStatus("BLE_DISCONNECTED");
  }
};

void setupBle() {
  BLEDevice::init(config::BLE_DEVICE_NAME);
  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks());

  BLEService* service = server->createService(config::BLE_SERVICE_UUID);

  BLECharacteristic* command = service->createCharacteristic(
      config::BLE_COMMAND_CHAR_UUID,
      BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);
  command->setCallbacks(new CommandCallbacks());

  g_statusChar = service->createCharacteristic(
      config::BLE_STATUS_CHAR_UUID,
      BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
  g_statusChar->addDescriptor(new BLE2902());
  g_statusChar->setValue("BOOT");

  service->start();
  server->getAdvertising()->start();
}

void setup() {
  Serial.begin(115200);
  delay(200);

  g_motor.begin();
  g_motor.safeStop();
  g_battery.begin();

  setupBle();
  g_lastCommandMs = millis();

  publishStatus("IDLE_DISARMED");
}

void loop() {
  static uint32_t lastAdcSampleMs = 0;
  static uint32_t lastTelemetryMs = 0;

  const uint32_t now = millis();

  if ((now - lastAdcSampleMs) >= config::ADC_SAMPLE_MS) {
    lastAdcSampleMs = now;
    g_battery.sample();
  }

  if (g_estopLatched) {
    g_motor.safeStop();
  } else if ((now - g_lastCommandMs) > config::DEADMAN_TIMEOUT_MS) {
    g_motor.safeStop();
  } else {
    g_motor.writeMixed(g_latest.throttle, g_latest.turn);
  }

  if ((now - lastTelemetryMs) >= config::SERIAL_TELEMETRY_MS) {
    lastTelemetryMs = now;
    Serial.printf(
        "state=%s,ble=%d,thr=%.2f,turn=%.2f,hb=%lu,batt=%.2fV\n",
        g_estopLatched ? "ESTOP" : (((now - g_lastCommandMs) > config::DEADMAN_TIMEOUT_MS) ? "DEADMAN" : "ACTIVE"),
        g_bleConnected,
        g_latest.throttle,
        g_latest.turn,
        static_cast<unsigned long>(g_lastHeartbeat),
        g_lastBatteryV);
  }

  delay(5);
}
