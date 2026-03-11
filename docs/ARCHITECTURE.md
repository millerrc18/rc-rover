# Architecture

_Last updated: 2026‑03‑11_

This document describes the current architecture of the `rc-rover` project and outlines future candidate architectures as the platform evolves.

## Current architecture

There is no hardware or software architecture yet.  The repository has been bootstrapped with a documentation system, but the rover platform has not been designed.

## Future candidate architectures

The long‑term architecture is expected to evolve through the following stages:

1. **Stage 0 – Rolling chassis**  
   - Two drive wheels with motors and encoders.  
   - Passive casters or skid steering.  
   - Battery pack and power distribution board.  
   - Minimal onboard electronics (microcontroller to drive motors).

2. **Stage 1 – Manual remote control**  
   - Traditional RC transmitter/receiver or Bluetooth remote for throttle and steering.  
   - Microcontroller with motor driver and safety interlocks.  
   - Simple power monitoring.

3. **Stage 2 – Basic telemetry**  
   - Voltage and current sensors to monitor battery health and motor load.  
   - Telemetry sent back to the controller or logged onboard.  
   - Provide visual indicators (LEDs) for battery status.

4. **Stage 3 – First obstacle sensor**  
   - Install a front distance sensor (ultrasonic or time‑of‑flight).  
   - Implement a warning or auto‑stop feature when an obstacle is detected within a threshold.  
   - Deliverable: the rover warns or stops before hitting objects.

5. **Stage 4 – Motion sensing**  
   - Add wheel encoders to measure speed and distance.  
   - Install an IMU to measure acceleration and angular velocity.  
   - Compute estimated speed, heading and inclination.

6. **Stage 5 – Closed‑loop control**  
   - Use encoder and IMU feedback to implement closed‑loop speed control.  
   - Implement heading hold and straight‑line correction.  
   - Deliverable: smoother and more precise manual driving experience.

7. **Stage 6 – Advanced autonomy (future)**  
   - Integrate higher‑bandwidth sensors such as lidar or cameras.  
   - Implement mapping and localisation.  
   - Explore autonomous behaviours such as waypoint following and obstacle avoidance.  
   - Deliverable: a semi‑autonomous or fully autonomous rover.

Each stage builds upon the previous one, allowing modular growth.  Any changes to the architecture should be captured here and summarised in `PROJECT_STATE.md` and `HANDOFF.md`.