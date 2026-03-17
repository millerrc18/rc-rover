# Quality Improvement Log

## 2026-03-12

- **Improvement:** Added dedicated Stage 1 hardware freeze artifacts (`HARDWARE_ARCHITECTURE`, `INTERFACE_MAP`, `STAGE_1_BUILD_PLAN`).
- **Why it mattered:** Makes build execution reproducible and reduces interpretation ambiguity.
- **Evidence:** New cross-linked docs plus sourced BOM updates and explicit decisions in `DECISIONS.md`.

- **Improvement:** Upgraded Stage 0/1 BOM from generic placeholders to stronger first-pass sourced recommendations.
- **Why it mattered:** Enables immediate procurement with clearer alternates rationale.
- **Evidence:** `hardware/bom-stage-0-1.csv` now includes recommended parts, sources, and justifications.

- **Improvement:** Added Stage 1 implementation package (`STAGE_1_WIRING_DIAGRAM`, `STAGE_1_PIN_MAP`, `FIRMWARE_SCAFFOLD`).
- **Why it mattered:** Converts high-level freeze docs into bench-executable instructions and firmware-ready interfaces.
- **Evidence:** New docs include exact pin freeze, safety checklists, and firmware state behavior definitions.


## 2026-03-13

- **Improvement:** Delivered first runnable Stage 1 ESP32 firmware baseline with core safety and teleop control loop behavior.
- **Why it mattered:** Converts documentation-only plan into executable bench-ready implementation and unblocks real hardware testing.
- **Evidence:** Build attempt via `pio run` in `firmware/stage1-esp32-baseline/` plus new bring-up and BLE profile docs.

- **Improvement:** Added `docs/PROCUREMENT_STATUS.md` and reordered immediate execution flow to procurement -> receiving/inspection -> assembly -> flash/bring-up.
- **Why it mattered:** Makes physical execution sequence explicit and prevents premature validation steps.
- **Evidence:** Updated action ordering in `docs/NEXT_STEPS.md` and new tracker in `docs/PROCUREMENT_STATUS.md`.


## 2026-03-14

- **Improvement:** Reframed procurement documentation into initial buy-now vs included-with-kit vs later-stage sections.
- **Why it mattered:** Makes first purchase set unambiguous and reduces ordering mistakes in pre-assembly execution.
- **Evidence:** Updated `hardware/bom-stage-0-1.csv` subtotal semantics and sectioned `docs/PROCUREMENT_STATUS.md` tracker.

## 2026-03-17

- **Improvement:** Introduced a concise multi-generation strategy package (definitions, envelopes, timelines, skills, triggers, summary table) without changing Stage 1 baseline execution plan.
- **Why it mattered:** Gives new agents fast strategic context while keeping immediate physical execution priorities stable and explicit.
- **Evidence:** Cross-doc updates in `docs/ROADMAP.md`, `docs/ARCHITECTURE.md`, `docs/PROJECT_STATE.md`, `docs/NEXT_STEPS.md`, and `docs/HANDOFF.md`.
