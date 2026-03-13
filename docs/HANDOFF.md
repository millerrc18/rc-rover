# Handoff Summary

_Last updated: 2026-03-13_

Quick snapshot for the next session.

## Current phase

Stage 1 execution readiness; pre-procurement and pre-assembly

## Current objective

Start physical execution from zero hardware progress: order parts, receive/inspect, assemble, then flash and run first bench bring-up.

## What just changed

- Realigned repository status docs to reflect actual physical reality:
  - no parts ordered,
  - no assembly/wiring,
  - no hardware flashing,
  - no bench bring-up performed yet.
- Reordered immediate task queue to start with procurement and receiving inspection.
- Added procurement tracker: `docs/PROCUREMENT_STATUS.md`.
- Clarified that firmware baseline exists but is not yet validated on physical hardware.
- Updated bench bring-up log framing to future-use template language.

## Constraints to preserve

- Keep Stage 1 simple and buildable.
- Differential-drive robotics-first direction is fixed.
- ESP32-DevKitC-32E + Romi motor board baseline is fixed.
- No autonomy/camera/lidar scope in Stage 1.

## Open questions

- What measured deadman timeout feels safest while still drivable on real hardware?
- Do we need non-zero PWM floor after first wheel-off-ground tests?
- Should low-voltage handling remain warning-only or add duty-cap in Stage 1.1?

## Next three high-priority actions

1. Place initial Stage 0/1 parts orders from `hardware/bom-stage-0-1.csv` and update `docs/PROCUREMENT_STATUS.md`.
2. Receive and inspect critical parts (ESP32 board, motor board, power-path items) and log outcomes.
3. Begin controlled assembly/wiring, then flash `firmware/stage1-esp32-baseline/` and run first logged bench bring-up.

## Key files to read first next session

- `docs/PROJECT_STATE.md`
- `docs/NEXT_STEPS.md`
- `docs/PROCUREMENT_STATUS.md`
- `hardware/bom-stage-0-1.csv`
- `docs/STAGE_1_BUILD_PLAN.md`
- `docs/STAGE_1_WIRING_DIAGRAM.md`
- `docs/STAGE_1_PIN_MAP.md`
- `firmware/stage1-esp32-baseline/`
- `docs/BENCH_BRINGUP_LOG.md`
- `docs/STAGE_1_ACCEPTANCE_TEST.md`
