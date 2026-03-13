# Architecture

_Last updated: 2026-03-12_

This document describes the current and planned architecture for `rc-rover`.

## Current architecture (frozen for Stage 1)

Stage 1 architecture is now defined and intentionally minimal:

- Differential-drive Romi-class rover base
- ESP32-DevKitC-32E microcontroller board
- Romi-native motor driver/power distribution board
- AA NiMH battery path with inline fuse and main switch
- Explicit dual power mode for ESP32:
  - bench USB power via USB-A to Micro-USB
  - untethered 5V from motor board regulator into ESP32 5V pin
- BLE manual teleoperation with deadman timeout and stop behavior
- Basic battery voltage measurement via ADC

Detailed references:
- `docs/HARDWARE_ARCHITECTURE.md`
- `docs/INTERFACE_MAP.md`
- `docs/STAGE_1_WIRING_DIAGRAM.md`
- `docs/STAGE_1_PIN_MAP.md`
- `docs/FIRMWARE_SCAFFOLD.md`
- `docs/STAGE_1_BUILD_PLAN.md`

## Stage progression (unchanged direction)

1. **Stage 0 – Rolling chassis**
2. **Stage 1 – Manual remote control (active focus)**
3. **Stage 2 – Basic telemetry**
4. **Stage 3 – First obstacle sensor**
5. **Stage 4 – Motion sensing**
6. **Stage 5 – Closed-loop control**
7. **Stage 6 – Advanced autonomy (future)**

## Architecture principles for current phase

- Minimize integration complexity before adding features.
- Keep interfaces explicit and documented for reproducibility.
- Reserve expansion points (encoders, I2C sensor path, telemetry channels) without implementing them prematurely.
