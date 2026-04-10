# Next Steps

_Last updated: 2026-04-10_

## Now (blocked on encoder delivery)

- Install Romi Encoder Pair Kit (#3542) when it arrives.
- Phase 11: First battery power-on — wheels elevated, motor test firmware, press Romi power button + EN reset.
- Phase 12: Motor direction check, then flash production firmware.

## Next

- Execute deadman/e-stop validation; record in `docs/STAGE_1_TUNING.md`.
- Perform battery ADC calibration per `docs/STAGE_1_TUNING.md`.
- Execute `docs/STAGE_1_ACCEPTANCE_TEST.md` and capture pass/fail evidence.
- Tune drivability (PWM floor, turn scaling, deadman timeout).

## Stage 2 (after Stage 1 acceptance)

- Add Wi-Fi transport alongside BLE using the same T,R,H,E,C protocol.
- Build web-based control dashboard.
- Begin mobile app design.
- Start planning handheld physical controller (Pi Zero + screen + joysticks).

## Later

- Mk2/Mk3/Mk4 remain documented planning scope only.
- Front distance sensing (Stage 3), IMU (Stage 4).
- Telemetry logging, higher-level control loops.
- Handheld physical controller as primary long-term control surface.

## Blocked

- **Phase 11–13:** Waiting on Romi Encoder Pair Kit (#3542) for motor connection.
- Final naming/branding.
- Autonomy stack before Stage 1 completion.
- All control surface work until Stage 2.
