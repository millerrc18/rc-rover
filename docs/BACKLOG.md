# Backlog

This file lists ideas and tasks that are not yet prioritised.  They may be explored in the future but are not part of the current action queue.

- Research differential vs. Ackermann steering platforms and choose one based on ease of control and flexibility.
- Explore using off‑the‑shelf RC car chassis vs. a custom frame built from aluminium extrusion or laser‑cut plates.
- Investigate various sensor types (ultrasonic, ToF, lidar, camera, IMU) for later integration.
- Consider open source robotic control frameworks (e.g. ROS 2) for future autonomy stages.
- Evaluate telemetry protocols (Bluetooth, Wi‑Fi, LoRa) for sending data back to a base station.
## Control surfaces (post Stage 1)

- **Stage 2:** Add Wi-Fi transport to ESP32 firmware alongside BLE, using the same T,R,H,E,C protocol.
- **Stage 2:** Build a web-based control dashboard (runs in browser over Wi-Fi) — easiest first control surface to implement.
- **Stage 2/3:** Build a mobile app (React Native or Flutter) with virtual joystick UI for iOS/Android.
- **Future:** Design and build a handheld physical controller with integrated screen and physical joysticks (Raspberry Pi Zero class + small touchscreen). This is the primary long-term control surface target. Communicates with rover over Wi-Fi.
