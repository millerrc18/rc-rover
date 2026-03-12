# Next Steps

_Last updated: 2026-03-11_

This file contains the prioritised action queue for the `rc-rover` project. When tasks are completed or priorities change, update this file accordingly.

## Now

- Accept or revise the Stage 0/1 platform recommendation in `docs/PLATFORM_SELECTION.md`.
- Freeze the first-pass Stage 0/1 BOM in `hardware/bom-stage-0-1.csv`.
- Decide the exact ESP32 development board and motor-driver path.
- Start a sourcing pass for the chassis, controller, power parts, and wiring items.

## Next

- Create a wiring plan for Stage 1 power, controller, and motors.
- Define the manual-control interface in more detail (Bluetooth app, web UI, or fallback radio path).
- Create a firmware scaffold for basic motor control and battery-voltage reporting.
- Create a simple assembly checklist for Stage 0/1.

## Later

- Add a front distance sensor for obstacle warning or auto-stop.
- Add wheel encoders for speed and odometry.
- Add an IMU for motion awareness.
- Add structured telemetry logging.
- Revisit industrial design and concept rendering after the base moves reliably.

## Blocked

- Final naming and branding.
- Any autonomy-stack work before Stage 1 passes.
