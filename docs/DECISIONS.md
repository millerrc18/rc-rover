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