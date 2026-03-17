# 1. Build Overview

## Objective
Build Rover A Stage 1 as a safe, working, manually controlled differential-drive rover using a Romi-style chassis, ESP32, DRV8833 motor driver, battery pack, and two DC motors.

## What you are building (simple explanation)
You are building a small two-wheel rover.
One motor drives the left wheel.
One motor drives the right wheel.
The battery provides motor power.
The ESP32 tells the motor driver which way each motor should spin.

## Final expected outcome
At the end of this guide, you should have:
- A fully assembled rolling chassis.
- Motors wired to the DRV8833 motor driver.
- ESP32 control wires connected to the driver.
- Safe power setup for first tests.
- Basic motor movement confirmed (forward, reverse, turning).

![Completed Rover Top View](../assets/images/stage1_rover_complete_top.png)
What this image should show: a top-down view of the finished Stage 1 rover with labeled ESP32, DRV8833, battery pack, left motor, and right motor.

# 2. System Architecture (Simple Explanation)

Think of the rover as three paths that must all be correct.

- **Power path:** battery -> motor driver -> motors.
  - The battery sends energy to the motor driver.
  - The motor driver sends that energy to each motor.
- **Control path:** ESP32 -> motor driver.
  - The ESP32 sends simple ON/OFF direction signals to the motor driver.
  - The motor driver uses those signals to decide motor direction.
- **Ground path (critical):** ESP32 ground and motor driver ground must be connected.
  - This gives both boards the same electrical reference.
  - Without this shared ground, control signals may fail or behave randomly.

![Power Control Ground Diagram](../assets/images/stage1_power_control_ground_paths.png)
What this image should show: a simple block diagram with three colored paths: battery to driver to motors, ESP32 to driver control pins, and one bold shared ground line between ESP32 and driver.

# 3. Tools Required

Required:
- Screwdriver (small Phillips and/or flat depending on your chassis screws and terminal blocks).
- Wire stripper (for clean wire ends).

Optional:
- Soldering iron (only if your driver board or wire setup needs soldered joints).
- Multimeter (optional but strongly recommended for polarity and continuity checks).

# 4. Parts Identification

Before assembly, place all parts on a table and identify each one.

- **ESP32 board**
  - A small microcontroller board with many side pins.
  - Usually has a USB connector for programming and power.
  - Often labeled “ESP32” or “DevKit.”

- **DRV8833 motor driver board**
  - Small board with labeled control and motor terminals.
  - Look for labels such as `IN1`, `IN2`, `IN3`, `IN4` (or `AIN1`, `AIN2`, `BIN1`, `BIN2`).
  - Look for motor outputs such as `OUT1`, `OUT2`, `OUT3`, `OUT4`.
  - Look for power pins labeled `VM` (or `VCC`) and `GND`.

- **Two DC motors**
  - Small metal gear motors or plastic-geared DC motors.
  - Each motor has two wires (or two tabs).
  - Each motor has a metal output shaft for a wheel.

- **Romi-style chassis components**
  - Main chassis plate.
  - Motor mounts/brackets.
  - Two drive wheels.
  - Rear caster (ball or wheel type).
  - Screws, nuts, spacers.

- **Battery pack / holder**
  - Holds the required battery cells (often AA NiMH for Romi-style setups).
  - Has positive (+) and negative (-) output leads.

![Parts Flat Lay](../assets/images/stage1_parts_identification_flatlay.png)
What this image should show: all major parts laid out on a bench with text labels pointing to ESP32, DRV8833 board, motors, chassis pieces, and battery pack.

# 5. PHASED BUILD INSTRUCTIONS

## PHASE 1 — Mechanical Assembly (NO electronics)

### Goal
Build a straight, freely rolling rover chassis before adding electronics.

### Parts Used
- Chassis plate and hardware.
- Two DC motors.
- Two wheels.
- Rear caster.
- Battery holder.

