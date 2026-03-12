# Roadmap

_Last updated: 2026-03-12_

This roadmap outlines phased growth of `rc-rover`.

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
