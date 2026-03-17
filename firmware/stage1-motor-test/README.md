# Stage 1 Motor Test Sketch

Minimal bring-up sketch that drives both motors through a fixed test sequence without requiring a BLE app or phone. Use this for first hardware validation before switching to the full BLE baseline.

## Purpose

- Validate that all five control wires are connected correctly.
- Confirm motor spin directions (forward/reverse) for both sides.
- Identify any reversed motors before the production firmware is flashed.

## When to use this

Flash this sketch **before** `firmware/stage1-esp32-baseline/` during Phase 7 of `docs/builds/stage1-rover-a-build.md`. After motor directions are confirmed, reflash the production baseline.

## Pin map (matches frozen Stage 1 map)

| Function | Pin |
|---|---|
| Left motor PWM | GPIO25 |
| Left motor DIR | GPIO26 |
| Right motor PWM | GPIO27 |
| Right motor DIR | **GPIO14** (not GPIO33) |

## Build and flash

```bash
cd firmware/stage1-motor-test
pio run -t upload
pio device monitor -b 115200
```

## Test sequence

The sketch runs automatically on boot:

1. Left motor forward only
2. Left motor reverse only
3. Right motor forward only
4. Right motor reverse only
5. Both forward
6. Both reverse
7. Left turn (left slow, right fast)
8. Right turn (right slow, left fast)

Each step runs for ~1.2 seconds then stops for ~0.6 seconds.

## Expected serial output

```
[MOTOR TEST] Starting.
[MOTOR TEST] WHEELS MUST BE ELEVATED.
[MOTOR TEST] Step 1: Left motor FORWARD (right wheel should be still)
[MOTOR TEST] STOP
[MOTOR TEST] Step 2: Left motor REVERSE (right wheel should be still)
[MOTOR TEST] STOP
... (all 8 steps)
[MOTOR TEST] Sequence complete.
```

## If a motor spins backward

Do NOT swap physical wires. Instead, invert the direction logic for that motor in the production firmware (`writeSide()` in `firmware/stage1-esp32-baseline/src/main.cpp`). Record the observation in `docs/STAGE_1_TUNING.md`.

## Safety

- Always run this sketch with wheels elevated off the ground.
- Keep fingers clear of wheels during the test sequence.
- The test duty is set conservatively (~31% and ~55%) to reduce risk on first power-on.
