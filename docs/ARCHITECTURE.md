# Architecture

_Last updated: 2026-03-17_

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
- Executable Stage 1 firmware baseline now lives at `firmware/stage1-esp32-baseline/`.

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


## Cross-Generation Architecture

Stage 1 hardware is intentionally fixed to protect execution reliability and avoid scope creep during first physical bring-up.

The architecture is designed to be portable across chassis generations (Mk1 -> Mk4). As platforms scale, these elements should remain reusable:

- Firmware patterns (control loop, command handling, safety state handling)
- Safety behaviors (deadman timeout, e-stop semantics, startup-safe defaults)
- Interface mapping discipline (pin/path mapping and explicit signal ownership)
- Telemetry structure (battery/runtime/status reporting conventions)
- Documentation-driven memory system (`PROJECT_STATE`, `NEXT_STEPS`, decisions, logs)


This enables hardware evolution without losing operational continuity or documentation quality.

### Future architecture notes

#### Future Outdoor Power Extension

- All current and near-term rover generations remain electric-drive-first.
- Hybrid propulsion is out of scope for Rover A / Mk1 and Rover B / Mk2.
- If a hybrid approach is explored in later generations, treat it as a **serial-hybrid / range-extender** architecture:
  - Electric motors remain the only wheel-drive actuators.
  - Any gasoline engine is an outdoor-only generator/power module, not a direct mechanical drive path.
  - Indoor operation remains battery-electric only.
