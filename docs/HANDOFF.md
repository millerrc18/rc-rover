# Handoff Summary

_Last updated: 2026-03-12_

Quick snapshot for the next session.

## Current phase

Stage 1 wiring + firmware bring-up execution (ready)

## Current objective

Use the frozen Stage 1 wiring/pin/firmware package to perform real bench bring-up and acceptance testing.

## What just changed

- Added Stage 1 bring-up package docs:
  - `docs/STAGE_1_WIRING_DIAGRAM.md`
  - `docs/STAGE_1_PIN_MAP.md`
  - `docs/FIRMWARE_SCAFFOLD.md`
- Updated `docs/HARDWARE_ARCHITECTURE.md` with explicit power-flow diagram and exact ESP32 power-mode explanation.
- Updated `docs/INTERFACE_MAP.md` with frozen pin-level interface entries.
- Updated `hardware/bom-stage-0-1.csv` to remove board-dependent ambiguity:
  - frozen untethered logic-power harness path
  - frozen USB cable type (USB-A to Micro-USB data cable)

## Constraints to preserve

- Keep Stage 1 simple and buildable.
- Differential-drive robotics-first direction is fixed.
- ESP32-DevKitC-32E + Romi motor board baseline is fixed.
- No autonomy/camera/lidar scope in Stage 1.

## Open questions

- Which BLE control app/profile should be standardized for first firmware tests?
- What deadman timeout and ramp limits feel safest while still drivable?
- Do we need a low-voltage duty-cap policy in Stage 1 or warning-only behavior first?

## Next three high-priority actions

1. Wire hardware exactly per `docs/STAGE_1_WIRING_DIAGRAM.md` and run pre-power checklist.
2. Implement initial firmware per `docs/FIRMWARE_SCAFFOLD.md` using `docs/STAGE_1_PIN_MAP.md`.
3. Run `docs/STAGE_1_ACCEPTANCE_TEST.md` and record evidence/outcomes.

## Key files to read first next session

- `docs/PROJECT_STATE.md`
- `docs/STAGE_1_WIRING_DIAGRAM.md`
- `docs/STAGE_1_PIN_MAP.md`
- `docs/FIRMWARE_SCAFFOLD.md`
- `docs/HARDWARE_ARCHITECTURE.md`
- `docs/INTERFACE_MAP.md`
- `hardware/bom-stage-0-1.csv`
- `docs/STAGE_1_ACCEPTANCE_TEST.md`
