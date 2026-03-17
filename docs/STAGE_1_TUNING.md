# Stage 1 Tuning Notes

_Last updated: 2026-03-17_

Field-ready notes for first tuning passes after baseline firmware flash.

## Initial tuning variables

| Variable | Default | Location in firmware | Notes |
|---|---|---|---|
| Deadman timeout | `300 ms` | `config::DEADMAN_TIMEOUT_MS` | Conservative safe default |
| PWM frequency | `18 kHz` | `config::PWM_FREQUENCY_HZ` | Above audible range |
| PWM resolution | `8-bit` | `config::PWM_RESOLUTION_BITS` | 0–255 range |
| PWM floor | `0` | `config::PWM_FLOOR` | Safest initial value; raise after first wheel test |
| Turn scaling | `1.0` | `config::TURN_SCALING` | Reduce if turns feel too sharp |
| Battery calibration | `1.0f` | `config::BATTERY_CALIBRATION` | Must be measured; see calibration procedure below |
| Ramp limit | `99.0f/sec` | `config::FUTURE_RAMP_LIMIT_PER_SEC` | Placeholder only — see note below |

---

## Battery ADC calibration procedure

The firmware reports battery voltage by scaling ADC counts using a fixed divider ratio and a calibration multiplier. The default calibration multiplier is `1.0f`, which assumes the resistor values are exactly nominal. Real resistors have tolerance, and the ESP32 ADC has its own non-linearity. A one-time calibration measurement is required for accurate readings.

### Required tools
- Digital multimeter set to DC voltage.
- Charged AA NiMH battery pack installed in the rover.
- Serial monitor open at 115200 baud.

### Step-by-step

1. Install a charged battery pack in the Romi chassis.
2. Power on the ESP32 (USB or battery-powered via 5V rail).
3. In the serial monitor, observe the `batt=X.XXV` field in the telemetry output. Note the reported value. Let it stabilize for 5–10 seconds (moving average settles after ~0.8 seconds with 8-sample window).
4. With the rover idle (no motor commands), use your multimeter to measure the actual voltage directly across the battery pack terminals.
5. Compute the correction factor:
   ```
   correction = actual_measured_voltage / firmware_reported_voltage
   ```
   Example: multimeter reads 7.85V, firmware reports 7.60V → correction = 7.85 / 7.60 = 1.033
6. Open `firmware/stage1-esp32-baseline/src/main.cpp`.
7. Update the `BATTERY_CALIBRATION` constant:
   ```cpp
   constexpr float BATTERY_CALIBRATION = 1.033f;  // measured 2026-MM-DD
   ```
8. Rebuild and reflash.
9. Verify the reported voltage now matches the multimeter reading within ±0.1V.
10. Record the date, measured values, and final calibration factor in the test note table below.

### Notes on ADC accuracy

- The ESP32 ADC is known to have non-linearity near the top and bottom of its range. For best accuracy, take calibration measurements near the middle of the expected operating range (nominally charged NiMH pack, not fresh off the charger).
- If you observe inconsistent readings, ensure the optional 100nF filter cap is installed on the ADC node (see `STAGE_1_WIRING_DIAGRAM.md`).
- The 8-sample moving average in the firmware (window size in `BatteryAdc::sample()`) already smooths short-term noise. The calibration corrects for systematic offset, not noise.

---

## Ramp limiter note

The firmware declares `config::FUTURE_RAMP_LIMIT_PER_SEC = 99.0f` as a placeholder but does **not** use it in the Stage 1 control loop. Motor commands go directly to PWM output with no acceleration ramp applied.

This is intentional for Stage 1 — the safest first behavior is no hidden smoothing so you see raw command behavior during bring-up.

**When to add a ramp limiter:** If sudden BLE command changes or deadman recovery cause jerky motion or brownouts under battery power, add a per-loop ramp clamp in `writeMixed()`:

```cpp
// Example approach (Stage 1.1 enhancement):
// lastLeft = clamp(newLeft, lastLeft - maxStep, lastLeft + maxStep);
```

Set `FUTURE_RAMP_LIMIT_PER_SEC` to a real value (e.g. `2.0f` = full range in 0.5 sec) and wire it into the loop at that time. Record the change in `docs/DECISIONS.md`.

---

## Bench tuning checklist

1. Flash `firmware/stage1-motor-test/` first. Run wheel-off-ground test sequence. Confirm motor spin directions and note any reversed sides.
2. Reflash `firmware/stage1-esp32-baseline/`.
3. With wheels elevated, connect via BLE and confirm `T:0.00,R:0.00` gives no wheel motion.
4. Send low throttle (`T:0.15`) and note the first effective PWM for each side (observe if one side lags).
5. Apply left/right turn at low throttle and check controllability symmetry.
6. Trigger deadman by disconnecting BLE — confirm motors stop within 300ms.
7. Trigger e-stop (`E:1`) — confirm immediate stop and `ESTOP_LATCHED` in serial.
8. Clear e-stop (`T:0,R:0,C:1`) — confirm `ESTOP_CLEARED` in serial.
9. Perform battery ADC calibration (see procedure above).
10. Record any low-voltage sag symptoms under light drive.

---

## Test note table

| Date | Firmware commit | Deadman (ms) | PWM floor | Turn scaling | Batt reported (V) | Batt actual (V) | Calibration factor | Notes |
|---|---|---:|---:|---:|---:|---:|---:|---|
| 2026-03-17 | _TBD_ | 300 | 0 | 1.0 | _TBD_ | _TBD_ | 1.0 (default) | Baseline values. Calibration pending hardware test. |
