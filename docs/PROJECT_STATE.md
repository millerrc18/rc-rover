# Project State

_Last updated: 2026‑03‑11_

This file serves as the canonical description of the current state of the `rc-rover` project.  It should be updated whenever work is completed that changes the state of the project.

## Current phase

**Repository bootstrap**

At this phase the focus is on creating a durable project structure, not on hardware or software development.

## Current objective

Freeze the Stage 0/1 platform direction, draft the initial hardware decision package, and define the first hardware acceptance test.

## Summary of progress

- Created the repository and established initial documentation structure.
- Defined project vision, scope and goals in `README.md` and `PROJECT_CHARTER.md`.
- Established conventions and workflow for agents in `AGENTS.md`.
- Added templates and index files to support consistent documentation.

## Completed tasks

- Created repository `rc-rover` (temporary name).
- Added high-level project description and organisation.
- Added documentation structure under `docs/`.
- Added configuration file for Codex/agent.
- Initialised the memory system with default content.
- Added the Stage 0/1 decision package: platform selection, initial BOM, and Stage 1 acceptance test.

## Open tasks

See `docs/NEXT_STEPS.md` for prioritised action items. The highest-priority branch of work is now the Stage 0/1 base-platform decision and parts freeze.

## Hardware state

No hardware purchased or assembled yet. Reference architecture now points to a robotics-first differential-drive base with an ESP32-class controller.

## Software state

No firmware written yet. The project now has enough architectural direction to begin Stage 0/1 hardware research and part ordering.

## Assumptions

- The repository will serve as the single source of truth for project state and instructions.
- The project will eventually involve designing, building and programming a mobile rover capable of being controlled remotely and upgraded with sensors.
- The name `rc-rover` is temporary and may change later.