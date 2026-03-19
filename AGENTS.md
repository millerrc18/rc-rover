# Instructions for Agents

## Required pre-work

Before starting any substantial task, read these files in order:

1. `README.md` — project overview.
2. `docs/HANDOFF.md` — current phase, constraints, and next actions.
3. `docs/PROJECT_STATE.md` — canonical current state.
4. `docs/NEXT_STEPS.md` — prioritized action queue.

## Workflow

1. **Plan first.** Summarize intended changes before modifying files.
2. **Execute.** Perform the planned changes.
3. **Validate.** Verify changes compile, run, or meet acceptance criteria.
4. **Update docs.** Reflect what changed (see below).

## End-of-task documentation updates

After modifying the project, update these files as applicable:

- **Always:** append a dated entry to `docs/BUILD_LOG.md`.
- **Always:** update `docs/HANDOFF.md` with a fresh snapshot.
- **If state changed:** update `docs/PROJECT_STATE.md`.
- **If priorities changed:** update `docs/NEXT_STEPS.md`.
- **If a decision was made:** add an entry to `docs/DECISIONS.md`.
- **If architecture changed:** update `docs/ARCHITECTURE.md`.
- **If a lesson was learned:** add to `docs/LEARNINGS.md`.

Not every task touches every file. Use judgment — but never leave the repo in a state where a new agent cannot determine current status and next actions.

## Assumptions vs. confirmed facts

Mark uncertain information as **Assumption** in documentation. When an assumption is confirmed or disproven, update the relevant doc and note the correction in `docs/LEARNINGS.md`.

## Canonical sources

- **Current state:** `docs/PROJECT_STATE.md`
- **Action queue:** `docs/NEXT_STEPS.md`
- **Decisions:** `docs/DECISIONS.md`
- **Build history:** `docs/BUILD_LOG.md`
- **Hand-off:** `docs/HANDOFF.md`
