# Handoff Summary

_Last updated: 2026-03-13_

Quick snapshot for the next session.

## Current phase

Stage 1 firmware baseline complete; bench validation execution in progress

## Current objective

Use the committed Stage 1 firmware baseline and bring-up docs to run and log real bench sessions.

## What just changed

- Added executable firmware baseline project: `firmware/stage1-esp32-baseline/` with safe startup, BLE command intake, differential mix, deadman timeout, e-stop latch, and battery ADC reporting.
- Added BLE command profile reference: `docs/BLE_CONTROL_PROFILE.md`.
- Added reusable bring-up run template: `docs/BENCH_BRINGUP_LOG.md`.
- Added initial tuning reference sheet: `docs/STAGE_1_TUNING.md`.
- Updated canonical state/action docs and quality logs for Stage 1 bench execution.

## Constraints to preserve

- Keep Stage 1 simple and buildable.
- Differential-drive robotics-first direction is fixed.
- ESP32-DevKitC-32E + Romi motor board baseline is fixed.
- No autonomy/camera/lidar scope in Stage 1.

## Open questions

- What measured deadman timeout feels safest while still drivable on real hardware?
- Do we need non-zero PWM floor after first wheel-off-ground tests?
- Should low-voltage handling remain warning-only or add duty-cap in Stage 1.1?

## Next three high-priority actions

1. Flash and smoke-test `firmware/stage1-esp32-baseline/` using USB bench power with wheels elevated.
2. Run and log full checks in `docs/BENCH_BRINGUP_LOG.md` and `docs/STAGE_1_TUNING.md`.
3. Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture evidence/outcomes.

## Key files to read first next session

- `docs/PROJECT_STATE.md`
- `docs/STAGE_1_WIRING_DIAGRAM.md`
- `docs/STAGE_1_PIN_MAP.md`
- `docs/FIRMWARE_SCAFFOLD.md`
- `docs/HARDWARE_ARCHITECTURE.md`
- `docs/INTERFACE_MAP.md`
- `docs/BLE_CONTROL_PROFILE.md`
- `docs/BENCH_BRINGUP_LOG.md`
- `docs/STAGE_1_TUNING.md`
- `docs/STAGE_1_ACCEPTANCE_TEST.md`
