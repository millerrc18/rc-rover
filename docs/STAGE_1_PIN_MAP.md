# Stage 1 Pin Map (ESP32-DevKitC-32E)

_Last updated: 2026-03-17_

This document freezes exact Stage 1 GPIO assignments for the Espressif ESP32-DevKitC-32E.

## Frozen pin assignments

| Function | ESP32 pin | Direction | Notes |
|---|---|---|---|
| Left motor PWM | GPIO25 | Output | LEDC PWM channel (motor speed left) |
| Left motor direction | GPIO26 | Output | Digital direction control left |
| Right motor PWM | GPIO27 | Output | LEDC PWM channel (motor speed right) |
| Right motor direction | GPIO14 | Output | Digital direction control right — see boot-strapping note below |
| Battery ADC sense | GPIO34 (ADC1_CH6) | Input | Input-only pin; battery divider sense |
| Optional status LED | GPIO2 | Output | Optional heartbeat/status blink |
| Reserved I2C SDA | GPIO21 | Bidirectional | Reserved for future Stage 3 sensor |
| Reserved I2C SCL | GPIO22 | Output/open-drain | Reserved for future Stage 3 sensor |

## Why these pins

- GPIO25 and GPIO27 are stable general-purpose output pins with LEDC support and no boot-strapping risk for PWM.
- GPIO26 is a straightforward digital output for a direction signal.
- GPIO34 is ADC1 (not ADC2), avoiding Wi-Fi/BLE coexistence limitations that can affect ADC2 reads.
- GPIO2 is optional only; the system does not depend on onboard LED behavior.
- GPIO21/GPIO22 match common ESP32 I2C defaults, keeping future sensor integration low-friction.

## GPIO14 — boot-strapping pin notice

GPIO14 is used for the right motor direction output. GPIO14 is a boot-strapping pin on the ESP32 that is sampled during reset to set the SPI flash clock frequency.

**Why this is safe in Stage 1:**
- The direction output is initialized LOW at startup in the firmware before any BLE or motor commands are processed.
- The Romi Motor Driver board's M2DIR input presents a high-impedance load that does not pull the pin HIGH during boot.
- No pull-up resistor is used or should be added to this line.

**What would make it unsafe:**
- Adding an external pull-up resistor to GPIO14 could set the flash clock to a non-standard frequency at boot, causing boot failures.
- If the Romi board M2DIR input ever pulls this line HIGH through unexpected circuitry, re-evaluate the pin assignment.

**Decision:** GPIO14 is accepted for Stage 1 with the LOW-init constraint documented. If boot instability is observed during hardware bring-up, the fallback assignment is GPIO33 (which requires updating the firmware `config::PIN_RIGHT_DIR` constant and reflashing). Log any such change in `docs/DECISIONS.md`.

## Conflict avoidance and constraints

- Avoided ADC2 pins for battery sensing to prevent radio-related ADC conflicts.
- Avoided UART0 pins (GPIO1/GPIO3) to preserve USB serial flashing/logging.
- GPIO14 accepted for direction output (static LOW-init output); no pull-up to be added.
- Direction pins are static digital outputs; PWM is isolated to dedicated LEDC channels.
- GPIO33 is **not** used in Stage 1. An earlier draft of the build guide incorrectly assigned GPIO33 to M2DIR. The frozen assignment is GPIO14. See `docs/builds/stage1-rover-a-build.md` for the corrected wiring guide.

## Bring-up notes

- Initialize all motor output pins low at startup before BLE is enabled.
- Configure PWM at a conservative frequency suitable for the motor driver (18 kHz per firmware config).
- Ensure deadman timeout sets both PWM channels to 0 and drives safe direction defaults.
- GPIO14 must be LOW at startup — this is the firmware default and matches safe direction state.
