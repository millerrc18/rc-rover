# Next Steps

_Last updated: 2026-03-12_

This file contains the prioritized action queue for `rc-rover`.

## Now

- Create a Stage 1 wiring diagram artifact with exact pin assignments derived from `docs/INTERFACE_MAP.md`.
- Create firmware scaffold for ESP32 BLE teleop + differential motor output + deadman timeout.
- Build and run Stage 1 bench bring-up checklist (USB, motor spin, battery ADC).
- Start purchasing from `hardware/bom-stage-0-1.csv` and track substitutions explicitly.

## Next

- Execute full mechanical assembly on the selected chassis.
- Run `docs/STAGE_1_ACCEPTANCE_TEST.md` and record pass/fail evidence.
- Tune low-speed drivability parameters (PWM floor, turn scaling, timeout).
- Add a simple operator checklist for pre-drive safety checks.

## Later

- Add front distance sensing (Stage 3 path).
- Add wheel encoders and IMU for motion awareness (Stage 4 path).
- Add telemetry logging and higher-level control loops.
- Revisit Wi-Fi teleop mode as an optional control path after BLE baseline is stable.

## Blocked

- Final naming/branding.
- Autonomy stack and heavy perception before Stage 1 completion.
