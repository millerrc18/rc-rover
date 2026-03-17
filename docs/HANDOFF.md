# Handoff Summary

_Last updated: 2026-03-17_

Quick snapshot for the next session.

## Current phase

Active: Rover A / Mk1 Stage 1 execution readiness (pre-procurement and pre-assembly)

## Current objective

Keep immediate execution focus unchanged: procurement -> inspection -> assembly -> bring-up.

## What just changed

- Added a clear multi-generation platform strategy to the roadmap (Rover A/Mk1 through Rover D/Mk4).
- Documented payload/tow/runtime target envelopes, duration-based planning timelines, migration triggers, and per-platform skill goals.
- Added cross-generation architecture guidance clarifying what is reusable vs what remains fixed in Stage 1.
- Recorded accepted decisions that Stage 1 Romi is the learning baseline and Mk2/Mk3/Mk4 are future targets only.

## Constraints to preserve

- Keep Stage 1 hardware baseline fixed (Romi + ESP32-DevKitC-32E + Romi motor board + BLE teleop path).
- Do not imply any physical build progress until procurement/inspection/assembly actually occur.
- Mk2/Mk3/Mk4 are defined planning targets and remain not started/out of scope for current execution.

## Open questions

- What measured deadman timeout feels safest while still drivable on real hardware?
- Do we need non-zero PWM floor after first wheel-off-ground tests?
- Should low-voltage handling remain warning-only or add duty-cap in Stage 1.1?

## Next three high-priority actions

1. Place initial Stage 0/1 **buy-now** order from `hardware/bom-stage-0-1.csv` and update `docs/PROCUREMENT_STATUS.md`.
2. Receive and inspect critical parts (ESP32 board, motor board, power-path items) and log outcomes.
3. Begin controlled assembly/wiring, then flash `firmware/stage1-esp32-baseline/` and run first logged bench bring-up.

## Key files to read first next session

- `docs/PROJECT_STATE.md`
- `docs/NEXT_STEPS.md`
- `docs/ROADMAP.md`
- `docs/PROCUREMENT_STATUS.md`
- `hardware/bom-stage-0-1.csv`
- `docs/STAGE_1_BUILD_PLAN.md`
- `docs/STAGE_1_WIRING_DIAGRAM.md`
- `docs/STAGE_1_PIN_MAP.md`
- `firmware/stage1-esp32-baseline/`
- `docs/BENCH_BRINGUP_LOG.md`
- `docs/STAGE_1_ACCEPTANCE_TEST.md`
