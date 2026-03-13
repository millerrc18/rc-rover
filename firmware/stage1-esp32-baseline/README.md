# Stage 1 ESP32 Firmware Baseline

Minimal bench-bring-up firmware for ESP32-DevKitC-32E.

## Scope included

- BLE teleop command intake (`T,R,H,E,C` packet)
- Differential motor mixing
- Motor output abstraction and safe startup stop
- Deadman timeout safety stop
- E-stop latch and explicit clear behavior
- Battery ADC sampling/reporting over serial

## Pin map (frozen Stage 1)

- Left PWM: GPIO25
- Left DIR: GPIO26
- Right PWM: GPIO27
- Right DIR: GPIO14
- Battery ADC: GPIO34

## Build and flash

```bash
cd firmware/stage1-esp32-baseline
pio run
pio run -t upload
pio device monitor -b 115200
```

## BLE command write format

Write command strings to the BLE command characteristic:

`T:<throttle>,R:<turn>,H:<heartbeat>,E:<estop>,C:<estop_clear>`

Example:

`T:0.20,R:-0.10,H:42,E:0,C:0`

## Bench safety

- Start with wheels elevated.
- Confirm zero output at boot before sending commands.
- Verify deadman and e-stop before floor testing.
