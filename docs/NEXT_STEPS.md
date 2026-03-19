# Next Steps

_Last updated: 2026-03-19_

## Now

- Receive parts tomorrow; update `docs/PROCUREMENT_STATUS.md` as items arrive.
- Verify ESP32 enumerates over USB and flashes cleanly.
- Flash `firmware/stage1-motor-test/` to confirm toolchain works end-to-end.
- Receive Romi chassis (#3506) and Motor Driver board (#3543) Saturday.
- Assemble per `docs/builds/stage1-rover-a-build.md`.
- Perform wiring and pre-power checks per `docs/STAGE_1_WIRING.md` (R1=22kΩ / R2=10kΩ).
- Flash motor test on assembled hardware for wheel-off-ground validation.
- Reflash `firmware/stage1-esp32-baseline/` and run first logged bench bring-up.

## Next

- Execute deadman/e-stop validation; record in `docs/STAGE_1_TUNING.md`.
- Perform battery ADC calibration per `docs/STAGE_1_TUNING.md`.
- Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture pass/fail evidence.
- Tune drivability (PWM floor, turn scaling, deadman timeout).

## Stage 2 (after Stage 1 acceptance)

- Add Wi-Fi transport alongside BLE using the same T,R,H,E,C protocol.
- Build web-based control dashboard.
- Begin mobile app design.
- Start planning handheld physical controller (Pi Zero + screen + joysticks).

## Later

- Mk2/Mk3/Mk4 remain documented planning scope only.
- Front distance sensing (Stage 3), encoders + IMU (Stage 4).
- Telemetry logging, higher-level control loops.
- Handheld physical controller as primary long-term control surface.

## Blocked

- Final naming/branding.
- Autonomy stack before Stage 1 completion.
- All control surface work until Stage 2.
