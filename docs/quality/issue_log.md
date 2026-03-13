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
