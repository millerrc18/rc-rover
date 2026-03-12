# Handoff Summary

_Last updated: 2026-03-11_

This document provides a quick snapshot of the current state of the project. It is intended for a brand new agent or session to regain context quickly.

## Current phase

Stage 0/1 hardware direction freeze

## Current objective

Lock the first base-platform choices tightly enough to begin sourcing parts and preparing Stage 1 assembly and firmware work.

## Known constraints

- Naming is temporary (`rc-rover`) and may change later.
- The project should avoid runaway scope; no autonomy, cameras, or advanced sensors in Stage 1.
- The base must stay modular enough to support encoders, telemetry, and future sensors.
- The repo is the durable project memory and must stay current.

## Open questions

- Which exact ESP32 board should be the standard dev board for the project?
- Should the first motor-driver path be Romi-native or a more generic driver path?
- Should the first manual-control interface be Bluetooth serial/app control or Wi-Fi web teleop?

## Next three high-priority actions

1. **Accept or refine the platform recommendation**  
   Review `docs/PLATFORM_SELECTION.md` and confirm the robotics-first differential-drive direction.

2. **Freeze the first BOM revision**  
   Review `hardware/bom-stage-0-1.csv` and replace any weak placeholders with exact part numbers where needed.

3. **Prepare the first wiring and firmware scaffold**  
   Create a Stage 1 wiring plan and a minimal firmware structure for motor control plus battery-voltage reporting.

## Key files to read

- `README.md`
- `AGENTS.md`
- `docs/PROJECT_STATE.md`
- `docs/PLATFORM_SELECTION.md`
- `docs/STAGE_1_ACCEPTANCE_TEST.md`
- `hardware/bom-stage-0-1.csv`
- `docs/NEXT_STEPS.md`
