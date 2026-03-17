# Next Steps

_Last updated: 2026-03-17_

This file contains the prioritized action queue for `rc-rover`.

## Now

- Receive parts tomorrow; update `docs/PROCUREMENT_STATUS.md` as items arrive.
- Verify ESP32 enumerates over USB and flashes cleanly before chassis arrives.
- Flash `firmware/stage1-motor-test/` to confirm toolchain works end-to-end.
- Receive Romi chassis (#3506) and Motor Driver board (#3543) Saturday; begin assembly per `docs/builds/stage1-rover-a-build.md`.
- Perform wiring and pre-power continuity/polarity checks per `docs/STAGE_1_WIRING_DIAGRAM.md` (R1=20kΩ / R2=10kΩ for battery divider).
- Flash `firmware/stage1-motor-test/` on assembled hardware for wheel-off-ground motor direction validation.
- Reflash `firmware/stage1-esp32-baseline/` and run first logged bench bring-up in `docs/BENCH_BRINGUP_LOG.md`.

## Next

- Execute deadman/e-stop validation; record in `docs/STAGE_1_TUNING.md`.
- Perform battery ADC calibration per procedure in `docs/STAGE_1_TUNING.md`.
- Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture pass/fail evidence.
- Tune drivability parameters (PWM floor, turn scaling, deadman timeout).
- Add a one-page operator checklist for pre-drive and shutdown safety.

## Stage 2 (after Stage 1 acceptance)

- Add Wi-Fi transport to ESP32 firmware alongside BLE, using the same T,R,H,E,C protocol.
- Build web-based control dashboard as first new control surface.
- Begin mobile app design (React Native or Flutter).
- Start planning the handheld physical controller (Pi Zero + screen + joysticks).

## Later

- Keep Mk2/Mk3/Mk4 as documented planning scope only until Stage 1 physical acceptance is complete.
- Add front distance sensing (Stage 3 path).
- Add wheel encoders and IMU for motion awareness (Stage 4 path).
- Add telemetry logging and higher-level control loops.
- Build handheld physical controller as primary long-term control surface.

## Blocked

- Final naming/branding.
- Autonomy stack and heavy perception before Stage 1 completion.
- All control surface work until Stage 2.
