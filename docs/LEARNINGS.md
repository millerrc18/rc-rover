# Learnings

This file captures lessons learned, mistakes made and heuristics discovered during the project.  Entries should include a date and a brief description.

## 2026‑03‑11

- Establishing a documentation‑driven memory system early on prevents loss of context between sessions and reduces reliance on chat history.
## 2026-03-12

- Aligning `PROJECT_STATE.md` with `HANDOFF.md` and `NEXT_STEPS.md` prevents conflicting phase signals that can misdirect future sessions.
- A freeze package is more actionable when architecture, interface map, and build plan are split into separate docs rather than merged into one long narrative.
- Freezing both bench-power mode and untethered-power mode in the same wiring package prevents hidden integration ambiguity that BOM-only updates often miss.

## 2026-03-13

- A plain-text BLE control packet with explicit heartbeat (`T,R,H,E,C`) is fast to validate on bench hardware and reduces tooling friction during first bring-up.
- Maintaining a dedicated bench bring-up log template prevents ad-hoc test notes and makes acceptance evidence easier to compare across runs.
