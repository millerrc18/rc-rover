# Stage 1 Rover A — Physical Build Guide

_Last updated: 2026-03-17_

> **Board notice:** This guide targets the **Pololu Romi Motor Driver and Power Distribution Board (#3543)** exclusively. If you have any version of this guide that mentions `AIN1`, `AIN2`, `BIN1`, `BIN2`, `OUT1`–`OUT4`, or GPIO33 for M2DIR, discard it and use this file only.

---

# 1. Build Overview

## Objective

Build Rover A Stage 1 as a safe, working, manually controlled differential-drive rover using:
- Romi chassis kit (Pololu #3506, blue)
- Pololu Romi Motor Driver and Power Distribution Board (#3543)
- ESP32-DevKitC-32E
- 6× AA NiMH cells

## What you are building

One motor drives the left wheel, one motor drives the right wheel. The Romi Motor Driver board sits on the chassis, drives both motors, and supplies regulated 5V logic power to the ESP32. The ESP32 sends PWM and direction signals to the motor driver board via jumper wires.

## Key facts about the Romi Motor Driver board

Before you start, understand what this board does and does not do automatically:

- **Motors connect through the chassis** — the board has female headers that mate with the motor tabs when pressed into the chassis. No separate motor wire routing needed, but the headers must be **soldered to the board first** (before mounting).
- **Battery contacts must be soldered** — after the board is mounted, you solder the four battery terminal tabs to the board to establish the electrical and mechanical connection.
- **6-cell series jumper required** — the Romi battery compartment is split into a 4-cell section and a 2-cell section. A short jumper wire must be soldered to connect them in series for full 7.2V nominal.
- **The board has a built-in latching power button** — one press turns power on, another turns it off. This is your primary power switch. Your SPST toggle switch can be wired externally in parallel as an additional cutoff, but the board's built-in button handles normal operation.
- **Control signals need 5 jumper wires** — from ESP32 GPIO pins to the board's control header pins.
- **Regulated 5V output** on the board powers the ESP32 in untethered operation.

## Correct build order

The build must follow this sequence. Doing steps out of order creates rework:

1. Toolchain setup and ESP32 verification
2. Solder headers and motor connectors to the Romi board **on the bench** before mounting
3. Mechanical chassis assembly
4. Mount board into chassis; solder battery contacts
5. Solder 6-cell series jumper
6. Mount and secure ESP32
7. Wire ESP32 control signals to Romi board
8. Wire ESP32 logic power from Romi board
9. Build battery voltage divider
10. Pre-power checklist
11. First power-on (USB only)
12. First battery power-on
13. Motor direction verification and production firmware flash
14. Drive validation

---

# 2. System Architecture

Three paths must all be correct:

**Power path:** Battery cells → chassis contacts (soldered to Romi board) → Romi motor drivers → motors. Also: Romi board regulated 5V → ESP32 5V pin.

**Control path:** ESP32 GPIO pins → jumper wires → Romi board control headers → motor driver ICs → motors.

**Ground path (critical):** ESP32 GND and Romi board GND must share a jumper wire. Without this, control signals will not work.

---

# 3. Tools Required

**Mandatory:**
- Soldering iron with temperature control (650–720°F / 340–380°C for battery contacts; 600–650°F / 315–340°C for headers)
- Rosin-core solder, 60/40 or 63/37, 0.6–0.8mm diameter
- Tip cleaner (brass wool preferred)
- Small Phillips screwdriver
- Wire stripper
- Multimeter

**Helpful:**
- Helping hands or PCB holder
- Flush cutters
- Heat-resistant mat

---

# 4. Parts Identification

**Romi chassis kit (#3506, blue)**
- Main blue chassis plate with integrated 6× AA battery compartment (split 4+2 sections)
- Two DC gear motors with wire leads
- Two drive wheels
- Ball caster assembly
- Hardware bag
- Four individual battery contact terminals (spring type)
- Two double-sided battery contacts (long cross-shaped, bridge the sections)

**Pololu Romi Motor Driver and Power Distribution Board (#3543)**
- Compact PCB with white chassis connector on underside
- Built-in latching power button (small tactile button)
- Two low-profile female headers included in packaging (for motor connections)
- Control header holes: M1PWM, M1DIR, M2PWM, M2DIR, GND, 5V

**Consumables needed:**
- Male 0.1" pin headers for control signal headers (check if any shipped with the board)
- Short wire ~5cm for 6-cell series jumper
- 5× Dupont jumper wires
- R1: 22kΩ resistor
- R2: 10kΩ resistor
- 100nF ceramic capacitor (optional noise filter)
- Small perfboard or mini breadboard for voltage divider

---

# 5. PHASED BUILD INSTRUCTIONS

---

## PHASE 0 — Toolchain Setup and ESP32 Verification

### Goal
Confirm the ESP32 flashes and your development tools work before any hardware assembly.

### Install PlatformIO
1. Install [Visual Studio Code](https://code.visualstudio.com/).
2. Open VS Code → Extensions → search "PlatformIO IDE" → install.
3. Restart VS Code.

### Verify the ESP32
1. Connect ESP32 to laptop via USB-A to Micro-USB cable.
2. Confirm a serial port appears (Device Manager on Windows; `ls /dev/tty*` on Mac/Linux).
3. Navigate to `firmware/stage1-motor-test/` in a terminal.
4. Run `pio run` — compiles the sketch (first run downloads ESP32 toolchain, ~5 min).
5. Run `pio run -t upload` to flash.
6. Run `pio device monitor -b 115200` and confirm you see:
```
[MOTOR TEST] Starting.
[MOTOR TEST] WHEELS MUST BE ELEVATED.
[MOTOR TEST] Step 1: Left motor FORWARD ...
```
Motors won't move yet — no motor power connected. This just confirms the toolchain and ESP32 are working.

### Stop condition
Stop Phase 0 only when the ESP32 flashes and serial output is confirmed.

---

## PHASE 1 — Solder Romi Motor Driver Board (BENCH — before chassis assembly)

### Goal
Complete all soldering to the Romi board while it is off the chassis. Access is much better now than after mounting.

### What to solder

**A. Motor connection female headers**
The board ships with two low-profile female headers. These allow the motor tabs to plug in automatically when the board seats into the chassis.

1. Insert the female headers into the motor connection holes on the front edge of the board (the two sets of holes positioned over where the motors will sit).
2. Solder from the bottom side. Tack one pin first, check alignment, then solder the rest.
3. Temperature: 650°F / 340°C.
4. Inspect: headers should be flush and perpendicular.

**B. Control signal male headers**
Solder a row of male 0.1" header pins into the control signal holes so Dupont jumper wires can connect.
You need at minimum: M1PWM, M1DIR, M2PWM, M2DIR, GND, 5V.

1. Insert male pins from the top side.
2. Use a spare breadboard to hold pins perpendicular while soldering.
3. Solder from the bottom side.
4. Temperature: 620°F / 325°C.

### Soldering reminders
- Tin the tip before starting. Wipe on brass wool, add a tiny bit of fresh solder to the tip.
- Heat pad and pin together 1–2 seconds, then feed solder to the joint (not the iron).
- A good joint is shiny and volcano-shaped. A cold joint is dull and blobby.
- 2–3 seconds per joint max.

### What NOT to solder yet
Do not solder the battery contacts — those are done after mounting.

### Stop condition
Stop Phase 1 only when both motor female headers and all control signal male headers are soldered and visually inspected.

---

## PHASE 2 — Mechanical Chassis Assembly

### Goal
Build a straight, freely rolling chassis before adding electronics.

### Steps
1. Place chassis flat with battery compartment facing up.
2. Install ball caster in the rear mounting hole. Snug, not over-tightened.
3. Insert the two double-sided battery contacts into the battery compartment channels from the underside.
4. Place the four individual battery contact terminals into the battery box from the top. They should rest loosely in their slots — they will be soldered later.
5. Press left motor into its motor clip until it clicks and is secure.
6. Press right motor into its motor clip until it clicks.
7. Snap left wheel onto left motor shaft (align the D-flat first).
8. Snap right wheel onto right motor shaft.
9. Roll rover forward and backward by hand. Check for binding.

### Stop condition
Rover rolls freely with no scraping or binding.

---

## PHASE 3 — Mount Romi Motor Driver Board and Solder Battery Contacts

### Goal
Mount the prepared Romi board and complete the battery contact soldering.

### Mount the board
1. Confirm no batteries are installed.
2. Orient the Romi Motor Driver board with the underside connector aligned to the chassis connector.
3. Press the board down firmly and evenly until fully seated. The motor tabs will engage the female headers from Phase 1.
4. Secure with the included #2-56 screws and nuts (two screws, front corners of the board).

### Solder the battery contacts
5. The four battery contact terminals are now accessible through the board's battery contact slots.
6. Apply iron to each terminal tab and pad together for 1.5–2 seconds, then feed solder.
7. Temperature: 680–720°F / 360–380°C — these joints need more heat due to thermal mass.
8. Work quickly — prolonged heat near the battery compartment plastic can deform the chassis.
9. Inspect each joint. Should be solid and shiny.

### Stop condition
Board mounted securely, all four battery contacts soldered.

---

## PHASE 4 — Solder 6-Cell Series Jumper

### Goal
Connect the two battery sections in series for full 6-cell (7.2V nominal) power.

### Why this is needed
The Romi battery compartment has a 4-cell section and a 2-cell section. Without a jumper they are isolated. A short wire connects them in series.

### Steps
1. Cut a short wire (~5cm), strip and tin both ends.
2. Identify the battery jumper pad locations on the Romi board (labeled Bat Jmp on the board or see Pololu schematic).
3. Solder one end to the BAT1− pad and the other end to the BAT2+ pad.
4. Gentle tug to confirm secure.

> **Warning:** Do not bridge BAT1− to GND without first disconnecting BAT1− from BAT2+. That would short the BAT2 cells across the board. The standard 6-series configuration only connects BAT1− to BAT2+.

### Stop condition
Series jumper in place and confirmed.

---

## PHASE 5 — Mount and Secure ESP32

### Goal
Mount the ESP32 on the chassis with USB port accessible and jumper wires able to reach the Romi board headers.

### Mounting (M2 standoffs not available — use foam tape)
1. Place ESP32 in planned deck position with USB connector facing outward.
2. Confirm five jumper wires can reach M1PWM, M1DIR, M2PWM, M2DIR, GND on the Romi board.
3. Apply two pieces of double-sided foam tape to the underside of the ESP32.
4. Press firmly onto the chassis. Hold 20–30 seconds.
5. Gentle tug to confirm secure.

> M2.5 standoffs fit the ESP32 mounting holes if a more permanent mount is needed later. Foam tape is fully adequate for Stage 1.

### Stop condition
ESP32 is secure and USB port is unobstructed.

---

## PHASE 6 — Wire ESP32 Control Signals

### Goal
Connect the five jumper wires from ESP32 GPIO pins to the Romi Motor Driver board.

### Frozen Stage 1 wiring map

| ESP32 pin | Romi Motor Driver pin | Function |
|---|---|---|
| GPIO25 | M1PWM | Left motor speed |
| GPIO26 | M1DIR | Left motor direction |
| GPIO27 | M2PWM | Right motor speed |
| GPIO14 | M2DIR | Right motor direction |
| GND | GND | Shared ground (mandatory) |

> **GPIO14 note:** GPIO14 is a boot-strapping pin. The firmware initializes it LOW at startup — safe. Do not add a pull-up resistor to this line.

### Steps
1. Confirm all power off, no batteries.
2. Connect GPIO25 → M1PWM.
3. Connect GPIO26 → M1DIR.
4. Connect GPIO27 → M2PWM.
5. Connect GPIO14 → M2DIR.
6. Connect any ESP32 GND pin → Romi board GND.
7. Tug each wire to confirm seated.
8. Confirm no wire can contact the wheels.

### Stop condition
All five wires connected and verified against the table.

---

## PHASE 7 — Wire ESP32 Logic Power

### Goal
Connect the Romi board's regulated 5V output to the ESP32 for untethered operation.

### Steps
1. Confirm all power off.
2. Run a jumper wire from Romi board 5V header pin → ESP32 5V pin.
3. Confirm the GND wire from Phase 6 is still seated (it serves as the shared ground for this path too).

> Connects to the ESP32 5V pin specifically — not 3.3V, not VIN.

### Stop condition
5V power wire connected.

---

## PHASE 8 — Build Battery Voltage Divider

### Goal
Build the resistor divider that scales battery voltage to a safe level for the ESP32 ADC input.

### Components
| Component | Value |
|---|---|
| R1 | 22kΩ |
| R2 | 10kΩ |
| C1 | 100nF ceramic (optional) |

Ratio: 3.2×. Max ADC voltage at 8.4V pack: 2.625V — within ESP32's 3.3V limit.

### Steps
1. On a small piece of perfboard or breadboard:
2. Connect one end of R1 to the battery voltage sense tap (VBAT or VSW test point on the Romi board).
3. Connect the other end of R1 to a node — this is your ADC node.
4. Connect one end of R2 from the ADC node to GND.
5. Run a wire from the ADC node to ESP32 GPIO34.
6. Optional: place a 100nF cap from the ADC node to GND near the ESP32 pin.
7. With batteries in and power on, measure the ADC node with your multimeter. Should be approximately battery voltage ÷ 3.2.

### Stop condition
Divider built, wired to GPIO34, and multimeter reading confirmed plausible.

---

## PHASE 9 — Pre-Power Checklist

### Continuity checks (multimeter, power off, no batteries)
- [ ] GPIO25 → M1PWM: continuity confirmed
- [ ] GPIO26 → M1DIR: continuity confirmed
- [ ] GPIO27 → M2PWM: continuity confirmed
- [ ] GPIO14 → M2DIR: continuity confirmed
- [ ] ESP32 GND → Romi GND: continuity confirmed
- [ ] Romi 5V → ESP32 5V pin: continuity confirmed
- [ ] No signal wire has continuity to GND
- [ ] ADC divider chain: tap → R1 → ADC node → R2 → GND confirmed
- [ ] ADC node → GPIO34: continuity confirmed

### Visual checks
- [ ] All four battery contacts soldered with no cold joints
- [ ] 6-cell series jumper in place
- [ ] Motor female headers soldered, no cold joints
- [ ] No exposed wire strands near adjacent pins
- [ ] ESP32 secure on foam tape
- [ ] All jumper wires clear of wheels
- [ ] USB port accessible

### Stop condition
All checklist items confirmed.

---

## PHASE 10 — First Power-On (USB only, no batteries)

### Goal
Confirm firmware boots before introducing battery power.

### Steps
1. No batteries installed.
2. Connect USB-A to Micro-USB from laptop to ESP32.
3. Flash motor test sketch if not already done:
```bash
cd firmware/stage1-motor-test
pio run -t upload
pio device monitor -b 115200
```
4. Confirm serial output shows the motor test sequence.
5. No motor movement will occur — no motor power without batteries.
6. Confirm no heat.

### Stop condition
Serial output clean, no heat observed.

---

## PHASE 11 — First Battery Power-On

### Goal
Introduce battery power and confirm safe idle behavior.

### Steps
1. Keep wheels elevated.
2. Install 6× AA NiMH cells, observing polarity markings.
3. Press the Romi board's built-in power button once to turn power on.
4. Connect USB for serial monitoring.
5. Motor test sequence runs automatically — wheels will try to spin.
6. Observe for heat or smell. Power off immediately (press button again) if either occurs.

### Warning signs — press power button immediately
- Any component hot within seconds
- Burning smell or smoke
- Uncontrolled wheel motion before the test sequence begins

### Stop condition
Battery-powered operation stable and safe through the motor test sequence.

---

## PHASE 12 — Motor Direction Check and Production Firmware Flash

### Goal
Confirm motor spin directions, then switch to production BLE firmware.

### Steps
1. With wheels elevated and rover battery-powered, observe the serial output step labels and watch each wheel.
2. Note any motor that spins backward relative to expected direction.
3. If a motor is reversed, correct it in `firmware/stage1-esp32-baseline/src/main.cpp` by inverting the `forward` flag in `writeSide()` for that channel. Do not swap physical wires.
4. Flash production firmware:
```bash
cd firmware/stage1-esp32-baseline
pio run -t upload
pio device monitor -b 115200
```
5. Confirm serial shows:
```
state=DEADMAN,ble=0,thr=0.00,turn=0.00,hb=0,batt=X.XXV
```
6. Confirm battery voltage reading is plausible (6.0–8.4V range). If far off, perform ADC calibration in `docs/STAGE_1_TUNING.md`.
7. Install nRF Connect on your phone. Scan for `rc-rover-stage1` and confirm BLE is advertising.

### Stop condition
Production firmware running, BLE advertising, battery telemetry plausible.

---

## PHASE 13 — Drive Validation

### Goal
Confirm controlled motion on a flat surface.

### Safety checks first (wheels elevated)
1. Send one BLE command, wait >300ms, confirm motors stop (deadman).
2. Send `T:0.00,R:0.00,H:1,E:1,C:0` — confirm ESTOP_LATCHED in serial.
3. Send `T:0.00,R:0.00,H:2,E:0,C:1` — confirm ESTOP_CLEARED in serial.

### Floor test
4. Place rover on flat surface.
5. Drive forward at low throttle (T:0.15). Check straight-line tracking.
6. Drive reverse.
7. Test left and right turns.
8. Run a 5-minute low-speed indoor soak.

### Troubleshooting
- **One motor not responding:** Check that motor's PWM and DIR wires. Check serial for CMD_PARSE_ERROR.
- **Neither motor responding:** Check shared GND wire first. Always.
- **Motors stop immediately:** Deadman timeout. Commands must be sent continuously at 20–50 Hz — a single BLE write will not sustain motion.
- **Rover pulls left or right:** PWM floor difference — see `docs/STAGE_1_TUNING.md`.
- **Forgot to press power button:** The Romi board has a latching button — press it once to turn power on.

### Stop condition
Rover drives forward, reverse, left, and right under control with clean stops.

---

# 6. Wiring Reference

### Power path (through chassis — no manual motor wiring)
Battery cells → chassis contacts (soldered) → Romi Motor Driver board → motors

### ESP32 logic power (untethered)
Romi board 5V pin → ESP32 5V pin + shared GND

### ESP32 logic power (bench)
Laptop USB → ESP32 Micro-USB

### Control wires (5 jumper wires)
| From (ESP32) | To (Romi Motor Driver) | Function |
|---|---|---|
| GPIO25 | M1PWM | Left motor speed |
| GPIO26 | M1DIR | Left motor direction |
| GPIO27 | M2PWM | Right motor speed |
| GPIO14 | M2DIR | Right motor direction |
| GND | GND | Shared ground |

### Battery voltage divider
Battery tap → R1 (22kΩ) → ADC node → ESP32 GPIO34
ADC node → R2 (10kΩ) → GND
Optional: 100nF cap from ADC node to GND

---

# 7. Common Mistakes

- **Soldering battery contacts before mounting the board.** Battery contacts must be soldered after the board is in the chassis.
- **Skipping the 6-cell series jumper.** Without it the battery pack is split and you get no power or half voltage.
- **Forgetting to press the Romi board power button.** Power does not flow until you press the built-in latching button once.
- **Missing shared GND wire.** Single most common cause of nothing works.
- **Using GPIO33 instead of GPIO14 for M2DIR.** The frozen pin is GPIO14.
- **Adding a pull-up resistor to GPIO14.** Do not do this.
- **Powering ESP32 from raw battery voltage.** Use Romi board regulated 5V → ESP32 5V pin.
- **Sending a single BLE command expecting sustained motion.** Deadman stops motors after 300ms. Commands must repeat at 20–50 Hz.
- **Floor testing before wheel-off-ground validation is complete.**

---

# 8. Build Completion Checklist

### Soldering
- [ ] Motor connection female headers soldered to Romi board (before mounting)
- [ ] Control signal male headers soldered to Romi board (before mounting)
- [ ] All four battery contacts soldered (after mounting in chassis)
- [ ] 6-cell series jumper soldered
- [ ] All joints inspected — no cold or bridged joints

### Mechanical
- [ ] Rover rolls freely by hand
- [ ] Romi Motor Driver board fully seated and screwed in
- [ ] ESP32 secure on foam tape, USB accessible

### Wiring
- [ ] All five control jumper wires per frozen pin map (GPIO25/26/27/14/GND)
- [ ] GPIO14 used for M2DIR (not GPIO33)
- [ ] Shared GND wire present
- [ ] Romi board 5V → ESP32 5V pin connected
- [ ] Battery divider built (R1=22kΩ / R2=10kΩ) and wired to GPIO34
- [ ] All wires clear of wheels

### Firmware and validation
- [ ] PlatformIO installed and working
- [ ] ESP32 flashes successfully
- [ ] Motor test sketch confirms both motors respond correctly
- [ ] Production firmware running; serial shows DEADMAN state and battery voltage
- [ ] Battery voltage plausible; ADC calibrated if needed (see STAGE_1_TUNING.md)
- [ ] BLE advertising as rc-rover-stage1
- [ ] Deadman timeout confirmed working
- [ ] E-stop latch and clear confirmed working
- [ ] Forward, reverse, left, right all work on flat surface
- [ ] No unusual heat or smell during tests
