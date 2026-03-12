# Stage 1 Build Plan

_Last updated: 2026-03-12_

This is the practical execution plan to build and validate the Stage 1 manual-control rover.

## Goal

Build a reproducible Stage 1 rover that can be manually driven safely on a flat test surface using BLE teleop, with basic battery reporting and stop mechanisms.

## Build phases

### Phase A: Parts and bench prep

1. Source all Stage 0/1 BOM items.
2. Verify ESP32 board enumerates over USB.
3. Verify motor-driver board power rails and no shorts.
4. Prepare fused/switchable battery harness.

Exit criteria:
- All critical parts in hand.
- Bench power continuity checks pass.

### Phase B: Mechanical assembly

1. Assemble differential-drive chassis.
2. Mount motor driver/power board and ESP32 with standoffs.
3. Install battery holder and accessible main switch.
4. Perform static wiring check against `docs/INTERFACE_MAP.md`.

Exit criteria:
- Mechanical assembly complete.
- Wiring passes continuity + polarity check.

### Phase C: Firmware bring-up

1. Flash minimal firmware scaffold.
2. Validate serial output and command parser.
3. Confirm motor spin test per side at low duty cycle.
4. Implement deadman timeout + software e-stop.
5. Read battery voltage ADC and print scaled estimate.

Exit criteria:
- Teleop commands drive both motors correctly.
- Deadman timeout stops rover reliably.

### Phase D: Drive validation

1. Perform low-speed forward/reverse test.
2. Perform left/right turn test.
3. Perform stop and e-stop test.
4. Run 10-minute indoor manual-drive soak.

Exit criteria:
- Meets `docs/STAGE_1_ACCEPTANCE_TEST.md` pass criteria.

## Risks and mitigations

- BLE command jitter -> use input smoothing and conservative timeout.
- Brownouts under acceleration -> limit ramp rate and verify battery health.
- Wiring errors -> pre-power continuity and polarity checklist.

## Minimum tool list

- Multimeter
- Soldering/termination tools as needed
- USB cable + laptop
- Hex drivers/screwdrivers

## Deliverables produced by this plan

- Assembled Stage 1 rover
- Wiring/pin notes for firmware scaffold
- Initial tuning values (PWM floor, turn scale, timeout)
- Acceptance test results log

## Assumptions

- **Assumption:** Indoor test area is available for first motion tests.
- **Assumption:** Firmware scaffold starts from a clean ESP-IDF or Arduino-ESP32 baseline in the next work session.
