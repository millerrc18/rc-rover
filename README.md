# rc-rover

A modular mobile robotics platform that starts as a manually controlled differential-drive rover and grows into a reusable testbed for sensors, control systems, telemetry, and autonomy.

**Working name** — final branding TBD.

## Current status

**Stage 1: Manual remote control** — parts arriving, physical build imminent.

Firmware exists for BLE teleop and motor testing. No hardware has been assembled yet. See `docs/HANDOFF.md` for the latest session snapshot.

## Platform generations

| Gen | Platform | Role | Status |
|-----|----------|------|--------|
| Mk1 | Rover A | Romi-based learning rover | **Active** |
| Mk2 | Rover B | Payload-class (~5 lb) | Planned |
| Mk3 | Rover C | Utility-class (~15 lb) | Planned |
| Mk4 | Rover D | Scout/manipulation (~30 lb) | Vision |

## Getting started

**For a new session (human or agent):**

1. Read this file for the overview.
2. Read `docs/HANDOFF.md` for the current phase, constraints, and next actions.
3. Read `docs/PROJECT_STATE.md` for canonical project state.
4. Read `docs/NEXT_STEPS.md` for the prioritized action queue.

**For agents:** also read `AGENTS.md` for the mandatory workflow.

## Repository layout

```
README.md               — This file. Project overview and entry point.
AGENTS.md               — Workflow rules for automated agents.
docs/
  HANDOFF.md            — Session hand-off snapshot (start here each session).
  PROJECT_STATE.md      — Canonical current state.
  NEXT_STEPS.md         — Prioritized action queue.
  DECISIONS.md          — Decision log with rationale.
  BUILD_LOG.md          — Chronological work history.
  LEARNINGS.md          — Lessons learned and heuristics.
  ARCHITECTURE.md       — Current and planned architecture.
  ROADMAP.md            — Multi-generation growth plan.
  BACKLOG.md            — Unprioritized ideas and future work.
  CONTRIBUTING.md       — Contribution guidelines.
  HARDWARE_ARCHITECTURE.md  — Stage 1 hardware freeze (includes interface map).
  STAGE_1_WIRING.md     — Wiring diagram, pin map, and checklists.
  STAGE_1_ACCEPTANCE_TEST.md — Pass/fail criteria for Stage 1.
  STAGE_1_TUNING.md     — Tuning worksheet and ADC calibration procedure.
  BLE_CONTROL_PROFILE.md — BLE service/packet format.
  BENCH_BRINGUP_LOG.md  — Reusable test session template.
  PROCUREMENT_STATUS.md — Order/receiving tracker.
  builds/
    stage1-rover-a-build.md — Complete physical assembly guide.
  archive/              — Superseded docs retained for reference.
firmware/
  stage1-esp32-baseline/ — Production BLE teleop firmware.
  stage1-motor-test/     — Standalone motor validation sketch.
hardware/
  bom-stage-0-1.csv     — Bill of materials.
```

## Principles

- **Incremental growth** — each stage yields a working system before adding complexity.
- **Modularity** — new capabilities layer on without rewriting the base.
- **Documentation-driven** — decisions, state, and lessons live in the repo, not in chat history.
- **Safety-first** — deadman timeout, e-stop, and physical power cutoff from day one.

## Glossary

- **Differential drive** — two independently driven wheels; steering by varying wheel speeds.
- **Deadman timeout** — motors stop automatically if control commands stop arriving.
- **E-stop** — emergency stop; latches motors off until explicitly cleared.
- **BLE** — Bluetooth Low Energy; used for Stage 1 phone-to-rover teleop.
- **Telemetry** — data (voltage, state, sensor readings) reported from rover to operator.
- **Encoder** — sensor measuring wheel/motor rotation for speed and distance estimation.
- **IMU** — Inertial Measurement Unit; measures acceleration and angular velocity.
- **SLAM** — Simultaneous Localization and Mapping; future autonomy capability.
