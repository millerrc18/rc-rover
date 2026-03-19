# Handoff Summary

_Last updated: 2026-03-19_

## Current phase

Stage 1 execution — hardware arriving, build imminent.

## What just changed

- Consolidated documentation: merged 7 files into parent docs, moved 7 superseded files to `docs/archive/`, removed unused templates and quality logs.
- Fixed stale 20kΩ/3.0f references across all living docs (actual as-built: R1=22kΩ, ratio 3.2×).
- Added battery ADC moving average to firmware (8-sample window, matching doc claims).
- Added root `.gitignore`.
- Added thread-safety note and DIR convention comment to firmware.

## Hardware status

- First parts received: SPST switches, Dupont kit + crimper, M3 standoffs, resistor assortment (22kΩ confirmed, 10kΩ confirmed).
- ESP32, batteries, wiring items arriving tomorrow.
- Romi chassis (#3506) and Motor Driver board (#3543) arriving Saturday.

## Constraints

- Stage 1 hardware baseline is fixed. No scope changes until acceptance complete.
- GPIO14 is the frozen right motor direction pin. No pull-up.
- Battery divider: R1=22kΩ / R2=10kΩ, firmware `BATTERY_DIVIDER_RATIO = 3.2f`.
- Wi-Fi and control surfaces are Stage 2+ only.

## Next three actions

1. Tomorrow: verify ESP32 over USB, flash motor test sketch, inventory parts.
2. Saturday: assemble Romi chassis per `docs/builds/stage1-rover-a-build.md` Phases 1–5.
3. Saturday: first power-on, motor test, reflash production BLE baseline.

## Key files

- `docs/PROCUREMENT_STATUS.md` — update as parts arrive
- `docs/builds/stage1-rover-a-build.md` — live build checklist
- `docs/STAGE_1_WIRING.md` — wiring/pin reference and checklists
- `firmware/stage1-motor-test/` — flash first
- `firmware/stage1-esp32-baseline/` — production firmware
- `docs/BENCH_BRINGUP_LOG.md` — log bring-up session
- `docs/STAGE_1_ACCEPTANCE_TEST.md` — pass/fail criteria
