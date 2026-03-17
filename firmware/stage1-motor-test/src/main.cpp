/*
 * Stage 1 Motor Test Sketch
 *
 * Purpose: Validate motor wiring and direction on first bench bring-up without
 * requiring a BLE app or phone. This sketch runs a fixed test sequence
 * automatically on boot and reports each step over USB serial (115200 baud).
 *
 * This sketch is NOT the production Stage 1 firmware. After motor validation
 * is complete, flash firmware/stage1-esp32-baseline/ for full BLE teleop.
 *
 * Pin map (must match docs/STAGE_1_PIN_MAP.md and the production firmware):
 *   Left motor PWM:  GPIO25
 *   Left motor DIR:  GPIO26
 *   Right motor PWM: GPIO27
 *   Right motor DIR: GPIO14  <-- NOTE: GPIO14, not GPIO33
 *
 * Build and flash:
 *   cd firmware/stage1-motor-test
 *   pio run -t upload
 *   pio device monitor -b 115200
 *
 * Expected serial output:
 *   [MOTOR TEST] Starting. Wheels must be ELEVATED.
 *   [MOTOR TEST] Step 1: Left motor forward ...
 *   [MOTOR TEST] Step 1: STOP
 *   ... (continues through all steps)
 *   [MOTOR TEST] Complete. Check direction notes above and reflash stage1-esp32-baseline.
 *
 * If a motor spins backward when "forward" is expected, note it here and
 * correct the direction logic in the production firmware (main.cpp writeSide())
 * rather than swapping physical wires.
 */

#include <Arduino.h>

// ---------------------------------------------------------------------------
// Pin assignments — must match STAGE_1_PIN_MAP.md and production firmware
// ---------------------------------------------------------------------------
constexpr int PIN_LEFT_PWM  = 25;
constexpr int PIN_LEFT_DIR  = 26;
constexpr int PIN_RIGHT_PWM = 27;
constexpr int PIN_RIGHT_DIR = 14;  // GPIO14, NOT GPIO33

constexpr int PWM_CH_LEFT  = 0;
constexpr int PWM_CH_RIGHT = 1;
constexpr int PWM_FREQ_HZ  = 18000;
constexpr int PWM_BITS     = 8;
constexpr int PWM_MAX      = 255;

// Test parameters — keep duty low for first bench test
constexpr int  TEST_DUTY_LOW  = 80;   // ~31% — enough to confirm spin
constexpr int  TEST_DUTY_MED  = 140;  // ~55% — used for combined-motor steps
constexpr uint32_t STEP_MS    = 1200; // How long each test step runs (ms)
constexpr uint32_t STOP_MS    = 600;  // Pause between steps (ms)

// ---------------------------------------------------------------------------
// Motor helpers
// ---------------------------------------------------------------------------
void motorsInit() {
  // Initialize direction pins LOW before anything else (GPIO14 boot-strap safety)
  pinMode(PIN_LEFT_DIR,  OUTPUT); digitalWrite(PIN_LEFT_DIR,  LOW);
  pinMode(PIN_RIGHT_DIR, OUTPUT); digitalWrite(PIN_RIGHT_DIR, LOW);

  ledcSetup(PWM_CH_LEFT,  PWM_FREQ_HZ, PWM_BITS);
  ledcSetup(PWM_CH_RIGHT, PWM_FREQ_HZ, PWM_BITS);
  ledcAttachPin(PIN_LEFT_PWM,  PWM_CH_LEFT);
  ledcAttachPin(PIN_RIGHT_PWM, PWM_CH_RIGHT);

  ledcWrite(PWM_CH_LEFT,  0);
  ledcWrite(PWM_CH_RIGHT, 0);
}

void motorsStop() {
  ledcWrite(PWM_CH_LEFT,  0);
  ledcWrite(PWM_CH_RIGHT, 0);
  digitalWrite(PIN_LEFT_DIR,  LOW);
  digitalWrite(PIN_RIGHT_DIR, LOW);
}

