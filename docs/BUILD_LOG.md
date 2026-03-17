# Build Log

This log records every meaningful modification or work session on the project.  Each entry should include a date and a concise description of what changed.

## 2026‑03‑11

- Bootstrapped the repository with documentation and memory system.
- Added `README.md`, `AGENTS.md` and `.codex/config.toml`.
- Created the `docs/` directory with initial state, next steps, decisions, architecture, build log, learnings, backlog, glossary, handoff, project charter, roadmap, contributing and index.
- Added templates for session notes, architecture decisions, experiments, milestone reviews and task briefs.
- Added `docs/PLATFORM_SELECTION.md` to compare platform options and force a Stage 0/1 recommendation.
- Added `hardware/bom-stage-0-1.csv` with a first-pass hardware bill of materials.
- Added `docs/STAGE_1_ACCEPTANCE_TEST.md` to define the first hardware milestone.
- Updated state, next steps, decisions, and handoff docs to reflect the new hardware direction.

## 2026-03-12

- Created Stage 1 hardware freeze package docs: `docs/HARDWARE_ARCHITECTURE.md`, `docs/INTERFACE_MAP.md`, and `docs/STAGE_1_BUILD_PLAN.md`.
- Strengthened `hardware/bom-stage-0-1.csv` into a first-pass sourced BOM with clearer recommended parts and rationale.
- Explicitly froze three key Stage 1 decisions: exact ESP32 board, motor-driver path, and initial manual-control method.
- Updated canonical memory docs (`PROJECT_STATE`, `NEXT_STEPS`, `HANDOFF`, `ARCHITECTURE`, `ROADMAP`, `INDEX`) for consistency with active Stage 0/1 hardware-freeze work.
- Added quality tracking logs under `docs/quality/` for issue/improvement evidence capture.
- Added Stage 1 execution-ready bring-up artifacts:
  - `docs/STAGE_1_WIRING_DIAGRAM.md`
  - `docs/STAGE_1_PIN_MAP.md`
  - `docs/FIRMWARE_SCAFFOLD.md`
- Resolved logic-power ambiguity by freezing untethered ESP32 path as `MPDB regulated 5V -> ESP32 5V pin`, and bench path as USB-powered bring-up.
- Updated BOM to freeze USB cable type for ESP32-DevKitC-32E as USB-A to Micro-USB data cable.
- Synchronized architecture, interface map, state, next steps, handoff, and index docs with the new bring-up package.


## 2026-03-13

- Added first executable Stage 1 ESP32 firmware baseline under `firmware/stage1-esp32-baseline/` (PlatformIO + Arduino).
- Implemented baseline runtime behavior: safe startup motor stop, BLE teleop packet intake, differential drive mixing, deadman timeout, e-stop latch/clear, and battery ADC serial reporting.
- Added `docs/BLE_CONTROL_PROFILE.md` to freeze first-pass BLE control message format and UUID map.
- Added `docs/BENCH_BRINGUP_LOG.md` as reusable run log template for USB/battery/safety checks.
- Added `docs/STAGE_1_TUNING.md` with initial tuning constants and bench test capture table.
- Updated canonical state docs (`PROJECT_STATE`, `NEXT_STEPS`, `HANDOFF`, `INDEX`) and quality logs to reflect implementation readiness.

## 2026-03-13

- Realigned canonical project status docs to match physical reality: no procurement, no assembly/wiring, no hardware flashing, and no bench bring-up completed yet.
- Updated `PROJECT_STATE`, `NEXT_STEPS`, and `HANDOFF` to move immediate execution back to pre-procurement and pre-assembly readiness.
- Converted `BENCH_BRINGUP_LOG` framing to explicit future-use template language.
- Added `docs/PROCUREMENT_STATUS.md` to track ordered/received/inspected status for Stage 0/1 parts.
- Updated `docs/INDEX.md` and quality logs to reflect the documentation correction and new tracker.


## 2026-03-14

- Cleaned `hardware/bom-stage-0-1.csv` to make Stage 0/1 procurement-ready and eliminate duplicate Romi subcomponent purchases when using the full Romi kit.
- Corrected the blue Romi chassis kit reference to `Pololu #3506`.
- Relabeled Romi motors/wheels/caster as optional spare-only and added explicit "included in kit" battery-holder line item.
- Reworked `docs/PROCUREMENT_STATUS.md` into clear sections: buy-now initial order, included-with-kit no-buy items, and later-stage items.
- Updated canonical state/handoff/next-step docs and quality logs to reflect corrected procurement baseline.

## 2026-03-17

