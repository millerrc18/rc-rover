# Project State

_Last updated: 2026-03-19_

This file is the canonical description of current project status.

## Current phase

**Stage 1 execution — parts arriving, build imminent.**

## What exists

- Stage 1 hardware freeze: `docs/HARDWARE_ARCHITECTURE.md`, `docs/STAGE_1_WIRING.md`
- Production firmware: `firmware/stage1-esp32-baseline/` (BLE teleop, deadman, e-stop, battery ADC)
- Motor test firmware: `firmware/stage1-motor-test/` (standalone, no BLE required)
- Physical build guide: `docs/builds/stage1-rover-a-build.md`
- BOM: `hardware/bom-stage-0-1.csv`
- Procurement tracker: `docs/PROCUREMENT_STATUS.md`

## Hardware state

- First batch of parts received (switches, resistors, Dupont kit, standoffs).
- ESP32, batteries, wiring items arriving tomorrow.
- Romi chassis (#3506) and Motor Driver board (#3543) arriving Saturday.
- No assembly, wiring, flashing, or bench testing has occurred.

## Software state

Both firmware projects compile but have not been validated on physical hardware.

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
