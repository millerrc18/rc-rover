# rc-rover

**Temporary project name**: `rc-rover`

`rc-rover` is a modular mobile robotics platform designed to begin as a simple manually controlled RC rover and to evolve into a reusable sensor and robotics development platform.  The goal is to create a base that allows incremental learning and experimentation in remote control, sensors, control systems, telemetry, and autonomy.

## Long‑term vision

The long‑term vision for this project is to build a platform that can grow from a basic RC vehicle into a capable robotics testbed.  It will support adding sensors, data logging, closed‑loop control, obstacle detection, semi‑autonomous behavior and ultimately more advanced autonomy and payloads.  Each step will be documented so that future users can reproduce and extend the work.

The roadmap now also defines a multi-generation platform path: Rover A / Mk1 (current learning platform), Rover B / Mk2 (payload-class), Rover C / Mk3 (utility-class), and Rover D / Mk4 (scout/manipulation vision), while keeping Stage 1 execution scope fixed.

## Current status

This repository is currently being bootstrapped.  The initial commit sets up a documentation and memory system that will serve as a durable operating system for the project.  There is no hardware or software yet; the focus is on scaffolding the repo so that future agents and contributors can understand the project context and history without prior chat.

## Repository organization

```
- `README.md` — This document.  High‑level overview and how to navigate the repo.
- `AGENTS.md` — Instructions for future agents on how to work in this repo.
- `.codex/config.toml` — Local configuration for codex/agent behaviour.
- `docs/` — Project documentation and memory system.
  - `START_HERE.md` — Entry point for new contributors or sessions.
  - `PROJECT_STATE.md` — Canonical current state of the project.
  - `NEXT_STEPS.md` — Prioritised action queue.
  - `DECISIONS.md` — Record of important decisions.
  - `ARCHITECTURE.md` — Description of current and future architecture.
  - `BUILD_LOG.md` — Append‑only log of work done.
  - `LEARNINGS.md` — Lessons learned and heuristics.
  - `BACKLOG.md` — Ideas and tasks not yet prioritised.
  - `GLOSSARY.md` — Definitions of project terms.
  - `HANDOFF.md` — Quick summary for resuming sessions.
  - `PROJECT_CHARTER.md` — Mission, principles and scope for v1.
  - `ROADMAP.md` — Phased growth plan.
  - `CONTRIBUTING.md` — Guidelines for contributing and workflow.
  - `templates/` — Reusable templates for logs, decisions, experiments, milestones and task briefs.
  - `INDEX.md` — Map of documentation files.
```

## Getting started

1. Read `docs/START_HERE.md` for an overview of the repo structure and how to contribute.
2. Review `docs/HANDOFF.md` for a snapshot of the current phase, objectives, constraints and upcoming actions.
3. Consult `AGENTS.md` for the workflow expected of automated agents working in this repo.

## First time contributors

If you are a new contributor (human or agent), please start by reading `docs/START_HERE.md`, then proceed to `docs/PROJECT_STATE.md` and `docs/NEXT_STEPS.md` to understand the current status and what needs to be done next.  The `docs/INDEX.md` file provides a map of all documentation resources.