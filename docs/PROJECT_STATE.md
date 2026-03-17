# Project State

_Last updated: 2026-03-17_

This file is the canonical description of current project status.

## Current phase

**Stage 1 execution readiness (pre-procurement, pre-assembly, pre-bring-up)**

## Current objective

Begin real-world Stage 1 execution in the correct order: procure parts, inspect parts, assemble safely, then flash and run first bench bring-up.

## Summary of progress

- Platform direction is locked to a robotics-first differential-drive base.
- Stage 1 hardware and interface freeze artifacts exist and are cross-linked.
- Stage 1 execution package includes exact wiring/pin docs, firmware scaffold, and committed executable baseline and motor test projects:
  - `docs/STAGE_1_WIRING_DIAGRAM.md` (includes battery divider resistor values R1=20kΩ / R2=10kΩ)
  - `docs/STAGE_1_PIN_MAP.md` (includes GPIO14 boot-strapping note and GPIO33 conflict correction)
  - `docs/FIRMWARE_SCAFFOLD.md`
  - `firmware/stage1-esp32-baseline/` (production BLE teleop firmware)
  - `firmware/stage1-motor-test/` (standalone motor validation sketch, no BLE required)
- Stage 0/1 BOM has been cleaned for procurement readiness (correct blue Romi kit SKU, no duplicate included subcomponent buys in the initial order set).
- Bring-up support documents are prepared for future physical testing:
  - `docs/BLE_CONTROL_PROFILE.md`
  - `docs/BENCH_BRINGUP_LOG.md`
  - `docs/STAGE_1_TUNING.md` (includes battery ADC calibration procedure and ramp limiter note)
- Logic-power ambiguity is resolved in documentation:
  - Bench bring-up ESP32 power: USB-A to Micro-USB cable.
  - Untethered ESP32 power: Romi Motor Driver board regulated 5V to ESP32 5V pin.
- Physical assembly guide corrected and finalized at `docs/builds/stage1-rover-a-build.md`:
  - Targets Pololu Romi Motor Driver and Power Distribution Board (#3543) exclusively (previous version incorrectly targeted a DRV8833 breakout).
  - Uses the frozen GPIO pin map (GPIO25/26/27/**14**) throughout; previous GPIO33 error corrected.
  - Phase 7 provides both motor test sketch path and BLE app path for first motor validation.
- Multi-generation platform strategy is documented: Rover A / Mk1 active, Rover B / Mk2 and Rover C / Mk3 planned, Rover D / Mk4 long-term vision.
- Historical/superseded documents now carry explicit notices and are listed separately in `docs/INDEX.md`.

## Completed tasks

- Established documentation-driven memory system.
- Added platform selection and Stage 1 acceptance test artifacts.
- Frozen Stage 1 baseline architecture and interfaces.
- Created Stage 1 wiring diagram with continuity/polarity/pre-power checklists and explicit resistor values.
- Frozen exact ESP32 Stage 1 pin assignments including ADC/PWM conflict avoidance and GPIO14 boot-strapping constraint.
- Defined implementation-ready firmware scaffold (BLE teleop, deadman, e-stop, drive mix, battery ADC, failure states).
- Implemented first executable Stage 1 firmware baseline with safe startup, BLE control intake, differential mixing, deadman timeout, e-stop latch, and battery ADC serial reporting.
- Added standalone motor test sketch for no-BLE first hardware validation.
- Authored and corrected a complete phased Rover A Stage 1 physical build instruction guide targeting the correct hardware.
- Performed full-repo correctness audit; found and resolved 9 documentation issues (2 critical, 3 moderate, 4 minor).

## Open tasks

See `docs/NEXT_STEPS.md` for queue order. Immediate work is procurement from the corrected initial-order set, incoming inspection, and first physical assembly before any bench flashing/validation.

## Hardware state

- No Stage 1 parts have been ordered yet.
- No parts have been received or inspected yet.
- No assembly has started.
- No wiring has been performed on physical hardware.
- No firmware has been flashed to physical hardware.
- No bench bring-up session has occurred.

## Software state

Production firmware baseline exists in `firmware/stage1-esp32-baseline/` and is aligned to frozen Stage 1 pins and interfaces. Motor test sketch exists in `firmware/stage1-motor-test/`. Neither has been validated on physical hardware yet.

## Confirmed decisions now in effect

- Standard dev board: Espressif ESP32-DevKitC-32E.
- Primary motor-driver path: Pololu Romi Motor Driver and Power Distribution Board (#3543).
- Initial manual control: BLE teleop.
- Untethered ESP32 logic power: Romi Motor Driver board regulated 5V → ESP32 5V pin.
- Bench cable standard: USB-A to Micro-USB data cable.
- Battery divider: R1=20kΩ / R2=10kΩ (ratio 3.0×, matching `BATTERY_DIVIDER_RATIO = 3.0f` in firmware).
- GPIO14 accepted for right motor direction with LOW-init constraint; no pull-up to be added.
- Electric traction remains the core architecture; any hybrid concept is future-only serial range-extender planning and out of scope for Mk1/Mk2.

## Assumptions

- **Assumption:** Romi Motor Driver board regulated 5V output current budget is adequate for DevKitC-32E and Stage 1 logic load.
- **Assumption:** Initial test environment is indoor flat-surface operation.
- **Assumption:** Stage 1 remains strictly manual-control first; autonomy remains out of scope.
