# Next Steps

_Last updated: 2026-03-13_

This file contains the prioritized action queue for `rc-rover`.

## Now

- Flash `firmware/stage1-esp32-baseline/` to ESP32 and run first real bench bring-up session.
- Fill one full run entry in `docs/BENCH_BRINGUP_LOG.md` with USB and battery power evidence.
- Execute deadman/e-stop validation and record measured behavior in `docs/STAGE_1_TUNING.md`.
- Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture pass/fail evidence in docs.

## Next

- Tune drivability parameters (PWM floor, turn scaling, deadman timeout) from safe defaults.
- Validate and calibrate battery divider scaling against multimeter readings.
- Start purchasing from `hardware/bom-stage-0-1.csv` and log substitutions explicitly.
- Add a one-page operator checklist for pre-drive and shutdown safety.

## Later

- Add front distance sensing (Stage 3 path).
- Add wheel encoders and IMU for motion awareness (Stage 4 path).
- Add telemetry logging and higher-level control loops.
- Revisit Wi-Fi teleop mode as an optional control path after BLE baseline is stable.

## Blocked

- Final naming/branding.
- Autonomy stack and heavy perception before Stage 1 completion.
