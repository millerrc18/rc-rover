# Handoff Summary

_Last updated: 2026-03-17_

Quick snapshot for the next session.

## Current phase

Active: Rover A / Mk1 Stage 1 execution readiness — hardware arriving imminently.

## Current objective

Receive and inspect hardware, then execute Stage 1 build in phase order per `docs/builds/stage1-rover-a-build.md`.

## What just changed

- Recorded multi-platform control surface vision and architecture decisions.
- Long-term primary control surface target: handheld physical controller with integrated screen and joysticks (Pi Zero class, Wi-Fi transport).
- Also targeting web dashboard and mobile app as earlier control surfaces.
- Decided Wi-Fi transport will be added in Stage 2 alongside BLE using the same T,R,H,E,C protocol.
- Added control surface items to BACKLOG.

## Hardware status

- ESP32, wiring/power items, and most parts arriving tomorrow.
- Romi chassis kit (#3506) and Romi Motor Driver board (#3543) arriving Saturday.
- Tomorrow's tasks: verify ESP32 flashes, test toolchain with motor test sketch, inventory parts, set up BLE app.

## Constraints to preserve

- Stage 1 hardware baseline is fixed. No scope changes until Stage 1 acceptance is complete.
- GPIO14 is the frozen right motor direction pin. No external pull-up to be added.
- Battery divider: R1=20kΩ / R2=10kΩ. Firmware `BATTERY_DIVIDER_RATIO = 3.0f` matches this.
- Wi-Fi transport and all control surfaces are Stage 2+ work only.

## Next three high-priority actions

1. Tomorrow: verify ESP32 enumerates over USB, flash `firmware/stage1-motor-test/`, inventory arriving parts into `docs/PROCUREMENT_STATUS.md`.
2. Saturday: assemble Romi chassis per `docs/builds/stage1-rover-a-build.md` Phase 1–5.
3. Saturday: first power-on check, then motor test, then reflash production BLE baseline.

## Key files for next session

- `docs/PROCUREMENT_STATUS.md` — update as parts arrive
- `docs/builds/stage1-rover-a-build.md` — live build checklist
- `docs/STAGE_1_WIRING_DIAGRAM.md` — wiring reference
- `firmware/stage1-motor-test/` — flash first
- `firmware/stage1-esp32-baseline/` — production firmware
- `docs/BENCH_BRINGUP_LOG.md` — log bring-up session
- `docs/STAGE_1_ACCEPTANCE_TEST.md` — pass/fail criteria
