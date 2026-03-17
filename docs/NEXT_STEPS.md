# Next Steps

_Last updated: 2026-03-17_

This file contains the prioritized action queue for `rc-rover`.

## Now

- Order Stage 0/1 buy-now parts from `hardware/bom-stage-0-1.csv` and track status in `docs/PROCUREMENT_STATUS.md` (do not duplicate Romi motors/wheels/caster/battery holder already included in full kit).
- Receive and inspect ordered parts; log any substitutions, defects, or missing items.
- Begin Stage 1 mechanical assembly once critical parts pass inspection.
- Perform initial wiring and pre-power continuity/polarity checks.
- Flash `firmware/stage1-esp32-baseline/` to ESP32 hardware.
- Run and log the first real bench bring-up session in `docs/BENCH_BRINGUP_LOG.md`.

## Next

- Execute deadman/e-stop validation and record measured behavior in `docs/STAGE_1_TUNING.md`.
- Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture pass/fail evidence in docs.
- Tune drivability parameters (PWM floor, turn scaling, deadman timeout) from safe defaults.
- Validate and calibrate battery divider scaling against multimeter readings.
- Add a one-page operator checklist for pre-drive and shutdown safety.

## Later

- Keep Mk2/Mk3/Mk4 as documented planning scope only until Stage 1 physical acceptance is complete.
- Add front distance sensing (Stage 3 path).
- Add wheel encoders and IMU for motion awareness (Stage 4 path).
- Add telemetry logging and higher-level control loops.
- Revisit Wi-Fi teleop mode as an optional control path after BLE baseline is stable.

## Blocked

- Final naming/branding.
- Autonomy stack and heavy perception before Stage 1 completion.
