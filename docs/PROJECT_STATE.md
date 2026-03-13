# Project State

_Last updated: 2026-03-13_

This file is the canonical description of current project status.

## Current phase

**Stage 1 firmware baseline implemented (ready for real bench bring-up logging)**

## Current objective

Run real bench bring-up sessions using the committed Stage 1 ESP32 firmware baseline and new test artifacts.

## Summary of progress

- Platform direction is locked to a robotics-first differential-drive base.
- Stage 1 hardware and interface freeze artifacts exist and are cross-linked.
- Stage 1 execution package now includes exact wiring/pin docs, firmware scaffold, and a committed executable baseline project:
  - `docs/STAGE_1_WIRING_DIAGRAM.md`
  - `docs/STAGE_1_PIN_MAP.md`
  - `docs/FIRMWARE_SCAFFOLD.md`
  - `firmware/stage1-esp32-baseline/`
- Added bring-up support documents for real bench testing:
  - `docs/BLE_CONTROL_PROFILE.md`
  - `docs/BENCH_BRINGUP_LOG.md`
  - `docs/STAGE_1_TUNING.md`
- Logic-power ambiguity is resolved:
  - Bench bring-up ESP32 power: USB-A to Micro-USB cable.
  - Untethered ESP32 power: motor board regulated 5V to ESP32 5V pin.
- BOM now freezes exact USB connector type for DevKitC-32E and adds explicit logic-power harness item.

## Completed tasks

- Established documentation-driven memory system.
- Added platform selection and Stage 1 acceptance test artifacts.
- Frozen Stage 1 baseline architecture and interfaces.
- Created Stage 1 wiring diagram with continuity/polarity/pre-power checklists.
- Frozen exact ESP32 Stage 1 pin assignments including ADC/PWM conflict avoidance.
- Defined implementation-ready firmware scaffold (BLE teleop, deadman, e-stop, drive mix, battery ADC, failure states).
- Implemented first executable Stage 1 firmware baseline with safe startup, BLE control intake, differential mixing, deadman timeout, e-stop latch, and battery ADC serial reporting.

## Open tasks

See `docs/NEXT_STEPS.md` for queue order. Immediate work is real hardware bring-up execution, tuning capture, and Stage 1 acceptance evidence.

## Hardware state

No full rover assembled yet, but wiring and power-path docs are now explicit enough for a real bench bring-up session.

## Software state

Production firmware baseline now exists in `firmware/stage1-esp32-baseline/` and is aligned to frozen Stage 1 pins and interfaces.

## Confirmed decisions now in effect

- Standard dev board: Espressif ESP32-DevKitC-32E.
- Primary motor-driver path: Pololu Romi Motor Driver and Power Distribution Board.
- Initial manual control: BLE teleop.
- Untethered ESP32 logic power: MPDB regulated 5V -> ESP32 5V pin.
- Bench cable standard: USB-A to Micro-USB data cable.

## Assumptions

- **Assumption:** MPDB regulated 5V output current budget is adequate for DevKitC-32E and Stage 1 logic load.
- **Assumption:** Initial test environment is indoor flat-surface operation.
- **Assumption:** Stage 1 remains strictly manual-control first; autonomy remains out of scope.
