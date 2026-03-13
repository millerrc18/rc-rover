# Decisions

This file records important decisions made in the project.  Each entry should include a date, a status (proposed/accepted/rejected/superseded), the decision, the rationale and any implications.

---

**Date:** 2026‑03‑11  
**Status:** Accepted  
**Decision:** Use a documentation‑driven memory system in the repository to capture project state, decisions, next steps and learnings.  
**Rationale:** The project will span many sessions and the chat history cannot be assumed to persist.  A durable memory system in the repository ensures that future agents and contributors can recover context.  
**Implications:** All work must be accompanied by updates to the documentation.  Agents must follow the workflow defined in `AGENTS.md`.

---

**Date:** 2026‑03‑11  
**Status:** Accepted  
**Decision:** Adopt a modular growth plan for the rover: start as a simple manual RC platform and progressively add sensors, telemetry and autonomy.  
**Rationale:** A modular approach allows incremental learning and development while avoiding scope creep.  
**Implications:** Early stages should focus on simplicity and reliability.  Later stages can layer complexity without rewriting the base.

---

**Date:** 2026‑03‑11  
**Status:** Assumption  
**Decision:** Use the temporary name `rc-rover` until a permanent name is chosen.  
**Rationale:** The project needs a working identifier, but the final branding will be determined later.  
**Implications:** Avoid tying external dependencies (e.g. printed labels, domain names) to the temporary name.
---

**Date:** 2026-03-11  
**Status:** Accepted  
**Decision:** Use a robotics-first differential-drive rover as the Stage 0/1 base-platform direction.  
**Rationale:** Differential drive gives the project the cleanest path into sensing, encoders, telemetry, and later autonomy while keeping the mechanical system simple at the beginning.  
**Consequences:** Early work should optimize for flat deck space, simple motor control, clear wiring, and repeatable documentation rather than car-like steering or custom-frame aesthetics.

---

**Date:** 2026-03-11  
**Status:** Accepted  
**Decision:** Use an ESP32-class development board as the primary early-stage controller.  
**Rationale:** ESP32 provides a practical bridge between basic embedded control and wireless experimentation without requiring a Linux-class compute stack in the first build.  
**Consequences:** The first firmware work should target simple motor control, serial debug, and battery-voltage reporting, with wireless teleop as a likely next step.

---

**Date:** 2026-03-12  
**Status:** Accepted  
**Decision:** Standardize on **Espressif ESP32-DevKitC-32E** as the Stage 1 development board.  
**Rationale:** It is a broadly documented, low-friction ESP32 baseline with straightforward USB flashing/debug and predictable bring-up behavior for early firmware work.  
**Consequences:** Firmware examples, pin planning, and assembly documentation should target DevKitC-32E pinout assumptions first; equivalents are allowed only when functionally compatible.

---

**Date:** 2026-03-12  
**Status:** Accepted  
**Decision:** Use **Pololu Romi Motor Driver and Power Distribution Board** as the primary Stage 1 motor-driver path.  
**Rationale:** Romi-native integration reduces mechanical and wiring uncertainty versus generic driver breakout combinations during first build.  
**Consequences:** Stage 1 assembly and interface docs prioritize this board; alternate driver paths may be evaluated only after Stage 1 baseline is validated.

---

**Date:** 2026-03-12  
**Status:** Accepted  
**Decision:** Use **Bluetooth (BLE) teleop** as the initial manual-control method for Stage 1.  
**Rationale:** BLE uses ESP32 built-in radios without extra hardware and avoids early Wi-Fi network/config complexity while still enabling phone-based control.  
**Consequences:** Initial firmware scaffold should implement BLE command/heartbeat handling; Wi-Fi teleop remains a later optional enhancement.

---

**Date:** 2026-03-12  
**Status:** Accepted  
**Decision:** Freeze Stage 1 ESP32 logic-power path as `Motor Driver/Power Board regulated 5V output -> ESP32-DevKitC-32E 5V pin` for untethered operation, and freeze bench bring-up cable as `USB-A to Micro-USB data cable`.  
**Rationale:** Previous docs allowed board-dependent and power-source ambiguity that could block bench bring-up reproducibility.  
**Consequences:** Wiring docs, BOM, and bring-up workflow now use a single explicit power path and connector standard for Stage 1.



---

**Date:** 2026-03-13  
**Status:** Accepted  
**Decision:** Implement Stage 1 firmware as a minimal single-loop PlatformIO/Arduino baseline with a plain-text BLE write protocol (`T,R,H,E,C`) for fastest bench bring-up.  
**Rationale:** Stage 1 success depends on fast, debuggable hardware validation rather than protocol sophistication; a compact ASCII control packet is easy to send from generic phone BLE tools and inspect over serial.  
**Consequences:** Control protocol is intentionally simple and may be superseded later by a binary or schema-validated profile after Stage 1 acceptance is complete.
