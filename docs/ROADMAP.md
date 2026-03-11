# Roadmap

_Last updated: 2026‑03‑11_

This roadmap outlines the phased growth of the `rc-rover` platform.  Each stage builds upon the previous one and introduces new capabilities.

## Stage 0: Rolling chassis

- Select or build a durable chassis with two drive wheels and casters or skid steering.
- Install motors, wheels and a battery pack.
- Add a simple motor driver and microcontroller to control the motors.
- Provide a safe power distribution setup with fuse and switch.
- **Deliverable:** a chassis that can move under manual voltage control (e.g. tethered or via a simple remote).

## Stage 1: Manual remote control

- Integrate a remote control system (traditional RC transmitter/receiver or Bluetooth).
- Implement throttle and steering control via the microcontroller.
- Add basic safety features (emergency stop).
- **Deliverable:** a rover that can be driven remotely on a flat surface.

## Stage 2: Basic telemetry

- Add voltage and current sensors to monitor battery health and motor load.
- Transmit or log telemetry data.
- Provide visual indicators (LEDs) for battery status.

## Stage 3: First obstacle sensor

- Install a front distance sensor (ultrasonic or time‑of‑flight).
- Implement a warning or auto‑stop feature when an obstacle is detected within a threshold.
- **Deliverable:** the rover warns or stops before hitting objects.

## Stage 4: Motion sensing

- Add wheel encoders to measure speed and distance.
- Install an IMU to measure acceleration and angular velocity.
- Compute estimated speed, heading and inclination.
- **Deliverable:** the rover reports its motion state and can log or display it.

## Stage 5: Closed‑loop control

- Use encoder and IMU feedback to implement closed‑loop speed control.
- Implement heading hold and straight‑line correction.
- **Deliverable:** smoother and more precise manual driving experience.

## Stage 6: Advanced autonomy (future)

- Integrate higher‑bandwidth sensors such as lidar or cameras.
- Implement mapping and localisation.
- Explore autonomous behaviours such as waypoint following and obstacle avoidance.
- **Deliverable:** a semi‑autonomous or fully autonomous rover.

The roadmap should be revisited and updated as the project progresses.  Completed stages should be marked and future stages can be adjusted based on lessons learned.