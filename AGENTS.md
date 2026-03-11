# Instructions for Agents

This file defines the conventions that must be followed by any automated agent or human acting in the role of an agent in this repository.  Its purpose is to ensure that the project state can always be reconstructed from the repository alone.

## Overview

This project uses a documentation‑driven memory system under `docs/` to capture the current state, decisions, next steps and historical logs.  Agents must read and update these files as part of their workflow.  The canonical state lives in the repository, not in chat history.

## Required pre‑work

Before starting any substantial task, an agent must:

1. Read `README.md` for the project overview.
2. Read `docs/START_HERE.md` to understand the documentation structure.
3. Read `docs/HANDOFF.md` to understand the current phase, objective, constraints and next actions.
4. Read `docs/PROJECT_STATE.md` to learn the canonical current state.
5. Read `docs/NEXT_STEPS.md` to see the prioritised action queue.

These files must be read in order to gain context before making changes.

## Planning and validation workflow

1. **Plan first**.  Before modifying any file or code, an agent must summarise the intended changes and seek feedback when appropriate.
2. **Execute**.  Perform the planned changes.
3. **Validate**.  Verify that the changes compile, run or meet the defined acceptance criteria.
4. **Update memory**.  After completing work, update the documentation system to reflect what changed.

## Mandatory end‑of‑task ritual

After any task that modifies the state of the project, the agent **must**:

- Append a dated entry to `docs/BUILD_LOG.md` describing the work done.
- If any decisions were made, record them in `docs/DECISIONS.md` with date, rationale and consequences.
- If any lessons were learned or heuristics discovered, add them to `docs/LEARNINGS.md`.
- Update `docs/PROJECT_STATE.md` to reflect the new state.
- Update `docs/NEXT_STEPS.md` if priorities have changed or tasks have been completed.
- Update `docs/ARCHITECTURE.md` if the architecture has changed.
- Update `docs/HANDOFF.md` to provide a fresh snapshot for the next session.

Never leave the repository in a state where a new agent cannot determine the current status and next actions.

## Recording assumptions vs confirmed facts

When documenting something that is uncertain, clearly mark it as an **assumption**.  Confirmed facts should be recorded without qualifiers.  If an assumption is later proven incorrect, update the relevant documentation and log the correction in `docs/LEARNINGS.md`.

## Canonical sources

- **Current state**: `docs/PROJECT_STATE.md`
- **Action queue**: `docs/NEXT_STEPS.md`
- **Decisions**: `docs/DECISIONS.md`
- **Architecture**: `docs/ARCHITECTURE.md`
- **Build history**: `docs/BUILD_LOG.md`
- **Hand‑off summary**: `docs/HANDOFF.md`

Agents must always treat these files as the source of truth.