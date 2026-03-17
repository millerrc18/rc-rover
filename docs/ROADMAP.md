# Roadmap

_Last updated: 2026-03-17_

This roadmap outlines phased growth of `rc-rover`.

## Platform Evolution Path

Rover generations describe physical platform evolution while stages describe capability growth.

- **Rover A / Mk1** = Romi-based learning and control platform (**current**).
- **Rover B / Mk2** = payload-class rover (**future**).
- **Rover C / Mk3** = utility-class rover (**future**).
- **Rover D / Mk4** = scout-manipulation platform (**long-term vision**).

**Note:** The stage-based roadmap tracks capability growth over time. Rover generations track chassis/platform evolution across build generations.

### Target Envelopes

**Rover A / Mk1**
- Romi-based learning rover
- Focus: teleop, wiring, bring-up, telemetry
- Not intended as final payload platform

**Rover B / Mk2**
- ~5 lb continuous payload
- ~8 lb short-duration test payload
- ~10 lb comfortable tow
- ~20 lb stretch tow
- Light manipulator-ready
- 20–45 min runtime

**Rover C / Mk3**
- ~15 lb continuous payload
- ~25 lb short-duration test payload
- ~40 lb comfortable tow
- ~75 lb stretch tow
- Moderate arm/tool support
- 45–90 min runtime

**Rover D / Mk4**
- ~30 lb continuous payload
- ~50 lb short-duration test payload
- ~100 lb comfortable tow
- ~150 lb stretch tow
- Serious manipulator + modular payloads
- 90–180 min runtime

### Planning Timeline Estimates

- **Rover A / Mk1:** ~2–6 weeks
- **Rover B / Mk2:** ~1–3 months
- **Rover C / Mk3:** ~2–5 months
- **Rover D / Mk4:** ~4–9+ months

These are planning estimates only. Actual timelines depend on scope discipline, fabrication approach, rework, and parts availability.

### Skills Intended Per Platform

**Rover A / Mk1**
- Differential drive fundamentals
- Safe wiring and power paths
- ESP32 bring-up and flashing
- BLE teleop
- Battery telemetry
- Structured bench testing
- Documentation discipline

**Rover B / Mk2**
- Chassis scaling tradeoffs
- Torque vs speed vs runtime
- Payload packaging and stability
- Center-of-gravity thinking
- Higher-current power distribution
- Modular mounting design

**Rover C / Mk3**
- Outdoor rover design
- Drivetrain sizing
- Terrain/traction handling
- Runtime and thermal margins
- Serviceability mindset
- Moderate arm/tool integration

**Rover D / Mk4**
- Modular robotics architecture
- Mobility + manipulation integration
- Sensing + compute partitioning
- Payload interface design
- Autonomy-ready systems
- Full platform systems engineering

### Migration Triggers

Move beyond Rover A / Mk1 when one or more are true:
- Payload need exceeds ~2 lb
- Towing need exceeds ~5 lb
- Manipulator arm integration is required
- Battery size exceeds safe packaging limits
- Stability or footprint limits are reached

### Roadmap Summary Table

| Generation | Platform | Role | Payload / Tow | Timeline | Key Skills | Status |
|-----------|---------|------|--------------|----------|-----------|--------|
| Mk1 | Rover A | Learning rover | Minimal payload, no towing focus | 2–6 weeks | Wiring, teleop, ESP32, telemetry | Active |
| Mk2 | Rover B | Payload rover | ~5 lb payload, 10–20 lb tow | 1–3 months | Stability, power, packaging | Planned |
| Mk3 | Rover C | Utility rover | ~15 lb payload, 40–75 lb tow | 2–5 months | Outdoor systems, drivetrain, reliability | Planned |
| Mk4 | Rover D | Scout/manipulation | ~30 lb payload, 100+ lb tow | 4–9+ months | Modular robotics, autonomy-ready systems | Vision |

## Stage 0: Rolling chassis

- Select/build differential-drive chassis.
- Install motors, wheels, battery path, and safe power switching.
- Deliverable: chassis can be powered and prepared for controlled motion bring-up.

## Stage 1: Manual remote control (current active build)

- Integrate ESP32-based control with dual motor driver.
- Implement BLE teleop, throttle/turn mapping, and safety stop behavior.
- Add battery-voltage reporting baseline.
- Deliverable: rover can be remotely driven on flat surface and pass Stage 1 acceptance tests.

## Stage 2: Basic telemetry

- Add current sensing and richer battery health telemetry.
- Improve runtime status indicators and logging.

## Stage 3: First obstacle sensor

- Add front distance sensing (ToF or ultrasonic).
- Implement warning and/or auto-stop threshold behavior.

## Stage 4: Motion sensing

- Add wheel encoders and IMU.
- Estimate speed, heading, and motion state.

## Stage 5: Closed-loop control

- Add closed-loop speed control and heading stabilization.
- Improve drivability consistency.

## Stage 6: Advanced autonomy (future)

- Evaluate camera/lidar and mapping/localization approaches.
- Implement semi-autonomous behaviors after lower stages are stable.

### Future Stages

- **Stage 4 (Future): Rover B / Mk2** — Not Started / Out of Scope for current execution.
- **Stage 5 (Future): Rover C / Mk3** — Not Started / Out of Scope for current execution.
- **Stage 6 (Vision): Rover D / Mk4** — Not Started / Out of Scope for current execution.
