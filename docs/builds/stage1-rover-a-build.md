# Stage 1 Rover A — Physical Build Guide

_Last updated: 2026-03-17_

> **Board notice:** This guide targets the **Pololu Romi Motor Driver and Power Distribution Board (#3543)** exclusively. An earlier draft of this guide incorrectly referenced a generic DRV8833 breakout board with different terminal names and a different wiring approach. If you have any version of this guide that mentions `AIN1`, `AIN2`, `BIN1`, `BIN2`, `OUT1`–`OUT4`, or GPIO33, discard it and use this file only.

---

# 1. Build Overview

## Objective

Build Rover A Stage 1 as a safe, working, manually controlled differential-drive rover using:
- Romi chassis kit (Pololu #3506, blue)
- Pololu Romi Motor Driver and Power Distribution Board (#3543)
- ESP32-DevKitC-32E
- 6× AA NiMH cells

## What you are building (simple explanation)

You are building a small two-wheel rover.
One motor drives the left wheel.
One motor drives the right wheel.
The battery provides power.
The Romi Motor Driver board sits on the chassis, drives both motors, and also supplies regulated 5V logic power to the ESP32.
The ESP32 sends PWM and direction signals to the motor driver board.

## Key facts about the Romi Motor Driver board

The Romi Motor Driver and Power Distribution Board (#3543) is designed to snap directly into the Romi chassis. This means:

- The **motors connect through the chassis connectors**, not through separate screw terminals you wire manually.
- The **battery pack connects through the chassis battery contacts**, not through separate power wires you wire manually.
- You **do** need to wire the four ESP32 control signals (two PWM pins, two direction pins) and the shared ground using jumper wires to the board's labeled header pins.
- The board provides a **regulated 5V output** that powers the ESP32 during untethered operation.

## Final expected outcome

At the end of this guide you should have:
- A fully assembled rolling chassis with the Romi Motor Driver board snapped in.
- ESP32 control signals wired to the motor driver board headers.
- Safe power setup confirmed for first tests.
- Basic motor movement confirmed (forward, reverse, turning).

![Completed Rover Top View](../assets/images/stage1_rover_complete_top.png)
_What this image should show: a top-down view of the finished Stage 1 rover with labeled ESP32, Romi Motor Driver board, battery compartment, and both drive wheels._

---

# 2. System Architecture (Simple Explanation)

Think of the rover as three paths that must all be correct.

**Power path:** battery contacts in chassis → Romi Motor Driver board → motors (through chassis connectors) and regulated 5V output → ESP32.

**Control path:** ESP32 GPIO pins → Romi Motor Driver board control headers → motor outputs.

**Ground path (critical):** ESP32 GND and Romi Motor Driver board GND must be connected by a wire. This gives both boards the same electrical reference. Without a shared ground, control signals will fail or behave randomly even if all other wiring looks correct.

![Power Control Ground Diagram](../assets/images/stage1_power_control_ground_paths.png)
_What this image should show: a simple block diagram with three colored paths: battery contacts through the chassis to the Romi board to the motors; ESP32 GPIO pins to Romi board control headers; and one bold shared ground line between ESP32 and the Romi board._

---

# 3. Tools Required

Required:
- Small Phillips screwdriver (for chassis assembly screws).
- Small flat screwdriver (for any board mounting hardware).
- Wire stripper (for clean wire ends on jumper wires).

Optional but strongly recommended:
- Multimeter (for polarity and continuity checks before first power-on).
- Soldering iron (only if your jumper wire connections need hardened joints; Dupont/pin connections are fine for Stage 1).

---

# 4. Parts Identification

Before assembly, place all parts on a table and identify each one.

**Romi chassis kit (#3506, blue)**
- Main blue chassis plate with integrated 6× AA battery compartment.
- Two DC gear motors with leads already attached to motor tabs.
- Two drive wheels.
- Ball caster assembly.
- Hardware bag (screws, nuts, spacers).

**Pololu Romi Motor Driver and Power Distribution Board (#3543)**
- A compact PCB designed to snap directly into the Romi chassis.
- Has a white rectangular board-to-board connector that mates with the chassis.
- Key labeled header pins visible on the board surface:
  - `M1PWM`, `M1DIR` — left motor control inputs
  - `M2PWM`, `M2DIR` — right motor control inputs
  - `GND` — ground reference
  - `5V` — regulated 5V output (powers ESP32 in untethered operation)
- Also has VIN contacts that receive battery power directly from the chassis contacts.

**ESP32-DevKitC-32E**
- Small microcontroller board with two rows of GPIO pins along the sides.
- Has a Micro-USB connector for bench power and firmware flashing.
- Pin labels are printed on the board near each pin.

**6× AA NiMH cells**
- Load these into the Romi chassis battery compartment after mechanical assembly.

**Jumper wires**
- You need five jumper wires: four for control signals, one for shared ground.
- Female-to-female or male-to-female Dupont wires depending on your header types.

![Parts Flat Lay](../assets/images/stage1_parts_identification_flatlay.png)
_What this image should show: all major parts laid out on a bench with text labels pointing to the Romi chassis, Romi Motor Driver board, ESP32, NiMH cells, and jumper wires._

---

# 5. PHASED BUILD INSTRUCTIONS

## PHASE 1 — Mechanical Assembly (NO electronics)

### Goal
Build a straight, freely rolling rover chassis before adding any electronics.

### Parts used
- Romi chassis and all hardware in the kit bag.
- Two drive wheels.
- Ball caster assembly.

### Step-by-step instructions

1. Place the Romi chassis on a flat table with the battery compartment facing up.
2. Install the ball caster in the rear caster mounting hole using the included hardware. Tighten snugly but do not strip the plastic.
3. Snap the left wheel onto the left motor shaft. The wheel should click into place.
4. Snap the right wheel onto the right motor shaft. The wheel should click into place.
5. Set the chassis on the table and gently roll it forward by hand.
6. Roll it backward by hand.

### How to verify alignment
- Look from the front: wheels should be parallel with equal spacing from the chassis edges.
- Push the rover forward slowly on a flat surface: it should not strongly pull left or right.
- Both wheels should spin freely by hand with no grinding or binding.

### What NOT to do
- Do not install any wires or boards in this phase.
- Do not force wheels if shaft fit feels wrong — check that the D-shaped shaft flat is aligned to the wheel hub flat before pushing.
- Do not over-tighten caster hardware into plastic.

### Stop condition
Stop Phase 1 only when the rover rolls freely on a flat surface with no scraping or binding.

---

## PHASE 2 — Electronics Layout Planning (NO wiring yet)

### Goal
Decide where the Romi Motor Driver board and ESP32 will sit before making any connection.

### Parts used
- ESP32-DevKitC-32E.
- Romi Motor Driver and Power Distribution Board (#3543).
- Chassis from Phase 1.

### The Romi Motor Driver board placement is fixed

Unlike a generic breakout board, the Romi Motor Driver and Power Distribution Board mounts in one specific location: it snaps into the white connector on the underside of the Romi chassis deck, directly over the motor and battery contacts. There is no placement choice to make for this board.

Do not snap the board in permanently yet — just dry-fit it to understand the orientation and which way the header pins face.

### ESP32 placement planning

1. Place the ESP32 on the chassis top deck where the USB Micro connector is accessible from outside.
2. Locate the `M1PWM`, `M1DIR`, `M2PWM`, `M2DIR`, and `GND` / `5V` header pins on the Romi Motor Driver board (visible when the board is snapped into the chassis).
3. Dry-route your five planned jumper wires with your finger:
   - Four control wires: ESP32 GPIO pins to Romi board control headers.
   - One ground wire: ESP32 GND to Romi board GND.
4. Confirm no planned wire path crosses the drive wheels.
5. Confirm USB access on the ESP32 is not obstructed.

### What NOT to do
- Do not connect any wires in this phase.
- Do not permanently mount the ESP32 before confirming wire routes.

### Stop condition
Stop Phase 2 only when board positions and wire routes are clearly decided.

![Top-Down Electronics Layout](../assets/images/stage1_layout_topdown.png)
_What this image should show: top-down chassis view with the Romi Motor Driver board snapped in and an ESP32 placed on the deck, with simple arrows showing planned jumper wire directions between them._

---

## PHASE 3 — Install Romi Motor Driver Board

### Goal
Snap the Romi Motor Driver board into the chassis so power and motor paths are established through the chassis connectors.

### Parts used
- Romi Motor Driver and Power Distribution Board (#3543).
- Romi chassis from prior phases (motors and ball caster installed).

### Step-by-step instructions

1. Confirm all power is disconnected — no batteries installed, no USB connected.
2. Orient the Romi Motor Driver board so its white chassis connector aligns with the white connector on the underside of the Romi chassis deck.
3. Gently press the board down until the connectors mate fully and the board sits flush.
4. Confirm the board is seated evenly and not tilted.
5. Verify you can identify the following labeled headers on the board surface:
   - `M1PWM` and `M1DIR` (left motor control)
   - `M2PWM` and `M2DIR` (right motor control)
   - `GND` and `5V` (shared ground and regulated output)

### What this connection provides

By snapping the board in, you have established:
- **Motor outputs:** the board's internal drivers are now connected to the left and right motors through the chassis connector — no separate motor wiring needed.
- **Battery input:** the board's VIN contacts are now resting against the chassis battery contact springs — no separate battery wiring needed.
- **Regulated 5V output:** accessible at the `5V` header pin, ready to power the ESP32 for untethered operation.

### What NOT to do
- Do not force the board at an angle — it should snap in straight.
- Do not install batteries yet.

### Stop condition
Stop Phase 3 only when the Romi Motor Driver board is fully seated and all key header labels are confirmed visible and accessible.

![Romi Motor Driver Board Installed](../assets/images/stage1_romi_board_installed.png)
_What this image should show: close-up of the Romi Motor Driver board snapped into the Romi chassis, with the control header pins labeled: M1PWM, M1DIR, M2PWM, M2DIR, GND, 5V._

---

## PHASE 4 — ESP32 to Motor Driver Wiring (CORE STEP)

### Goal
Connect the five jumper wires between ESP32 GPIO pins and the Romi Motor Driver board headers using the frozen Stage 1 pin map.

### Parts used
- ESP32-DevKitC-32E.
- Five jumper wires.

### Frozen Stage 1 wiring map (authoritative)

This map is frozen across all Stage 1 documentation, firmware, and this guide. Use it exactly.

| ESP32 pin | Romi Motor Driver pin | Function |
|---|---|---|
| GPIO25 | M1PWM | Left motor PWM speed |
| GPIO26 | M1DIR | Left motor direction |
| GPIO27 | M2PWM | Right motor PWM speed |
| GPIO14 | M2DIR | Right motor direction |
| GND | GND | Shared ground (required) |

> **GPIO14 note:** GPIO14 is a boot-strapping pin on the ESP32. The firmware initializes it LOW at startup, which is the safe default. The direction signal is a static digital output and this is safe in practice. However: ensure this pin is never externally pulled HIGH during boot (e.g. do not add a pull-up resistor to this line). The jumper wire to the Romi board M2DIR header is fine.

### Step-by-step instructions

1. Confirm all power is disconnected.
2. Locate GPIO25 on the ESP32 (check the label printed on the board edge).
3. Connect a jumper wire from GPIO25 to `M1PWM` on the Romi board.
4. Connect a jumper wire from GPIO26 to `M1DIR` on the Romi board.
5. Connect a jumper wire from GPIO27 to `M2PWM` on the Romi board.
6. Connect a jumper wire from GPIO14 to `M2DIR` on the Romi board.
7. Connect a jumper wire from any ESP32 `GND` pin to `GND` on the Romi board.
8. Gently tug each wire to confirm it is fully seated.
9. Confirm no control wire can contact the drive wheels or the battery contacts.

### Direction control explanation

Each motor uses one PWM wire (speed) and one DIR wire (direction).
- PWM wire: carries the speed signal, 0–100% duty cycle.
- DIR wire: HIGH = one direction, LOW = opposite direction.
- The firmware handles the mixing — you just wire the pins correctly.
- If a motor spins backward during testing, swap the DIR wire to its opposite logic level in firmware, or swap M1DIR/M2DIR wires between motors. Do not rewire the PWM lines.

### What NOT to do
- Do not use GPIO33 for M2DIR — earlier draft documentation contained this error. The frozen pin is **GPIO14**.
- Do not skip the shared GND wire. Without it, the ESP32 and motor driver have no common reference and motors will not respond correctly.
- Do not use ADC2 pins (GPIO0, 2, 4, 12–15, 25–27 range — check ESP32 docs) for other sensors later, as BLE conflicts with ADC2.

### Stop condition
Stop Phase 4 only when all five wires are connected and the map has been verified against the table above.

![ESP32 to Romi Board Control Wiring](../assets/images/stage1_esp32_romi_control.png)
_What this image should show: labeled jumper wires from ESP32 GPIO25/26/27/14/GND to Romi Motor Driver M1PWM/M1DIR/M2PWM/M2DIR/GND header pins._

---

## PHASE 5 — Safe Power Setup

### Goal
Configure the correct power mode before applying any power.

### Two power modes — know which one you are using

**Bench bring-up mode (recommended first):**
- ESP32 is powered by USB-A to Micro-USB cable from laptop.
- Batteries are NOT installed in this first check.
- You can confirm firmware boots and BLE is advertising before any motor power exists.

**Untethered battery mode:**
- Install 6× AA NiMH cells in the Romi chassis battery compartment (observe polarity marking inside compartment).
- The battery power flows through the chassis contacts directly to the Romi Motor Driver board.
- The Romi board's regulated 5V output → ESP32 5V pin provides ESP32 logic power.
- USB can remain connected for serial monitoring but is not required for operation.

### Step-by-step instructions for first bench bring-up

1. Confirm no batteries are installed.
2. Connect the USB-A to Micro-USB cable between your laptop and the ESP32 USB connector.
3. Verify the ESP32 power LED illuminates.
4. Open a serial monitor at 115200 baud.
5. Confirm you see the `IDLE_DISARMED` status message on serial output.
6. Confirm no wheel motion occurs.
7. If using a BLE app (nRF Connect or LightBlue), confirm the `rc-rover-stage1` device is advertising.

### Step-by-step for first battery power check

1. Load 6× AA NiMH cells into the Romi chassis compartment, observing the polarity markings.
2. Keep wheels elevated off the surface.
3. The Romi Motor Driver board powers up automatically when cells are loaded.
4. Connect the 5V regulated output from the Romi board to the ESP32 5V pin if running untethered (or leave USB connected for monitoring).
5. Wait 10–20 seconds and observe for heat, smell, or unexpected motion.

### What NOT to do
- Do not wire raw battery positive directly to the ESP32 VIN or 3.3V pin. The regulated 5V from the Romi board to the ESP32 5V pin is the correct untethered power path.
- Do not run first motor tests with wheels on the floor.

### Stop condition
Stop Phase 5 only when the ESP32 boots cleanly and no unexpected motion or heat occurs at idle.

---

## PHASE 6 — First Power-On Check (NO movement commands)

### Goal
Observe idle power-on behavior before sending any motor commands.

### Step-by-step instructions

1. Keep wheels elevated.
2. Power via USB (bench mode) or battery (untethered mode) as prepared in Phase 5.
3. Wait 15–20 seconds.
4. Observe serial output — you should see the telemetry line repeating:
   ```
   state=DEADMAN,ble=0,thr=0.00,turn=0.00,hb=0,batt=X.XXV
   ```
5. Touch near (not on) components to check for abnormal heat — none expected.
6. No wheel should move without commands.

### Warning signs — power OFF immediately if any occur
- Any component is hot within seconds of power-on.
- Burning smell or any smoke.
- ESP32 does not boot (no serial output, no BLE advertisement).
- Any wheel motion without commands.

### What to check before moving on
- Clean serial output with state=DEADMAN and batt voltage reading.
- BLE device advertising as `rc-rover-stage1`.
- No heat or smell.

### Stop condition
Stop Phase 6 only when idle behavior is clean and stable.

---

## PHASE 7 — Motor Test

### Goal
Confirm both motors respond correctly to basic motion commands from the Stage 1 BLE firmware.

### Using the Stage 1 firmware baseline

The production firmware in `firmware/stage1-esp32-baseline/` requires BLE commands to drive motors. There is no keyboard or serial command path in Stage 1 — motor commands only arrive via BLE.

**Option A — Use a minimal motor test sketch (recommended for first bench validation):**
A dedicated motor test sketch is available in `firmware/stage1-motor-test/`. It drives both motors through a fixed test sequence (forward, stop, reverse, stop, left turn, right turn) with no BLE required. Flash this sketch first, run the test sequence, then reflash the Stage 1 baseline.

To flash and run:
```bash
cd firmware/stage1-motor-test
pio run -t upload
pio device monitor -b 115200
```

Watch serial output for test step messages. The test runs automatically on boot.

**Option B — Use the Stage 1 BLE baseline directly:**
Install a BLE central app on your phone:
- **nRF Connect** (Android or iOS) — recommended for full control.
- **LightBlue** (iOS/Android) — alternative.

Steps:
1. Flash `firmware/stage1-esp32-baseline/` to the ESP32.
2. Open the BLE app. Scan for `rc-rover-stage1`.
3. Connect to the device.
4. Locate the Command characteristic (`f0001001-0451-4000-b000-000000000000`).
5. Write a command string. Format: `T:<throttle>,R:<turn>,H:<heartbeat>,E:0,C:0`
   - Example forward: `T:0.20,R:0.00,H:1,E:0,C:0`
   - Example stop: `T:0.00,R:0.00,H:2,E:0,C:0`
   - Example left turn: `T:0.10,R:-0.20,H:3,E:0,C:0`
6. You must send commands repeatedly (the firmware has a 300ms deadman timeout). Send a new command every 200ms or the motors will stop.

### Motor test sequence (both options)

1. Wheels elevated. Test Motor 1 (left) only — short forward, then stop.
2. Test Motor 2 (right) only — short forward, then stop.
3. Test both motors forward together at low throttle.
4. Test both motors reverse together.
5. Test left turn (left wheel slower/reverse relative to right).
6. Test right turn (right wheel slower/reverse relative to left).
7. Place rover on floor only after wheel-off-ground checks look correct.
8. Run a very short low-speed floor test.

### Troubleshooting

- **A motor spins backward when it should go forward:** The motor is wired with reversed polarity through the chassis connector. This is harmless — correct it by inverting the DIR logic for that side in firmware (swap HIGH/LOW in `writeSide()` for that channel), or note it as a known polarity offset and adjust the mixing logic.
- **One motor does not respond at all:** Check that motor's PWM and DIR jumper wires are fully seated. Check the shared GND wire. Check serial output for `CMD_PARSE_ERROR` or `ESTOP_LATCHED`.
- **Neither motor responds:** Almost always a missing or loose shared GND wire between ESP32 and Romi board. Check this first.
- **Motors run briefly then stop:** Deadman timeout is triggering. You need to send commands continuously at 20–50 Hz. A single write in a BLE app will not sustain motion.

### What NOT to do
- Do not run full throttle on the first floor test.
- Do not keep testing if any component heats rapidly.

### Stop condition
Stop Phase 7 when both motors reliably respond to commands and the rover performs basic controlled movement.

---

# 6. Wiring Reference

### Power path (through chassis connectors — no separate wiring needed)
Battery cells → chassis contacts → Romi Motor Driver board → motors (via chassis connector)

### ESP32 logic power path (untethered)
Romi Motor Driver board `5V` pin → ESP32 `5V` pin (+ shared GND)

### ESP32 logic power path (bench)
Laptop USB → ESP32 Micro-USB connector

### Control path (five jumper wires you install)
| From (ESP32) | To (Romi Motor Driver) | Function |
|---|---|---|
| GPIO25 | M1PWM | Left motor speed |
| GPIO26 | M1DIR | Left motor direction |
| GPIO27 | M2PWM | Right motor speed |
| GPIO14 | M2DIR | Right motor direction |
| GND | GND | Shared ground |

### Battery voltage monitor path (five wires total including divider)
Battery VIN → R1 (20kΩ) → ADC node → ESP32 GPIO34
ADC node → R2 (10kΩ) → GND
Optional 100nF ceramic cap from ADC node to GND (noise filter)

---

# 7. Common Mistakes

- **Using GPIO33 instead of GPIO14 for M2DIR.** The frozen pin map is GPIO14. An earlier draft of this guide contained GPIO33 in error — discard any reference to GPIO33 for M2DIR.
- **Missing shared GND wire between ESP32 and Romi Motor Driver board.** This is the single most common cause of "nothing works" on first test.
- **Trying to power the ESP32 from raw battery voltage directly.** Use the Romi board's regulated 5V output to the ESP32 5V pin for untethered operation.
- **Sending a single BLE write and expecting sustained motion.** The deadman timeout stops motors after 300ms. You must send commands repeatedly.
- **Testing with wheels on the floor before wheel-off-ground checks are complete.** Always run first motion tests with wheels elevated.
- **Pulling GPIO14 HIGH externally during boot.** GPIO14 is a boot-strapping pin. Do not add pull-up resistors to this line.

---

# 8. Build Completion Checklist

- [ ] Rover rolls freely by hand with no binding.
- [ ] Romi Motor Driver board is fully seated in chassis connector.
- [ ] ESP32 powers on cleanly over USB.
- [ ] All five control jumper wires installed per frozen pin map (GPIO25/26/27/14/GND).
- [ ] GPIO33 is NOT used for M2DIR (verify against pin map table above).
- [ ] No shared GND wire is missing.
- [ ] Serial output shows `IDLE_DISARMED` or `DEADMAN` state on boot.
- [ ] Battery voltage reading appears in serial telemetry (value may need calibration — see `docs/STAGE_1_TUNING.md`).
- [ ] Both motors respond to commands.
- [ ] Forward and reverse both work.
- [ ] Left and right turning both work.
- [ ] Deadman timeout stops motors reliably (send one command, wait >300ms, confirm stop).
- [ ] E-stop latch and clear work (send `E:1`, confirm stop; send `T:0,R:0,C:1`, confirm clear).
- [ ] No unusual heat or smell during short tests.
- [ ] Wiring is tidy and clear of moving parts.
