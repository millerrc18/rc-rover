# Project State

_Last updated: 2026-03-20_

This file is the canonical description of current project status.

## Current phase

**Stage 1 physical build in progress — Phase 0 complete, entering Phase 1 (soldering).**

## What exists

- Stage 1 hardware freeze: `docs/HARDWARE_ARCHITECTURE.md`, `docs/STAGE_1_WIRING.md`
- Production firmware: `firmware/stage1-esp32-baseline/` (BLE teleop, deadman, e-stop, battery ADC)
- Motor test firmware: `firmware/stage1-motor-test/` (standalone, no BLE required)
- Physical build guide: `docs/builds/stage1-rover-a-build.md` (with SVG diagrams)
- BOM: `hardware/bom-stage-0-1.csv`
- Procurement tracker: `docs/PROCUREMENT_STATUS.md`

## Hardware state

- **All Stage 1 parts received.** See `docs/PROCUREMENT_STATUS.md` for per-item status.
- ESP32-DevKitC-32E verified on physical hardware:
  - CP2102 driver installed (Windows), enumerated as COM4.
  - Motor test sketch flashed and serial output confirmed.
  - Production firmware compiles successfully.
- **Phase 0 (toolchain + ESP32 verification): COMPLETE.**
- Phase 1 (solder headers to Romi board): next.
- No soldering, assembly, or wiring performed yet.

## Software state

Motor test firmware validated on physical ESP32 hardware. Production firmware compiles but has not been flashed to hardware yet (will be flashed in Phase 12 after motor direction verification).

## Confirmed decisions

- Dev board: Espressif ESP32-DevKitC-32E
- Motor driver: Pololu Romi Motor Driver and Power Distribution Board (#3543)
- Manual control: BLE teleop
- ESP32 power (untethered): Romi board regulated 5V → ESP32 5V pin
- ESP32 power (bench): USB-A to Micro-USB
- Battery divider: R1=22kΩ / R2=10kΩ (ratio 3.2×, firmware `BATTERY_DIVIDER_RATIO = 3.2f`)
- GPIO14 for right motor direction (LOW-init, no pull-up)
- Electric traction only; hybrid is future-only planning

## Assumptions

- Romi board 5V output is sufficient for ESP32 + Stage 1 logic load.
- Test environment is indoor flat surfaces.
- Stage 1 is strictly manual control; autonomy is out of scope.