// forward=true means DIR pin HIGH; adjust in production firmware if physically reversed
void setLeft(bool forward, int duty) {
  digitalWrite(PIN_LEFT_DIR, forward ? HIGH : LOW);
  ledcWrite(PWM_CH_LEFT, constrain(duty, 0, PWM_MAX));
}

void setRight(bool forward, int duty) {
  digitalWrite(PIN_RIGHT_DIR, forward ? HIGH : LOW);
  ledcWrite(PWM_CH_RIGHT, constrain(duty, 0, PWM_MAX));
}

// ---------------------------------------------------------------------------
// Test step helpers
// ---------------------------------------------------------------------------
void runStep(const char* label, uint32_t durationMs) {
  Serial.printf("[MOTOR TEST] %s\n", label);
  delay(durationMs);
  motorsStop();
  Serial.println("[MOTOR TEST] STOP");
  delay(STOP_MS);
}

// ---------------------------------------------------------------------------
// Setup / main test sequence
// ---------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(300);

  motorsInit();
  motorsStop();

  Serial.println();
  Serial.println("========================================");
  Serial.println("[MOTOR TEST] Starting.");
  Serial.println("[MOTOR TEST] WHEELS MUST BE ELEVATED.");
  Serial.println("[MOTOR TEST] Watch each wheel for correct spin direction.");
  Serial.println("[MOTOR TEST] Note any reversed directions below:");
  Serial.println("  Expected: DIR HIGH = forward (away from caster end)");
  Serial.println("  If reversed: correct writeSide() in stage1-esp32-baseline main.cpp");
  Serial.println("========================================");
  delay(2000);

  // --- Step 1: Left motor forward ---
  setLeft(true, TEST_DUTY_LOW);
  setRight(false, 0);
  runStep("Step 1: Left motor FORWARD (right wheel should be still)", STEP_MS);

  // --- Step 2: Left motor reverse ---
  setLeft(false, TEST_DUTY_LOW);
  setRight(false, 0);
  runStep("Step 2: Left motor REVERSE (right wheel should be still)", STEP_MS);

  // --- Step 3: Right motor forward ---
  setLeft(false, 0);
  setRight(true, TEST_DUTY_LOW);
  runStep("Step 3: Right motor FORWARD (left wheel should be still)", STEP_MS);

  // --- Step 4: Right motor reverse ---
  setLeft(false, 0);
  setRight(false, TEST_DUTY_LOW);
  runStep("Step 4: Right motor REVERSE (left wheel should be still)", STEP_MS);

  // --- Step 5: Both forward ---
  setLeft(true, TEST_DUTY_MED);
  setRight(true, TEST_DUTY_MED);
  runStep("Step 5: BOTH motors FORWARD", STEP_MS);

  // --- Step 6: Both reverse ---
  setLeft(false, TEST_DUTY_MED);
  setRight(false, TEST_DUTY_MED);
  runStep("Step 6: BOTH motors REVERSE", STEP_MS);

  // --- Step 7: Left turn (left slower, right faster) ---
  setLeft(true, TEST_DUTY_LOW / 2);
  setRight(true, TEST_DUTY_MED);
  runStep("Step 7: LEFT TURN (left slow, right fast)", STEP_MS);

  // --- Step 8: Right turn (right slower, left faster) ---
  setLeft(true, TEST_DUTY_MED);
  setRight(true, TEST_DUTY_LOW / 2);
  runStep("Step 8: RIGHT TURN (right slow, left fast)", STEP_MS);

  Serial.println("========================================");
  Serial.println("[MOTOR TEST] Sequence complete.");
  Serial.println("[MOTOR TEST] Review direction results above.");
  Serial.println("[MOTOR TEST] Record any reversed motors in docs/STAGE_1_TUNING.md.");
  Serial.println("[MOTOR TEST] Next: flash firmware/stage1-esp32-baseline/ for BLE teleop.");
  Serial.println("========================================");
}

void loop() {
  // Ensure motors stay off after test completes.
  motorsStop();
  delay(1000);
}
