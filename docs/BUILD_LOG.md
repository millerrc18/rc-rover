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

## 2026-03-17 — First parts received; resistor substitution applied

- SPST switches, Dupont connector kit + crimper, M3 standoffs, and resistor assortment arrived.
- Confirmed 10kΩ present. 22kΩ available; 20kΩ not in assortment — accepted as substitution.
- Updated `BATTERY_DIVIDER_RATIO` in `firmware/stage1-esp32-baseline/src/main.cpp` from `3.0f` to `3.2f` to match actual R1=22kΩ / R2=10kΩ as-built divider.
- Updated `docs/STAGE_1_WIRING_DIAGRAM.md` to reflect R1=22kΩ, 3.2× ratio, and corrected ADC voltage verification table.
- Updated `docs/PROCUREMENT_STATUS.md` with received items, substitution note, and M3-only standoff note (ESP32 mounting hole workaround documented).
- Recorded substitution decision in `docs/DECISIONS.md`.
- Romi chassis and motor driver board arriving Saturday. ESP32, batteries, and remaining wiring items arriving tomorrow.

## 2026-03-17 — Build guide comprehensive review and rewrite

Reviewed build guide against Pololu product documentation and identified 11 gaps. Full rewrite performed.

Critical gaps fixed:
- Soldering is mandatory, not optional. Three distinct soldering tasks exist in a specific order: motor headers and control headers (bench, before mounting), battery contacts (after mounting), and 6-cell series jumper.
- Phase ordering was wrong. Board preparation must happen before chassis assembly. Corrected to 13 phases in correct dependency order.
- Motor connections require soldering female headers to the board before mounting — not auto-connecting on snap-in.
- 6-cell series jumper not previously mentioned. Without it the battery pack is split and the rover has no power.
- Romi board has a built-in latching power button — not previously documented. Power does not flow until button is pressed.

Other gaps fixed:
- Tools section now lists soldering iron as mandatory with temperature guidance; adds solder, tip cleaner, PCB holder.
- Added Phase 0: PlatformIO toolchain install and ESP32 pre-verification before any assembly.
- Added Phase 7: dedicated ESP32 logic power wiring step (5V from Romi board to ESP32 5V pin).
- Added Phase 8: battery voltage divider construction with explicit component values (R1=22kΩ / R2=10kΩ).
- ESP32 foam tape mounting workaround documented (M2 standoffs not available).
- R1 value corrected to 22kΩ throughout (was 20kΩ in wiring reference section).
- Consumables list added to parts section (male headers, series jumper wire, resistors, perfboard).

## 2026-03-19 — Documentation consolidation and firmware fixes

Full-repo review identified documentation sprawl (40+ files for a pre-hardware project) and several correctness issues. Performed structural consolidation and bug fixes.

**Structural changes:**
- Merged `START_HERE.md`, `GLOSSARY.md`, and `PROJECT_CHARTER.md` into `README.md` as single entry point.
- Merged `INTERFACE_MAP.md` into `HARDWARE_ARCHITECTURE.md`.
- Merged `STAGE_1_PIN_MAP.md` and `STAGE_1_WIRING_DIAGRAM.md` into new `STAGE_1_WIRING.md`.
- Moved 7 superseded/historical files to `docs/archive/` (old roadmap, platform matrix, concept sheet, system arch block diagram, firmware scaffold, build plan, platform selection).
- Removed `docs/quality/` logs (redundant with BUILD_LOG) and `docs/templates/` (unused overhead).
- Removed `docs/INDEX.md` (replaced by repo layout in README).
- Simplified `AGENTS.md` to reduce mandatory end-of-task file count and remove reference to deleted files.

**Bug fixes:**
- Fixed stale R1=20kΩ / ratio 3.0× references in `PROJECT_STATE.md`, `NEXT_STEPS.md`, and `HANDOFF.md`. Correct as-built values: R1=22kΩ, ratio 3.2×, firmware `BATTERY_DIVIDER_RATIO = 3.2f`.
- Added 8-sample moving average to `BatteryAdc::sample()` in production firmware. Documentation claimed this existed but implementation was a direct overwrite.
- Added thread-safety note to global state variables in production firmware (BLE callback vs loop() task boundary).
- Added explicit DIR pin convention comment to motor test sketch.
- Added root `.gitignore` for OS artifacts, editor files, and PlatformIO build dirs.
- Updated all cross-file references to use new merged filenames.

**Net result:** Documentation reduced from ~40 files to ~22 active files. Historical docs preserved in `docs/archive/`.

## 2026-03-19 — Build guide enhanced with diagrams and detailed Phase 0

- Created `docs/builds/images/` directory with three SVG diagrams:
  - `phase0-setup.svg` — Phase 0 physical setup and terminal commands
  - `wiring-connections.svg` — all 6 wires + voltage divider circuit
  - `build-phase-order.svg` — phase sequence overview with ordering rules
- Rewrote Phase 0 from 15 lines to a comprehensive step-by-step guide with:
  - OS-specific serial port verification (Windows/Mac/Linux)
  - Full expected terminal output for each command
  - BOOT button hold procedure for upload issues
  - Explicit completion checklist (5 items)
  - Troubleshooting table covering 7 common failure modes
- Added diagram references to build guide Phase 6 (wiring) and build overview.

## 2026-03-20 — All parts received; Phase 0 complete

- All remaining Stage 1 parts arrived and marked received in `docs/PROCUREMENT_STATUS.md`.
- ESP32-DevKitC-32E verified on physical hardware:
  - Windows required CP2102 driver installation (Silicon Labs). Board enumerates as COM4.
  - PlatformIO CLI not in PowerShell PATH — resolved by using PlatformIO's built-in terminal in VS Code.
  - Motor test sketch (`firmware/stage1-motor-test/`) flashed and serial output confirmed (all 8 steps).
  - Production firmware (`firmware/stage1-esp32-baseline/`) compiles successfully.
- Phase 0 completion criteria: all 5 items passed.
- Phase 1 (soldering) is next. Builder is first-time solderer.

## 2026-03-20 — Build guide updated with Pololu photo references

- Added "Visual references" section to build guide overview with links to three key Pololu pages:
  - Romi Chassis Assembly Guide (pololu.com/docs/0J68/4)
  - Romi Chassis Power Options / series jumper photo (pololu.com/docs/0J68/all Section 5)
  - Motor Driver Board product page with pin layout (pololu.com/product/3543)
- Added photo reference callouts (📷) to Phases 1, 2, 3, 4, 6, and 12, pointing to the specific Pololu page sections with relevant photos for each step.
- Added DRV8838 DIR convention note to Phase 12: Pololu docs say DIR LOW = forward, but firmware uses DIR HIGH = forward. Motor test will reveal actual direction; fix in firmware if needed.
