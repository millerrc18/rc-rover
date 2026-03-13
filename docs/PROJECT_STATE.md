# Project State

_Last updated: 2026-03-12_

This file is the canonical description of current project status.

## Current phase

**Stage 1 wiring + firmware bring-up package complete (ready for bench execution)**

## Current objective

Execute physical wiring and initial firmware bring-up using the now-frozen Stage 1 package.

## Summary of progress

- Platform direction is locked to a robotics-first differential-drive base.
- Stage 1 hardware and interface freeze artifacts exist and are cross-linked.
- Stage 1 execution package now includes exact wiring, exact pin map, and firmware scaffold:
  - `docs/STAGE_1_WIRING_DIAGRAM.md`
  - `docs/STAGE_1_PIN_MAP.md`
  - `docs/FIRMWARE_SCAFFOLD.md`
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

## Open tasks

See `docs/NEXT_STEPS.md` for queue order. Immediate work shifts to physical assembly, flashing initial firmware, and acceptance-test evidence collection.

## Hardware state

No full rover assembled yet, but wiring and power-path docs are now explicit enough for a real bench bring-up session.

## Software state

No production firmware committed yet. Firmware behavior is now fully scaffolded and pin-frozen for Stage 1 implementation.

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
