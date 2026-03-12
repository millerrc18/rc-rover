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
