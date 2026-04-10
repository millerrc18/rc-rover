# Project State

_Last updated: 2026-04-10_

This file is the canonical description of current project status.

## Current phase

**Stage 1 physical build — Phase 11 (first battery power-on) BLOCKED. Waiting on Romi Encoder Pair Kit (#3542) to connect motors to the motor driver board.**

## What exists

- Stage 1 hardware freeze: `docs/HARDWARE_ARCHITECTURE.md`, `docs/STAGE_1_WIRING.md`
- Production firmware: `firmware/stage1-esp32-baseline/` (BLE teleop, deadman, e-stop, battery ADC)
- Motor test firmware: `firmware/stage1-motor-test/` (standalone, no BLE required)
- Physical build guide: `docs/builds/stage1-rover-a-build.md` (with SVG diagrams)
- BOM: `hardware/bom-stage-0-1.csv`
- Procurement tracker: `docs/PROCUREMENT_STATUS.md`

## Hardware state

- **Phases 0–10 complete.** Chassis assembled, Romi board mounted, headers soldered, battery contacts soldered, 6-cell series jumper installed, ESP32 mounted, control signal wiring complete, voltage divider built, USB power-on test passed.
- **Phase 11 BLOCKED:** Motors are not connected to the motor driver board. The included female headers are designed for the Romi Encoder Pair Kit — bare motors don't plug in directly. Encoders ordered (Pololu #3542); will complete motor connection on arrival.
- **ESP32 #1 failed:** Original ESP32 stuck in DOWNLOAD_BOOT mode (GPIO0/BOOT button likely shorted). Replaced with a second ESP32-DevKitC-32E, which works correctly. Dead board set aside.
- Motor test firmware flashed and serial output confirmed on replacement ESP32.
- 6 AA NiMH batteries installed.

## Software state

Motor test firmware validated on replacement ESP32. Production firmware compiles but has not been flashed (will be flashed in Phase 12 after motor direction verification).

## Confirmed decisions

- Dev board: Espressif ESP32-DevKitC-32E
- Motor driver: Pololu Romi Motor Driver and Power Distribution Board (#3543)
- Motor connection: Romi Encoder Pair Kit (#3542) — plugs into existing female headers
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
