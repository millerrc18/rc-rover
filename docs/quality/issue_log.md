# Quality Issue Log

## 2026-03-12

- **Issue:** `docs/PROJECT_STATE.md` lagged active repository state and still framed work as bootstrap.
- **Impact:** Could cause incorrect task prioritization and duplicated bootstrap effort.
- **Resolution:** Updated canonical state to Stage 0/1 hardware-freeze status and synchronized related docs.
- **Evidence:** Documentation consistency review across `PROJECT_STATE`, `HANDOFF`, `NEXT_STEPS`, `ROADMAP`, and BOM updates in this change set.

- **Issue:** Stage 1 documentation still had ambiguous ESP32 untethered logic-power path and board-dependent USB connector wording.
- **Impact:** Could cause wrong cable purchase, wiring errors, and delayed bench bring-up.
- **Resolution:** Added explicit power-mode definitions, exact wiring doc, and frozen BOM entries for logic-power harness and USB-A to Micro-USB cable.
- **Evidence:** Cross-document updates in `HARDWARE_ARCHITECTURE`, `INTERFACE_MAP`, new Stage 1 wiring/pin docs, and BOM revision.


## 2026-03-13

- **Issue:** Repository had Stage 1 firmware scaffold only and no executable firmware baseline for immediate bench bring-up.
- **Impact:** Bench validation and acceptance testing could not be performed from repo contents alone.
- **Resolution:** Added executable firmware project and aligned BLE/tuning/bring-up docs to implementation details.
- **Evidence:** `firmware/stage1-esp32-baseline/`, `docs/BLE_CONTROL_PROFILE.md`, `docs/BENCH_BRINGUP_LOG.md`, `docs/STAGE_1_TUNING.md`.

- **Issue:** Repository narrative implied active bench validation despite zero physical execution (no ordering, assembly, wiring, flashing, or bring-up).
- **Impact:** Could cause contributors to skip required procurement/inspection steps and misreport project maturity.
- **Resolution:** Corrected canonical status/handoff/next-step docs, reframed bench log as future-use, and added explicit procurement tracker.
- **Evidence:** Cross-doc consistency check via `cat docs/PROJECT_STATE.md docs/NEXT_STEPS.md docs/HANDOFF.md docs/BENCH_BRINGUP_LOG.md docs/PROCUREMENT_STATUS.md`.


## 2026-03-14

- **Issue:** Stage 0/1 BOM and procurement tracker implied separate purchases for Romi subcomponents that are already included in the full blue Romi chassis kit.
- **Impact:** Could cause unnecessary duplicate purchases before first procurement.
- **Resolution:** Corrected chassis kit SKU to `Pololu #3506`, marked motors/wheels/caster as optional spare-only, and added explicit included-with-kit battery-holder tracking.
- **Evidence:** Consistency review of `hardware/bom-stage-0-1.csv` and `docs/PROCUREMENT_STATUS.md` after update.

## 2026-03-17

- **Issue:** Roadmap context did not clearly distinguish Stage progression from physical platform generations, making future scaling intent hard to interpret for new agents.
- **Impact:** Could cause roadmap misreads, accidental Stage 1 scope creep, or implied physical progress on future platforms.
- **Resolution:** Added explicit platform-evolution sections, migration triggers, and status markers (planned/vision/not started) while preserving Stage 1 active scope.
- **Evidence:** Updated `docs/ROADMAP.md`, `docs/ARCHITECTURE.md`, `docs/DECISIONS.md`, and `docs/HANDOFF.md`.

## 2026-03-17

- **Issue:** Future planning language did not yet document how hybrid propulsion should be framed, which could be misread as permission for direct gas-drive exploration in near-term builds.
- **Impact:** Could trigger scope creep or architecture drift during Mk1/Mk2 execution planning.
- **Resolution:** Added explicit electric-drive-first and serial-hybrid/range-extender-only future guidance across architecture, roadmap, decision, and handoff docs.
- **Evidence:** `docs/ARCHITECTURE.md`, `docs/ROADMAP.md`, `docs/DECISIONS.md`, `docs/HANDOFF.md`, plus synchronized state/queue updates.

## 2026-03-17

- **Issue:** Stage 1 documentation lacked a single complete, beginner-friendly, live-use physical assembly procedure for Rover A hardware build sessions.
- **Impact:** First-time builders could make wiring or safety mistakes by stitching together multiple docs with different levels of detail.
- **Resolution:** Added a full phased build instruction guide with explicit goals, stop conditions, critical safety checks, and troubleshooting for first power-on and motor tests.
- **Evidence:** `docs/builds/stage1-rover-a-build.md` plus canonical context updates in `PROJECT_STATE`, `NEXT_STEPS`, and `HANDOFF`.

