# Stage 1 Pin Map (ESP32-DevKitC-32E)

_Last updated: 2026-03-12_

This document freezes exact Stage 1 GPIO assignments for the Espressif ESP32-DevKitC-32E.

## Frozen pin assignments

| Function | ESP32 pin | Direction | Notes |
|---|---|---|---|
| Left motor PWM | GPIO25 | Output | LEDC PWM channel (motor speed left) |
| Left motor direction | GPIO26 | Output | Digital direction control left |
| Right motor PWM | GPIO27 | Output | LEDC PWM channel (motor speed right) |
| Right motor direction | GPIO14 | Output | Digital direction control right |
| Battery ADC sense | GPIO34 (ADC1_CH6) | Input | Input-only pin; battery divider sense |
| Optional status LED | GPIO2 | Output | Optional heartbeat/status blink |
| Reserved I2C SDA | GPIO21 | Bidirectional | Reserved for future Stage 3 sensor |
| Reserved I2C SCL | GPIO22 | Output/open-drain | Reserved for future Stage 3 sensor |

## Why these pins

- GPIO25 and GPIO27 are stable general-purpose output pins with LEDC support and no boot-strapping risk for PWM.
- GPIO26 and GPIO14 are straightforward digital outputs for direction signals.
- GPIO34 is ADC1 (not ADC2), avoiding Wi-Fi/BLE coexistence limitations that can affect ADC2 reads.
- GPIO2 is optional only; the system does not depend on onboard LED behavior.
- GPIO21/GPIO22 match common ESP32 I2C defaults, keeping future sensor integration low-friction.

## Conflict avoidance and constraints

- Avoided ADC2 pins for battery sensing to prevent radio-related ADC conflicts.
- Avoided UART0 pins (GPIO1/GPIO3) to preserve USB serial flashing/logging.
- Avoided boot-strapping-sensitive pins for critical motor safety outputs where possible.
- Direction pins are static digital outputs; PWM is isolated to dedicated LEDC channels.

## Bring-up notes

- Initialize all motor output pins low at startup before BLE is enabled.
- Configure PWM at a conservative frequency suitable for the motor driver (for example 15-20 kHz).
- Ensure deadman timeout sets both PWM channels to 0 and drives safe direction defaults.

