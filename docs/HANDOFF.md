# Handoff Summary

_Last updated: 2026-03-17_

Quick snapshot for the next session.

## Current phase

Active: Rover A / Mk1 Stage 1 execution readiness (pre-procurement and pre-assembly)

## Current objective

Keep immediate execution focus unchanged: procurement -> inspection -> assembly -> bring-up.

## What just changed

- Performed a full-repo correctness audit and resolved 9 documentation issues (2 critical, 3 moderate, 4 minor).
- **Critical:** Rewrote `docs/builds/stage1-rover-a-build.md` to target the correct board (Pololu Romi Motor Driver and Power Distribution Board #3543). Previous version incorrectly described a DRV8833 breakout with wrong terminal names and wiring steps.
- **Critical:** Corrected pin conflict — GPIO33 in the old build guide replaced with the correct frozen pin GPIO14 for M2DIR. All docs and firmware now consistently use GPIO14.
- **Moderate:** Added GPIO14 boot-strapping constraint and safe-use rules to `docs/STAGE_1_PIN_MAP.md`.
- **Moderate:** Added battery divider resistor values (R1=20kΩ / R2=10kΩ) and verification table to `docs/STAGE_1_WIRING_DIAGRAM.md`.
- **Moderate:** Added `firmware/stage1-motor-test/` — a standalone 8-step motor test sketch requiring no BLE app. Build guide Phase 7 now directs builders to flash this first, then the production baseline.
- **Minor:** Added battery ADC calibration procedure and ramp limiter note to `docs/STAGE_1_TUNING.md`.
- **Minor:** Added superseded/historical notices to the four orphaned `rc-rover-*.md` docs.
- **Minor:** Updated `docs/INDEX.md` with a Historical Reference section, motor test firmware entry, and corrected build guide annotation.
- All changes committed and pushed to GitHub (`millerrc18/rc-rover`, main branch).

## Constraints to preserve

- Keep Stage 1 hardware baseline fixed (Romi chassis + Romi Motor Driver board #3543 + ESP32-DevKitC-32E + BLE teleop).
- Do not imply any physical build progress until procurement/inspection/assembly actually occur.
- GPIO14 is the frozen right motor direction pin. No external pull-up to be added to this line.
- Battery divider is frozen at R1=20kΩ / R2=10kΩ. Firmware `BATTERY_DIVIDER_RATIO = 3.0f` matches this.
- Mk2/Mk3/Mk4 are defined planning targets and remain not started/out of scope for current execution.
- Any future hybrid concept is constrained to a serial-hybrid/range-extender outdoor module and is out of scope for Mk1/Mk2 execution.

## Open questions

- What measured deadman timeout feels safest while still drivable on real hardware?
- Do we need non-zero PWM floor after first wheel-off-ground tests?
- Should low-voltage handling remain warning-only or add duty-cap in Stage 1.1?
- Will GPIO14 cause any boot issues on actual hardware? (Fallback is GPIO33 + firmware constant update.)

## Next three high-priority actions

1. Place initial Stage 0/1 **buy-now** order from `hardware/bom-stage-0-1.csv` and update `docs/PROCUREMENT_STATUS.md`.
2. Receive and inspect critical parts (ESP32 board, Romi Motor Driver board, power-path items) and log outcomes.
3. Begin controlled assembly using `docs/builds/stage1-rover-a-build.md`, flash `firmware/stage1-motor-test/` first for motor direction validation, then reflash `firmware/stage1-esp32-baseline/` and run first logged bench bring-up.

## Key files to read first next session

- `docs/PROJECT_STATE.md`
- `docs/NEXT_STEPS.md`
- `docs/PROCUREMENT_STATUS.md`
- `hardware/bom-stage-0-1.csv`
- `docs/builds/stage1-rover-a-build.md`
- `docs/STAGE_1_WIRING_DIAGRAM.md`
- `docs/STAGE_1_PIN_MAP.md`
- `firmware/stage1-motor-test/` (flash first for bring-up)
- `firmware/stage1-esp32-baseline/` (production firmware)
- `docs/BENCH_BRINGUP_LOG.md`
- `docs/STAGE_1_ACCEPTANCE_TEST.md`
