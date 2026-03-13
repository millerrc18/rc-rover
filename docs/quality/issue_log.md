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
