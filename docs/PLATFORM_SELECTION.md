# Platform Selection

_Last updated: 2026-03-11_

This document compares the most realistic Stage 0/1 base-platform options for `rc-rover` and forces a recommendation. The goal is not to pick the coolest platform. The goal is to pick the platform that is most likely to become a long-lived robotics mule without creating an early complexity trap.

## Decision criteria

The first platform should score well in five areas:

1. **Modularity** - easy to add sensors, controllers, and wiring later.
2. **Repeatability** - easy to build, document, and troubleshoot.
3. **Growth path** - supports encoders, telemetry, and later autonomy work.
4. **Mechanical simplicity** - minimizes suspension, steering, and drivetrain complexity at the start.
5. **Cost discipline** - keeps Stage 0/1 affordable without becoming disposable.

## Option A - Robotics-first differential-drive chassis

### What it is
A flat, compact, differential-drive rover base intended for robotics work. A Romi-style platform is the reference class for this option.

### Why it is attractive
- Differential drive is the cleanest path for learning motor control, odometry, and closed-loop behavior.
- The chassis is mechanically simple: two drive wheels and one or more passive contact points.
- It is naturally compatible with wheel encoders, front sensors, and later companion compute.
- A Romi-style reference platform already exposes mounting holes and accessory support for encoder and motor-driver add-ons.

### Trade-offs
- Less "real car" feel than an RC truck.
- Lower ground clearance and less outdoor rough-terrain capability.
- More functional than dramatic in stock form.

### Fit for this project
**Excellent.** This option aligns best with the project's actual purpose: a reusable learning and development platform.

## Option B - Hobby RC truck base

### What it is
An off-the-shelf RC car or truck chassis with existing steering, drivetrain, suspension, and hobby electronics heritage.

### Why it is attractive
- Feels immediately fun and recognizable.
- Often faster and more visually exciting.
- Good option if the primary goal is driving enjoyment.

### Trade-offs
- Steering linkages, suspension geometry, and integrated hobby systems add complexity that does not directly teach sensing or robotics fundamentals.
- Sensor and compute mounting is often more awkward.
- Future autonomy work can become more constrained by the original RC packaging.

### Fit for this project
**Moderate.** Good if "RC first" is the priority. Not the best long-term robotics mule.

## Option C - Custom frame from day one

### What it is
A purpose-built frame using aluminum extrusion, plate, or 3D-printed structure with fully custom packaging.

### Why it is attractive
- Maximum freedom in layout and aesthetics.
- Strong long-term upside.
- Best option if custom mechanical design is itself the learning target.

### Trade-offs
- Highest schedule risk.
- Easy to overbuild before the control stack is proven.
- More time is spent on fabrication before any rover motion exists.

### Fit for this project
**Low for Stage 0/1.** Strong future option, weak first option.

## Recommendation

## Select Option A: robotics-first differential drive

This is the strongest first platform because it maximizes learning-per-hour and creates the least friction for future upgrades.

A Romi-style differential-drive base is the best reference architecture for the first build because:
- it is explicitly a differential-drive robotics platform,
- the wheel layout supports in-place turning,
- mounting provisions are already available,
- encoder support is straightforward,
- and it reduces mechanical distractions during the first control and sensing stages.

## Stage 0/1 reference stack

The following stack is the recommended reference architecture for the first build. It is a starting point, not a permanent lock-in.

- **Chassis class:** Romi-style differential-drive rover
- **Primary controller:** ESP32 development board
- **Motor drive path:** dual-channel motor driver sized for the chosen motors
- **Power:** onboard battery pack with main power switch and fuse
- **Manual control:** Bluetooth or Wi-Fi teleop first, with traditional RC still allowed as a fallback
- **First sensor after manual control:** front time-of-flight distance sensor

## Why ESP32 is the recommended controller

ESP32 is the best early controller because it combines microcontroller simplicity with built-in wireless connectivity. That makes it a strong bridge between manual control, telemetry, and future network-connected experiments. It also keeps the early stack simpler than jumping straight to a Linux-class computer.

## Stage 0/1 architecture decision

The project will begin as a **robotics-first differential-drive rover** rather than an RC truck or a fully custom chassis.

That means Stage 0/1 work should optimize for:
- flat deck space,
- easy access to wiring,
- clear motor-control architecture,
- room for future sensors,
- and documentation quality.

## Deferred decisions

The following are intentionally deferred until after the base rover moves reliably:
- final project name,
- industrial design direction,
- full custom frame,
- camera/lidar selection,
- autonomy stack,
- companion computer.

## Exit criteria for this selection phase

This selection phase is complete when:
1. the chassis direction is accepted,
2. the Stage 0/1 BOM is frozen enough to order parts,
3. the Stage 1 acceptance test is agreed,
4. and the repo reflects the decision in `DECISIONS.md`, `PROJECT_STATE.md`, and `HANDOFF.md`.