### Step-by-step instructions
1. Place the chassis plate on a flat table.
2. Install the left motor in its mount.
3. Install the right motor in its mount.
4. Ensure both motor shafts point outward toward wheel locations.
5. Tighten motor mounting hardware evenly. Do not over-tighten plastic parts.
6. Push the left wheel onto the left motor shaft.
7. Push the right wheel onto the right motor shaft.
8. Install the rear caster at the rear mounting holes.
9. Install the battery holder in the planned battery location.
10. Confirm nothing rubs on the wheels.
11. Set rover on the table and gently roll it forward by hand.
12. Roll it backward by hand.

### How to verify alignment
- Look from the front: wheels should be parallel.
- Look from above: both wheels should sit at the same forward angle (not toe-in/toe-out).
- Push rover forward slowly: it should not strongly pull left or right.

### How to check rolling resistance
- With power OFF, push rover lightly.
- It should roll smoothly.
- If it stops immediately, inspect wheel rub, caster tightness, and motor mount alignment.

### What NOT to do
- Do not install any wires in this phase.
- Do not force wheels if shaft fit is wrong.
- Do not over-tighten screws into plastic.

### What to check before moving on
- Both motors are firmly mounted.
- Motor shafts are facing outward.
- Wheels are seated and spin cleanly.
- Caster is installed and rotates freely.
- Battery holder is secure.

### Stop condition
Stop Phase 1 only when the rover rolls freely on a flat surface with no scraping or binding.

## PHASE 2 — Electronics Layout Planning (NO wiring yet)

### Goal
Decide exactly where ESP32 and DRV8833 will be mounted before making any electrical connection.

### Parts Used
- ESP32 board.
- DRV8833 motor driver board.
- Chassis from Phase 1.
- Mounting tape, standoffs, or brackets.

### Step-by-step instructions
1. Place ESP32 on the chassis where USB access is easy.
2. Place DRV8833 near the motors to keep motor wires short.
3. Leave clear space around screw terminals and pin headers.
4. Dry-route (pretend route) each planned wire path with your finger:
   - Motor wires to driver outputs.
   - Battery wires to driver power input.
   - ESP32 control wires to driver inputs.
   - Ground wire between ESP32 and driver.
5. Confirm no planned wire path crosses moving wheels.
6. Confirm board locations do not block battery replacement.
7. Mark board positions lightly (tape marks or pencil dots).

### Why this matters
Planning first avoids rework.
You reduce wire clutter.
You lower the chance of loose wires hitting wheels.
You make troubleshooting easier later.

### What NOT to do
- Do not connect wires in this phase.
- Do not permanently glue boards before route planning is complete.

### What to check before moving on
- ESP32 USB port remains reachable.
- Motor driver terminals are reachable.
- All wire routes are clear of moving parts.

### Stop condition
Stop Phase 2 only when component positions and wire routes are clearly decided.

![Top-Down Electronics Layout](../assets/images/stage1_layout_topdown.png)
What this image should show: top-down chassis view with suggested ESP32 and DRV8833 placement and simple arrows showing planned wire directions.

## PHASE 3 — Motor Driver Wiring (CORE STEP)

### Goal
Wire motors and battery to the DRV8833 correctly and safely.

### Parts Used
- DRV8833 motor driver.
- Left and right motors.
- Battery pack leads.
- Wire and screw terminals (or solder pads depending on board).

### Step-by-step instructions
1. Ensure all power is disconnected.
2. Identify motor output terminals on DRV8833:
   - `OUT1`, `OUT2` for Motor A.
   - `OUT3`, `OUT4` for Motor B.
3. Connect left motor wires to `OUT1` and `OUT2`.
4. Connect right motor wires to `OUT3` and `OUT4`.
5. Tighten output terminals securely.
6. Gently tug each motor wire to confirm it is clamped.
7. Identify power input pins on DRV8833:
   - `VM` or `VCC` (battery positive input).
   - `GND` (battery negative).
8. Connect battery positive (+) lead to `VM`/`VCC`.
9. Connect battery negative (-) lead to `GND`.
10. Re-check polarity labels visually before any power is applied.

### A. Motor outputs
- `OUT1 + OUT2` -> Motor A.
- `OUT3 + OUT4` -> Motor B.
- Motor polarity does **not** need to be perfect initially.
- If direction is reversed in testing, you can swap that motor’s two wires later.

