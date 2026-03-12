# Handoff Summary

_Last updated: 2026-03-12_

Quick snapshot for the next session.

## Current phase

Stage 0/1 hardware freeze (in execution)

## Current objective

Use the frozen hardware package to begin sourcing, wiring detail, and Stage 1 firmware/mechanical bring-up.

## What just changed

- Added Stage 1 hardware freeze docs:
  - `docs/HARDWARE_ARCHITECTURE.md`
  - `docs/INTERFACE_MAP.md`
  - `docs/STAGE_1_BUILD_PLAN.md`
- Strengthened `hardware/bom-stage-0-1.csv` into a sourced first-pass BOM.
- Recorded explicit decisions:
  - ESP32 board: Espressif ESP32-DevKitC-32E
  - Motor-driver path: Pololu Romi Motor Driver and Power Distribution Board
  - Manual-control baseline: BLE teleop
- Realigned `docs/PROJECT_STATE.md` with active Stage 0/1 freeze work (not bootstrap).

## Constraints to preserve

- Keep Stage 1 simple and buildable.
- Differential-drive robotics-first direction is fixed.
- ESP32-class control and manual-control-first remain fixed.
- No autonomy/camera/lidar scope in Stage 1.

## Open questions

- Which BLE control app/profile should be standardized for first firmware tests?
- What timeout and ramp limits feel safest while still drivable?
- Which acceptable alternates should be pre-approved for stock shortages?

## Next three high-priority actions

1. Produce exact wiring/pin map and include continuity/polarity checklist.
2. Implement firmware scaffold for BLE teleop + motor control + deadman + battery ADC.
3. Begin part ordering and log substitutions/availability notes.

## Key files to read first next session

- `docs/PROJECT_STATE.md`
- `docs/HARDWARE_ARCHITECTURE.md`
- `docs/INTERFACE_MAP.md`
- `docs/STAGE_1_BUILD_PLAN.md`
- `hardware/bom-stage-0-1.csv`
- `docs/STAGE_1_ACCEPTANCE_TEST.md`
- `docs/NEXT_STEPS.md`
