# Documentation Index

This file maps the contents of `docs/` and `firmware/`.

## Core documents

- **START_HERE.md**: Entry point for new contributors/sessions.
- **PROJECT_STATE.md**: Canonical current project state.
- **NEXT_STEPS.md**: Prioritized action queue.
- **DECISIONS.md**: Decision log with rationale and consequences.
- **ARCHITECTURE.md**: Current and future architecture summary.
- **BUILD_LOG.md**: Chronological work log.
- **LEARNINGS.md**: Lessons and heuristics.
- **BACKLOG.md**: Unprioritized ideas/tasks.
- **GLOSSARY.md**: Project terminology.
- **HANDOFF.md**: Session hand-off snapshot.
- **PROJECT_CHARTER.md**: Mission, principles and scope.
- **ROADMAP.md**: Staged growth plan (canonical — replaces rc-rover-roadmap.md).
- **CONTRIBUTING.md**: Contribution workflow.

## Stage 0/1 hardware freeze artifacts

- **PLATFORM_SELECTION.md**: Stage 0/1 platform decision rationale (canonical — replaces rc-rover-platform-decision-matrix.md).
- **HARDWARE_ARCHITECTURE.md**: Frozen Stage 1 hardware architecture and recommendation rationale.
- **INTERFACE_MAP.md**: Stage 1 interface-level mapping (power, control, safety, deferred interfaces).
- **STAGE_1_WIRING_DIAGRAM.md**: Exact Stage 1 wiring, power/signal diagrams, resistor values for battery divider, and pre-power checks.
- **STAGE_1_PIN_MAP.md**: Frozen Stage 1 ESP32 pin assignments with conflict rationale and GPIO14 boot-strapping note.
- **FIRMWARE_SCAFFOLD.md**: Implementation-ready Stage 1 firmware behavior blueprint.
- **STAGE_1_BUILD_PLAN.md**: Build and bring-up plan for Stage 1.
- **STAGE_1_ACCEPTANCE_TEST.md**: Stage 1 pass/fail criteria.
- **BLE_CONTROL_PROFILE.md**: Stage 1 BLE service/packet format used by firmware baseline.
- **BENCH_BRINGUP_LOG.md**: Reusable log template for real bench bring-up sessions.
- **STAGE_1_TUNING.md**: Stage 1 drivability and safety tuning worksheet, including battery ADC calibration procedure.
- **../hardware/bom-stage-0-1.csv**: First-pass sourced BOM.
- **PROCUREMENT_STATUS.md**: Stage 0/1 order/receiving/inspection tracker.
- **builds/stage1-rover-a-build.md**: Beginner-friendly, phase-by-phase physical assembly guide for Rover A Stage 1. Targets the Pololu Romi Motor Driver and Power Distribution Board (#3543). Uses frozen pin map (GPIO25/26/27/14).

## Firmware

- **firmware/stage1-esp32-baseline/**: Production Stage 1 BLE teleop firmware (PlatformIO/Arduino). Flash this for normal operation.
- **firmware/stage1-motor-test/**: Minimal motor test sketch for first hardware bring-up. Runs a fixed test sequence with no BLE required. Flash this before the baseline to validate motor wiring, then reflash the baseline.

## Templates

`docs/templates/` includes reusable templates:
- `session_note.md`
- `architecture_decision_record.md`
- `experiment_record.md`
- `milestone_review.md`
- `task_brief.md`

## Quality logs

- `docs/quality/issue_log.md`
- `docs/quality/improvement_log.md`

## Historical reference documents (superseded — do not use as source of truth)

These documents are retained for historical context but have been superseded by the canonical documents listed above. Each file contains a superseded/historical notice at the top.

- **rc-rover-roadmap.md**: Early roadmap draft. Superseded by `docs/ROADMAP.md`.
- **rc-rover-platform-decision-matrix.md**: Early platform scoring analysis. Superseded by `docs/PLATFORM_SELECTION.md` and `docs/DECISIONS.md`. Retained for the weighted scoring matrix.
- **rc-rover-concept-render-sheet.md**: Early visual concept directions. Out of scope for Stage 1. Relevant in Stage 11+ per `docs/ROADMAP.md`. Retained for render prompt starters.
- **rc-rover-system-architecture-block-diagram.md**: Early system architecture narrative. Partially superseded by `docs/ARCHITECTURE.md` and `docs/HARDWARE_ARCHITECTURE.md`. Retained for its functional block diagrams.
