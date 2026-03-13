# Next Steps

_Last updated: 2026-03-12_

This file contains the prioritized action queue for `rc-rover`.

## Now

- Physically wire the rover exactly per `docs/STAGE_1_WIRING_DIAGRAM.md` and record any deviations.
- Implement first firmware pass from `docs/FIRMWARE_SCAFFOLD.md` using `docs/STAGE_1_PIN_MAP.md` pin assignments.
- Run bench bring-up sequence (USB flash, motor spin checks, battery ADC validation).
- Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture pass/fail evidence in docs.

## Next

- Tune drivability parameters (PWM floor, turn scaling, deadman timeout) from safe defaults.
- Standardize a single BLE app/profile and command packet example for repeatable testing.
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
