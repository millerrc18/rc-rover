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