- Reviewed core context files (`README.md`, `AGENTS.md`, `docs/START_HERE.md`, `docs/HANDOFF.md`, `docs/PROJECT_STATE.md`, `docs/NEXT_STEPS.md`) before making changes.
- Expanded `docs/ROADMAP.md` with a full multi-generation platform strategy while preserving Stage 0-Stage 6 structure and keeping Stage 1 baseline unchanged.
- Added platform definitions (Rover A/Mk1 through Rover D/Mk4), target envelopes, duration-based planning estimates, skill outcomes, migration triggers, and a concise roadmap summary table.
- Added cross-generation architecture guidance in `docs/ARCHITECTURE.md` clarifying reusable patterns and fixed Stage 1 constraints.
- Recorded new accepted platform-strategy decisions in `docs/DECISIONS.md`.
- Updated handoff/state/queue docs to reflect that Mk2/Mk3/Mk4 are defined but not started and remain out of current execution scope.
- Updated quality logs for traceability of this documentation change set.

## 2026-03-17

- Reviewed roadmap/architecture/decisions/handoff docs and added a concise future-facing hybrid propulsion note set without changing current execution scope.
- Updated architecture and roadmap docs to state electric-drive-first direction and document future-only serial-hybrid/range-extender constraints.
- Recorded an accepted decision preserving electric traction as core mobility architecture across generations.
- Updated handoff/state/next-step and quality logs to keep new-agent context clear and consistent.

## 2026-03-17

- Reviewed required context docs before editing (`README.md`, `docs/START_HERE.md`, `docs/HANDOFF.md`, `docs/PROJECT_STATE.md`, `docs/NEXT_STEPS.md`, `docs/ARCHITECTURE.md`, `docs/BUILD_LOG.md`).
- Created `docs/builds/stage1-rover-a-build.md` as a complete, highly detailed, beginner-friendly Rover A Stage 1 physical assembly guide for live build use.
- Included mandatory phased assembly workflow (mechanical, layout, core wiring, ESP32 control wiring, safe power setup, first power-on, and motor test) with explicit safety checks and stop conditions.
- Added wiring-reference summary, common-mistakes section, completion checklist, and local image placeholders with exact descriptions of expected visuals.
- Updated canonical state docs and quality logs to reflect availability of the new first-build assembly playbook.

## 2026-03-17 — Documentation correctness audit and fixes

Reviewed the full repository for correctness issues. Found and corrected nine issues across critical, moderate, and minor severity levels.

**Critical fixes:**
- Rewrote `docs/builds/stage1-rover-a-build.md` to target the correct board (Pololu Romi Motor Driver and Power Distribution Board #3543) throughout. The previous version was written for a generic DRV8833 breakout with different terminal names (`AIN1/AIN2/BIN1/BIN2`, `OUT1-OUT4`) that do not exist on the Romi board.
- Corrected the pin map conflict in the build guide: Phase 4 previously specified GPIO33 for M2DIR. The correct frozen pin is GPIO14. All Stage 1 docs, firmware, and the build guide now consistently use GPIO14.

**Moderate fixes:**
- Added GPIO14 boot-strapping risk note and safe-use constraints to `docs/STAGE_1_PIN_MAP.md`.
- Added explicit battery voltage divider resistor values (R1=20kΩ, R2=10kΩ) and derivation to `docs/STAGE_1_WIRING_DIAGRAM.md`, including a verification table at key battery voltages.
- Added `firmware/stage1-motor-test/` — a minimal motor test sketch that runs a fixed 8-step sequence with no BLE required. Provides the "simple motor test sketch" referenced in the build guide Phase 7 but previously missing.
- Updated the build guide Phase 7 to explain both the motor test sketch and the BLE app path (nRF Connect / LightBlue), including the deadman timeout constraint.

**Minor fixes:**
- Added battery ADC calibration procedure and ramp limiter documentation note to `docs/STAGE_1_TUNING.md`.
- Added superseded/historical notices to `docs/rc-rover-roadmap.md`, `docs/rc-rover-platform-decision-matrix.md`, `docs/rc-rover-concept-render-sheet.md`, and `docs/rc-rover-system-architecture-block-diagram.md`.
- Updated `docs/INDEX.md` with a new Historical Reference section, motor test firmware entry, and corrected build guide board target annotation.

## 2026-03-17 — Control surface vision and architecture decisions

- Recorded multi-platform control surface vision: web dashboard, mobile app, and handheld physical controller with integrated screen as the primary long-term target.
- Recorded decision to add Wi-Fi transport in Stage 2 alongside BLE using the same T,R,H,E,C protocol.
- Recorded physical controller architecture direction: Pi Zero class + touchscreen + joysticks over Wi-Fi.
- Added control surface items to BACKLOG.
- Updated DECISIONS.md (3 new entries), HANDOFF.md, and NEXT_STEPS.md to reflect the new direction.