### B. Power connections
- Battery positive -> `VM` / `VCC`.
- Battery negative -> `GND`.
- A reversed battery connection can damage the motor driver.

### C. Common ground (critical)
- ESP32 `GND` **must** connect to motor driver `GND`.
- This is required for control signals to work correctly.
- Without common ground:
  - Motors may not respond.
  - Motors may respond unpredictably.
  - Debugging becomes confusing because signals have no shared reference.

### What NOT to do
- Do not connect battery positive to `GND`.
- Do not connect battery negative to `VM`/`VCC`.
- Do not assume wire colors are correct without checking labels.

### What to check before moving on
- Left motor is on `OUT1/OUT2`.
- Right motor is on `OUT3/OUT4`.
- Battery polarity is correct at the driver input.
- No exposed copper is touching nearby terminals.

### Stop condition
Stop Phase 3 only when motors and battery are fully wired to the driver and all terminals are secure.

![Motor Wiring](../assets/images/motor_wiring.png)
What this image should show: close-up of motor wires connected to `OUT1/OUT2` and `OUT3/OUT4`, with labels showing left motor and right motor.

![Battery to Driver Power Wiring](../assets/images/stage1_battery_to_driver.png)
What this image should show: close-up of battery positive wire into `VM/VCC` and battery negative wire into `GND`, with polarity symbols.

## PHASE 4 — ESP32 to Motor Driver Wiring

### Goal
Connect ESP32 control pins to DRV8833 input pins using a simple default map.

### Parts Used
- ESP32 board.
- DRV8833 board.
- Jumper wires.

### Step-by-step instructions
1. Keep battery disconnected during this phase.
2. Identify driver control pins (`AIN1/AIN2/BIN1/BIN2` or equivalent `IN1-IN4`).
3. Wire the default control map:
   - `AIN1` -> ESP32 GPIO 27
   - `AIN2` -> ESP32 GPIO 26
   - `BIN1` -> ESP32 GPIO 25
   - `BIN2` -> ESP32 GPIO 33
4. Add one ground wire:
   - ESP32 `GND` -> DRV8833 `GND`.
5. Confirm each wire is fully seated and not loose.
6. Keep wires away from wheel rotation zones.

### Direction control explanation
- Each motor uses **two** control pins.
- Motor A uses `AIN1` + `AIN2`.
- Motor B uses `BIN1` + `BIN2`.
- Direction is controlled by HIGH/LOW combinations:
  - One pin HIGH and the other LOW = spin one direction.
  - Reversed states = opposite direction.
  - Both LOW (or both HIGH, depending on driver behavior) = brake/coast state.

### What NOT to do
- Do not skip the ESP32-to-driver ground wire.
- Do not use random GPIO pins without updating firmware later.

### What to check before moving on
- All four control wires match the default map.
- Ground wire between ESP32 and driver is present.
- No control wire can touch motor terminals.

### Stop condition
Stop Phase 4 only when all control wires and common ground are correctly installed.

![ESP32 to Driver Control Wiring](../assets/images/stage1_esp32_driver_control.png)
What this image should show: close-up showing `AIN1/AIN2/BIN1/BIN2` wires from DRV8833 to ESP32 GPIO 27/26/25/33 and one ESP32 `GND` to driver `GND` wire.

## PHASE 5 — Safe Power Setup

### Goal
Power the system in the safest first-test order.

### Parts Used
- USB cable for ESP32.
- Battery pack (connected to motor driver only).

### Step-by-step instructions
1. Confirm rover wheels are off the ground (use a stand or hold rover safely).
2. Connect ESP32 to USB power first.
3. Verify ESP32 power LED/boot indication appears.
4. Confirm battery is connected only to motor driver power input.
5. Double-check that battery is **not** wired directly to ESP32 power pins.
6. Keep fingers clear of wheels.

### Why not power ESP32 directly from battery here
- Battery voltage may be outside safe ESP32 input range if wired incorrectly.
- Wrong direct power wiring can permanently damage the ESP32.
- USB-first bring-up is easier to monitor and debug.

