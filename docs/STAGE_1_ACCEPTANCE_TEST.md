# Stage 1 Acceptance Test

_Last updated: 2026-03-11_

This document defines what "done" means for the first meaningful hardware milestone.

## Stage 1 objective

Prove that the rover is a stable manual-control platform that can serve as the base for all later sensor and autonomy work.

## Pass criteria

The rover passes Stage 1 when all of the following are true:

1. **Power-on behavior is safe**
   - Main power switch works predictably.
   - No unexpected motion at startup.
   - Emergency stop or hard stop behavior is documented and tested.

2. **Drive control works**
   - Rover moves forward on command.
   - Rover moves in reverse on command.
   - Rover turns left on command.
   - Rover turns right on command.
   - Rover can stop cleanly from low-speed motion.

3. **Low-speed control is usable**
   - Rover can be driven precisely enough to approach a target line or marker.
   - Control latency is low enough that manual driving feels intentional, not delayed or erratic.

4. **Power system is documented**
   - Battery type, nominal voltage, connector, fuse, and switch are recorded in the repo.
   - Controller supply path is documented.
   - Motor driver supply path is documented.

5. **Battery awareness exists**
   - Rover reports battery voltage through serial output, debug console, or a simple telemetry path.
   - Low-voltage threshold is documented, even if shutdown logic is not yet implemented.

6. **Repo state is reproducible**
   - BOM exists for Stage 0/1.
   - Wiring notes exist.
   - Current firmware entry point is documented.
   - A future contributor could reproduce the Stage 1 build from repo contents.

## Test procedure

### Bench checks
- Verify polarity before power-on.
- Verify fuse installed.
- Verify switch state and emergency stop behavior.
- Verify controller boots consistently.
- Verify motor directions are known and documented.

### Motion checks
- Place rover on a clear flat surface.
- Run forward, reverse, left, right, and stop commands.
- Repeat at least three times.
- Note any drift, wheel mismatch, brownout, or control lag.

### Power checks
- Record battery voltage at rest.
- Record battery voltage during low-speed motion.
- Record any reset events or power instability.

### Documentation checks
- Confirm the repo contains:
  - updated `PROJECT_STATE.md`
  - updated `NEXT_STEPS.md`
  - updated `BUILD_LOG.md`
  - updated `HANDOFF.md`
  - Stage 0/1 BOM

## Non-goals for Stage 1

The following are explicitly not required for Stage 1:
- obstacle detection,
- encoders,
- IMU integration,
- autonomous motion,
- polished industrial design,
- weather resistance,
- outdoor rough-terrain performance.

## Failure conditions

Stage 1 is not complete if any of the following occur:
- intermittent or unsafe startup motion,
- repeated controller brownouts,
- unreliable directional control,
- undocumented wiring changes,
- inability to reproduce the configuration from the repo.
