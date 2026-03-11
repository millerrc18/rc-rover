# Project Charter

_Last updated: 2026‑03‑11_

This charter defines the mission, principles, learning goals, scope and success criteria for the first version of the `rc-rover` platform.

## Mission

To build a modular, durable and extensible mobile rover platform that begins with manual remote control and incrementally adds sensors, telemetry and autonomy in order to facilitate continuous learning in robotics.

## Principles

- **Modularity**: Design the platform so that new capabilities can be added without redesigning the entire system.
- **Incremental growth**: Start simple and add complexity in stages.  Each stage should yield a usable system.
- **Transparency**: Document decisions, assumptions and lessons openly so that future contributors can understand the project's evolution.
- **Practicality**: Favour practical, working solutions over speculative or overly complex designs.
- **Reusability**: Build generic components that can be reused in future robotics projects.

## Learning goals

1. Gain hands‑on experience with remote control systems for ground vehicles.
2. Integrate and interpret basic sensors (voltage, current, distance, encoders, IMU).
3. Implement closed‑loop control for speed and heading.
4. Explore telemetry systems for monitoring the rover's state.
5. Lay the groundwork for future autonomous behaviours (obstacle avoidance, path planning).

## Scope boundaries

- The v1 platform will focus on ground vehicles only.
- The initial stages will use hobby‑grade components; commercial or industrial components are out of scope.
- Software will run on microcontrollers initially; companion computers (e.g. Raspberry Pi) and advanced frameworks (e.g. ROS) are deferred to later stages.
- Autonomous navigation and computer vision are considered future expansions and not part of v1.

## Success criteria for v1

- The rover can be driven manually over a flat surface with reliable throttle and steering control.
- Safety features are in place, including an emergency stop and proper power management.
- Basic telemetry (battery voltage) is available to the operator.
- The documentation accurately reflects the design, assembly and operation of the platform.
- Future contributors can build upon the v1 platform with minimal friction.