### What NOT to do
- Do not connect raw battery leads directly to ESP32 VIN/5V unless your exact power design explicitly supports it and is verified.
- Do not place rover wheels on the floor during first power checks.

### What to check before moving on
- ESP32 powers by USB normally.
- Motor driver has correct battery polarity.
- No component is heating before commands are sent.

### Stop condition
Stop Phase 5 only when power connections are confirmed safe and stable with no heat or smell.

## PHASE 6 — First Power-On (NO movement expected)

### Goal
Perform a safe observation-only power-on check before motor commands.

### Parts Used
- Fully assembled and wired rover from prior phases.

### Step-by-step instructions
1. Keep wheels off the ground.
2. Power ESP32 via USB.
3. Connect or switch on motor battery supply.
4. Wait 10-20 seconds and observe.
5. Check ESP32 boot indication.
6. Check motor driver board for obvious fault signs.
7. Touch near components carefully (without shorting) to detect abnormal heat.

### What normal looks like
- ESP32 boots normally.
- No wheel motion without commands.
- No burnt smell.
- No rapidly heating components.

### Warning signs (power OFF immediately)
- Hot board or hot wires within seconds.
- Burning or chemical smell.
- ESP32 does not boot.
- Any smoke.

### What NOT to do
- Do not send movement commands yet.
- Do not ignore unusual heat.

### What to check before moving on
- System can stay powered briefly with no faults.
- No unexpected movement happens at idle.

### Stop condition
Stop Phase 6 only when idle power-on behavior is stable and safe.

## PHASE 7 — Motor Test

### Goal
Confirm both motors respond correctly to basic motion commands.

### Parts Used
- Stage 1 assembled rover.
- ESP32 test firmware.

### Step-by-step instructions
1. Upload a simple motor test sketch/firmware to ESP32.
2. Test Motor A only (short forward command, then stop).
3. Test Motor B only (short forward command, then stop).
4. Test both motors forward together.
5. Test both motors reverse together.
6. Test turning:
   - Left turn (left slower/reverse, right forward as needed).
   - Right turn (right slower/reverse, left forward as needed).
7. Place rover on floor only after wheel-off-ground checks look correct.
8. Run a very short, low-speed floor test.

### Troubleshooting
- **Motor spinning backward:** swap that motor’s two output wires.
- **One motor not working:** check that motor’s output terminals (`OUTx`) and clamp tightness.
- **Nothing works:** check shared ground first (ESP32 `GND` to driver `GND`).

### What NOT to do
- Do not run full speed on first floor test.
- Do not keep testing if components heat quickly.

### What to check before moving on
- Rover moves forward and reverse under control.
- Rover can turn left and right.
- No overheating during short tests.

### Stop condition
Stop Phase 7 when both motors reliably respond to command and the rover performs basic controlled movement.

# 6. Wiring Reference (VERY IMPORTANT)

### Power Path
Battery -> Motor Driver -> Motors

### Control Path
ESP32 -> Motor Driver

### Ground Path
ALL grounds connected together (battery ground, driver ground, ESP32 ground).

Quick reference list:
- Battery `+` -> Driver `VM/VCC`
- Battery `-` -> Driver `GND`
- Motor A -> `OUT1/OUT2`
- Motor B -> `OUT3/OUT4`
- `AIN1` -> GPIO 27
- `AIN2` -> GPIO 26
- `BIN1` -> GPIO 25
- `BIN2` -> GPIO 33
- ESP32 `GND` -> Driver `GND`

# 7. Common Mistakes (MANDATORY)

- Reversed battery polarity at the motor driver input.
- Missing common ground between ESP32 and motor driver.
- Motors connected to incorrect output pairs.
- Powering ESP32 incorrectly from battery wiring.
- Routing wires where wheels can rub or cut insulation.

# 8. Build Completion Checklist

- [ ] Rover rolls freely by hand.
- [ ] ESP32 powers on reliably over USB.
- [ ] Motor driver receives battery power with correct polarity.
- [ ] Both motors respond to control commands.
- [ ] Forward and reverse both work.
- [ ] Left and right turning both work.
- [ ] No unusual heat or smell during short tests.
- [ ] Wiring is tidy and clear of moving parts.
