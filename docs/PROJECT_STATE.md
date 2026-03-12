# Project State

_Last updated: 2026-03-12_

This file is the canonical description of current project status.

## Current phase

**Stage 0/1 hardware freeze (active)**

The project has moved beyond repository bootstrap and is now focused on a practical, buildable Stage 1 rover package.

## Current objective

Finalize hardware architecture and interfaces, freeze a first-pass sourced BOM, and begin assembly/firmware bring-up preparation.

## Summary of progress

- Platform direction is locked to a robotics-first differential-drive base.
- Stage 1 hardware freeze package has been created:
  - `docs/HARDWARE_ARCHITECTURE.md`
  - `docs/INTERFACE_MAP.md`
  - `docs/STAGE_1_BUILD_PLAN.md`
- Stage 0/1 BOM has been strengthened with sourced first-pass recommendations in `hardware/bom-stage-0-1.csv`.
- Explicit decisions are now recorded for exact ESP32 board, motor-driver path, and initial manual-control method.

## Completed tasks

- Established documentation-driven memory system.
- Added platform selection and Stage 1 acceptance test artifacts.
- Frozen Stage 1 baseline architecture and interfaces.
- Updated canonical docs (`HANDOFF`, `NEXT_STEPS`, `ARCHITECTURE`, `INDEX`) to reflect active Stage 0/1 freeze work.

## Open tasks

See `docs/NEXT_STEPS.md` for queue order. Immediate work now shifts to wiring artifact detail, firmware scaffold, and physical assembly/validation.

## Hardware state

No full rover assembled yet. The first-pass sourced BOM and integration path are now frozen enough for purchasing and bench preparation.

## Software state

No production firmware yet. Stage 1 firmware scope is defined: BLE teleop input, differential motor control output, deadman/e-stop handling, and battery voltage reporting.

## Confirmed decisions now in effect

- Standard dev board: Espressif ESP32-DevKitC-32E.
- Primary motor-driver path: Pololu Romi Motor Driver and Power Distribution Board.
- Initial manual control: BLE teleop.

## Assumptions

- **Assumption:** Distributor-verified equivalents may be used when exact part stock is constrained, if fit/form/function remains compatible.
- **Assumption:** Initial test environment is indoor flat-surface operation.
- **Assumption:** Stage 1 remains strictly manual-control first; autonomy remains out of scope.
