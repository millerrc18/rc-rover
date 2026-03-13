# Stage 1 Wiring Diagram

_Last updated: 2026-03-12_

This document freezes the exact Stage 1 wiring for first bench bring-up and untethered driving.

## Stage 1 power and wiring path

```mermaid
flowchart LR
    BATT[6x AA NiMH pack] --> FUSE[Inline fuse 5A-7.5A]
    FUSE --> SW[Main power switch]
    SW --> VIN[Motor Driver/Power Board VIN]

    VIN --> L_MOTOR[Left motor]
    VIN --> R_MOTOR[Right motor]

    VIN --> REG5[5V regulated output]
    REG5 --> ESP5V[ESP32-DevKitC-32E 5V pin]

    ESP_GND[ESP32 GND] --- VIN_GND[Motor board GND common]

    VIN --> DIV_TOP[R1 divider]
    DIV_TOP --> ADC_NODE[ADC sense node]
    ADC_NODE --> DIV_BOT[R2 divider to GND]
    ADC_NODE --> ESP_ADC[ESP32 GPIO34 ADC1]

    USB[USB-A to Micro-USB cable] --> ESP_USB[ESP32 USB port]

    NOTE1[Bench mode: USB powers ESP32]
    NOTE2[Untethered mode: battery powers ESP32 via REG5 -> 5V pin]
    NOTE1 -.-> ESP_USB
    NOTE2 -.-> ESP5V
```

## Stage 1 control and signal path

```mermaid
flowchart LR
    PHONE[BLE teleop app] -->|throttle, turn, heartbeat, estop| ESP[ESP32 control loop]

    ESP -->|GPIO25 PWM| LPWM[Left PWM input]
    ESP -->|GPIO26 DIR| LDIR[Left DIR input]
    ESP -->|GPIO27 PWM| RPWM[Right PWM input]
    ESP -->|GPIO14 DIR| RDIR[Right DIR input]

    LPWM --> DRIVER[Motor driver board]
    LDIR --> DRIVER
    RPWM --> DRIVER
    RDIR --> DRIVER

    DRIVER --> LM[Left motor]
    DRIVER --> RM[Right motor]

    ESP -->|ADC read GPIO34| BATTMON[Battery voltage estimate]
```

## Exact connection list

1. Battery `+` -> inline fuse input.
2. Fuse output -> main switch input.
3. Main switch output -> motor board VIN.
4. Battery `-` -> motor board GND.
5. Motor board regulated `5V` -> ESP32 `5V` pin (untethered operation path).
6. Motor board GND -> ESP32 GND (shared logic/motor ground).
7. Left motor leads -> motor board left outputs (`M1A/M1B` equivalent).
8. Right motor leads -> motor board right outputs (`M2A/M2B` equivalent).
9. ESP32 GPIO25 -> left motor PWM input on motor board.
10. ESP32 GPIO26 -> left motor direction input on motor board.
11. ESP32 GPIO27 -> right motor PWM input on motor board.
12. ESP32 GPIO14 -> right motor direction input on motor board.
13. Battery sense divider top node from switched VIN -> R1 -> ADC node.
14. ADC node -> ESP32 GPIO34.
15. ADC node -> R2 -> GND.
16. Optional filter capacitor from ADC node to GND near ESP32.
17. USB-A to Micro-USB cable from laptop -> ESP32 USB connector for flashing/debug and bench power.

## Continuity checklist (power off)

- [ ] Battery `+` has continuity to fuse input only.
- [ ] Fuse output has continuity to switch input only.
- [ ] Switch output has continuity to motor board VIN only.
- [ ] Battery `-`, motor board GND, and ESP32 GND are common.
- [ ] No continuity between switched VIN and GND with switch OFF.
- [ ] Divider chain continuity: VIN -> R1 -> ADC node -> R2 -> GND.
- [ ] Left motor and right motor channels are not shorted together.

## Polarity checklist

- [ ] Battery polarity marked and verified before mate.
- [ ] VIN and GND to motor board not reversed.
- [ ] Motor board 5V output orientation verified before wiring ESP32 5V pin.
- [ ] USB cable is data-capable and connector orientation is correct (Micro-USB at ESP32).
- [ ] ADC divider lower leg returns to GND, not VIN.

## Pre-power inspection checklist

- [ ] Fuse installed and rated for initial low-speed testing (5A preferred start).
- [ ] Wheels elevated for first powered motor test.
- [ ] Main switch reachable by operator during test.
- [ ] No exposed conductor can short against chassis hardware.
- [ ] Motor wires secured away from rotating wheels.
- [ ] BLE app ready with deadman heartbeat enabled.
- [ ] Firmware default boot state confirmed to zero motor output.
- [ ] Serial monitor prepared to observe battery ADC and fault messages.

