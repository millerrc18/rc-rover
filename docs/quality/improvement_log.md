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
