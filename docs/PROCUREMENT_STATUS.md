# Procurement Status (Stage 0/1)

_Last updated: 2026-03-17_

Track procurement reality for each critical item before assembly begins.

## Buy now (initial order set from `hardware/bom-stage-0-1.csv`)

| Part | Ordered? | Received? | Inspected? | Notes |
|---|---|---|---|---|
| Pololu Romi Chassis Kit - Blue (Pololu #3506) | Yes | No | No | Arriving Saturday |
| ESP32-DevKitC-32E | Yes | No | No | Arriving tomorrow |
| Pololu Romi Motor Driver and Power Distribution Board (Pololu #3543) | Yes | No | No | Arriving Saturday |
| AA NiMH cell set (6 cells) | Yes | No | No | Arriving tomorrow |
| NiMH smart charger | Yes | No | No | Arriving tomorrow |
| Inline automotive blade fuse holder | Yes | No | No | Arriving tomorrow |
| 5A ATO/ATC blade fuses | Yes | No | No | Arriving tomorrow |
| SPST rocker toggle switch (DC-rated) | Yes | Yes | Yes | Arrived today — inspected OK |
| USB-A to Micro-USB data cable | Yes | No | No | Arriving tomorrow |
| 22 AWG silicone wire kit | Yes | No | No | Arriving tomorrow |
| JST-SM or JST-PH 2-pin connectors / harness | Yes | No | No | Arriving tomorrow |
| Dupont 2.54mm connector kit + crimper | Yes | Yes | Yes | Arrived today — inspected OK. Practice crimps recommended before build. |
| Ring/fork terminals + ferrules kit | Yes | No | No | Arriving tomorrow |
| Heat-shrink tubing assortment | Yes | No | No | Arriving tomorrow |
| Mounting standoffs/spacers + screws | Yes | Yes | Yes | Arrived today — M3 only. See note below. |
| Hook-and-loop straps / cable ties | Yes | No | No | Arriving tomorrow |
| Perfboard / mini protoboard | Yes | No | No | Arriving tomorrow |
| Digital multimeter | Yes | No | No | Arriving tomorrow (or mark N/A if already owned) |

## Resistors (battery voltage divider)

| Part | Received? | Inspected? | Notes |
|---|---|---|---|
| R1 — **22kΩ** (substituted for 20kΩ) | Yes | Yes | Arrived today. 22kΩ substituted for originally specified 20kΩ — safe, see substitution note below. |
| R2 — 10kΩ | Yes | Yes | Arrived today — confirmed present in assortment. |

### Resistor substitution note — 22kΩ for 20kΩ

The available R1 value is 22kΩ rather than the originally specified 20kΩ. This is safe and accepted.

- R1=22kΩ / R2=10kΩ gives a divider ratio of **3.2×** (previously 3.0×)
- Maximum ADC pin voltage at 8.4V pack: **2.625V** (safely within ESP32 3.3V limit)
- The firmware constant `BATTERY_DIVIDER_RATIO` has been updated from `3.0f` to `3.2f` in `firmware/stage1-esp32-baseline/src/main.cpp`
- `docs/STAGE_1_WIRING.md` has been updated to reflect R1=22kΩ
- A one-time calibration against a multimeter reading is still recommended after first power-on (see `docs/STAGE_1_TUNING.md`)

## Standoff note — M3 only, no M2

M3 standoffs arrived. M2 standoffs were not ordered. The Romi chassis mounting holes are M3-compatible so the chassis and Romi Motor Driver board mounting is fine. The ESP32-DevKitC-32E mounting holes are ~2.8mm — M3 screws will not pass through cleanly. Options for ESP32 mounting:
- Double-sided foam tape or adhesive pad (simplest for Stage 1)
- Zip ties through chassis slots
- Order M2.5 standoffs if a more permanent mount is wanted

This does not block Stage 1 build — foam tape is acceptable for first bring-up.

## Included with kit / do not buy separately for initial order

| Part | Ordered? | Received? | Inspected? | Notes |
|---|---|---|---|---|
| Romi motors (included in Pololu #3506 full kit) | N/A | N/A | N/A | Separate purchase is optional spare-only |
| Romi wheels (included in Pololu #3506 full kit) | N/A | N/A | N/A | Separate purchase is optional spare-only |
| Romi caster (included in Pololu #3506 full kit) | N/A | N/A | N/A | Separate purchase is optional spare-only |
| Integrated 6xAA battery holder in Romi chassis | N/A | N/A | N/A | Included in chassis kit |

## Later-stage / not immediate buys

| Part | Ordered? | Received? | Inspected? | Notes |
|---|---|---|---|---|
| Romi Encoder Pair Kit (Pololu #3542) | No | No | No | Stage 3/4 path |
| VL53L1X ToF sensor breakout | No | No | No | Future stage |

## Usage notes

- Update this file immediately after placing orders, receiving packages, and completing inspections.
- Record substitutions explicitly in **Notes** with rationale.
- Keep this file aligned with `hardware/bom-stage-0-1.csv`.
- For initial procurement, buy from the **Buy now** section only.
