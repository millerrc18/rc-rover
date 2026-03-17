# Next Steps

_Last updated: 2026-03-17_

This file contains the prioritized action queue for `rc-rover`.

## Now

- Order Stage 0/1 buy-now parts from `hardware/bom-stage-0-1.csv` and track status in `docs/PROCUREMENT_STATUS.md` (do not duplicate Romi motors/wheels/caster/battery holder already included in full kit).
- Receive and inspect ordered parts; log any substitutions, defects, or missing items.
- Begin Stage 1 mechanical assembly once critical parts pass inspection.
- Use `docs/builds/stage1-rover-a-build.md` as the live checklist during first physical assembly. This guide now targets the correct Pololu Romi Motor Driver board (#3543) and uses the correct frozen pin map throughout.
- Perform initial wiring and pre-power continuity/polarity checks per `docs/STAGE_1_WIRING_DIAGRAM.md` (includes resistor values for battery divider: R1=20kΩ / R2=10kΩ).
- Flash `firmware/stage1-motor-test/` first for wheel-off-ground motor direction validation (no BLE app required).
- After motor directions confirmed, reflash `firmware/stage1-esp32-baseline/` for full BLE teleop.
- Run and log the first real bench bring-up session in `docs/BENCH_BRINGUP_LOG.md`.

## Next

- Execute deadman/e-stop validation and record measured behavior in `docs/STAGE_1_TUNING.md`.
- Perform battery ADC calibration per the procedure in `docs/STAGE_1_TUNING.md` and update the `BATTERY_CALIBRATION` firmware constant.
- Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture pass/fail evidence in docs.
- Tune drivability parameters (PWM floor, turn scaling, deadman timeout) from safe defaults.
- Add a one-page operator checklist for pre-drive and shutdown safety.

## Later

- Keep Mk2/Mk3/Mk4 as documented planning scope only until Stage 1 physical acceptance is complete.
- Keep any hybrid/range-extender discussion as later-generation architecture planning only; no current execution tasks are opened for it.
- Add front distance sensing (Stage 3 path).
- Add wheel encoders and IMU for motion awareness (Stage 4 path).
- Add telemetry logging and higher-level control loops.
- Revisit Wi-Fi teleop mode as an optional control path after BLE baseline is stable.
- Consider ramp limiter implementation (see `STAGE_1_TUNING.md` ramp limiter note) if jerky motion or brownouts are observed.

## Blocked

- Final naming/branding.
- Autonomy stack and heavy perception before Stage 1 completion.
