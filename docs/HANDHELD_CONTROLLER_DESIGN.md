# Handheld Controller Design

_Last updated: 2026-04-10_

## Goal

Build a standalone handheld physical controller for the rover — a dedicated device with joysticks, a screen, and Wi-Fi connectivity. This is the primary long-term control surface, designed to feel like a purpose-built RC controller rather than a phone app.

## Overview

The controller is a self-contained device: a Raspberry Pi Zero 2 W reading two analog joysticks and displaying telemetry on a 3.5" TFT screen. It communicates with the rover over Wi-Fi using UDP packets in the existing T,R,H,E,C format.

## Compute Board: Raspberry Pi Zero 2 W

**Why Pi Zero 2 W:**
- Built-in Wi-Fi for rover communication
- Runs Linux + Python — easy UI development with pygame
- GPIO header for joystick ADC and buttons
- Enough compute for a 3.5" TFT with graphical telemetry UI
- Small form factor (65mm × 30mm) fits in a handheld enclosure
- Low power (~0.5W idle, ~1W active) — runs well from a small LiPo

**Why not ESP32:**
- Driving a 3.5" TFT with a rich graphical UI is difficult without an OS
- Limited graphics libraries compared to pygame/framebuffer
- Would work for a no-screen or small-screen controller, but not for the medium TFT choice

**Why not RP2040 (Pico W):**
- Similar TFT UI limitations as ESP32
- MicroPython display libraries are less mature than pygame

## Input: Two Analog Thumbsticks

**Layout (game controller style):**
- **Left stick** — Y-axis maps to `T` (throttle). Push forward = forward, pull back = reverse. X-axis unused initially (available for future strafe/pan).
- **Right stick** — X-axis maps to `R` (turn). Push right = turn right, push left = turn left. Y-axis unused initially (available for future camera tilt).

**Joystick hardware:**
- Standard PS4/Xbox-style analog thumbstick modules (two-axis potentiometer + click button)
- Common part: KY-023 or equivalent dual-axis module
- Each axis outputs 0–3.3V proportional to stick position
- Click button available for future functions (e.g., toggle headlights, honk)

**ADC requirement:**
The Pi Zero has no built-in analog-to-digital converter. An external ADC reads the joystick potentiometers:
- **Recommended: MCP3008** — 8-channel, 10-bit, SPI interface
  - 4 channels used (left Y, left X, right X, right Y)
  - 4 channels spare for future analog inputs
  - Fast enough for 50+ Hz polling
  - Well-supported in Python (`spidev` or `gpiozero`)
- **Alternative: ADS1015** — 4-channel, 12-bit, I2C interface
  - Fewer channels but higher resolution
  - I2C is simpler wiring but slightly slower

## Buttons

Minimum button set:
- **E-stop** — large, red, tactile. Sends `E:1` immediately. Physically distinct from other buttons.
- **E-stop clear** — smaller, recessed or guarded. Sends `C:1` (only works when joysticks are centered).
- **Power** — on/off for the controller itself

Optional (future):
- Mode select (manual / assisted / autonomous)
- Trim adjust
- Joystick click buttons (2, built into the thumbstick modules)

## Display: 3.5" TFT

**Hardware:**
- 3.5" SPI TFT display (480×320 or 320×240)
- Common part: ILI9486 or ILI9341-based SPI display with Pi Zero header
- Adafruit PiTFT 3.5" is a well-documented option that mounts directly onto the Pi GPIO header
- Resistive touch is available but not needed for Stage 2 (physical buttons handle all input)

**UI layout (pygame on framebuffer):**

```
┌─────────────────────────────────────────┐
│  rc-rover                    ██ 7.2V    │  ← header: name + battery bar
│─────────────────────────────────────────│
│                                         │
│   THR ████████░░  0.45    STATE: ACTIVE │  ← throttle bar + rover state
│  TURN ░░░░████░░  0.20    SOURCE: UDP   │  ← turn bar + command source
│                                         │
│   ┌─────────┐    BATT: 7.24V           │  ← left joystick visualizer
│   │    ●    │    RSSI: -42 dBm         │     + telemetry values
│   │         │    HB: 14523              │
│   └─────────┘    UPTIME: 00:12:34      │
│                                         │
│  [  E-STOP  ]              CONNECTED ● │  ← e-stop status + connection
└─────────────────────────────────────────┘
```

**Telemetry fields:**
- Battery voltage (from rover status messages)
- Throttle/turn values (local, from joystick)
- Rover state (ACTIVE / DEADMAN / ESTOP)
- Command source (UDP / WS / BLE)
- Wi-Fi RSSI (signal strength to rover)
- Heartbeat counter
- Uptime
- Connection status indicator

## Communication

**Protocol:** UDP on port 4210 (same as defined in Stage 2 design).

**Packet format:** Identical T,R,H,E,C ASCII string:
```
T:0.45,R:0.20,H:14523,E:0,C:0
```

**Send rate:** 20 Hz (50ms interval). Joystick values are read, mapped to -1.0..+1.0, and sent as a UDP packet every 50ms.

**Receive:** The controller listens for status messages from the rover (battery voltage, state, etc.) on a separate UDP port or as response packets. Format TBD — could mirror the serial telemetry format.

**Connection flow:**
1. Controller boots, connects to rover's Wi-Fi AP (`rc-rover`)
2. Sends first UDP packet to `192.168.4.1:4210`
3. Rover begins accepting commands (source arbitration kicks in)
4. If Wi-Fi disconnects, controller UI shows "DISCONNECTED" and retries
5. Rover's deadman timeout stops motors within 300ms of lost packets

## Power

**Battery:** Single-cell LiPo (3.7V, 2000–3000mAh) with a boost converter to 5V for the Pi.
- Estimated runtime: 3–5 hours (Pi Zero 2 W draws ~200mA, display ~80mA, joysticks negligible)
- Charging: USB-C charge board (TP4056 or similar) built into the enclosure
- Power switch: physical slide or toggle switch

**Alternative:** USB power bank (simpler, no charge circuit needed, but bulkier).

## Enclosure

**Approach:** 3D printed enclosure, game controller form factor.

**Key dimensions:**
- Two thumbstick cutouts on the face
- 3.5" TFT window in the center
- E-stop button prominently placed (top or face)
- USB-C charge port on bottom edge
- Power switch on top or side edge
- Comfortable two-handed grip with thumbs on joysticks

**If no 3D printer available:** Start with an open prototype on a breadboard/perfboard mounted to a flat acrylic or wood plate. Function over form for initial testing.

## Software Architecture

```
┌──────────────────────────────────────┐
│           main.py                     │
│  ┌────────────┐  ┌────────────────┐  │
│  │ JoystickADC│  │  UDPTransport  │  │
│  │  (MCP3008) │  │  (send/recv)   │  │
│  └─────┬──────┘  └───────┬────────┘  │
│        │                  │           │
│  ┌─────▼──────────────────▼────────┐  │
│  │        CommandBuilder           │  │
│  │  joystick → T,R,H,E,C string   │  │
│  └─────────────┬───────────────────┘  │
│                │                      │
│  ┌─────────────▼───────────────────┐  │
│  │        DisplayUI (pygame)       │  │
│  │  telemetry, joystick viz, state │  │
│  └─────────────────────────────────┘  │
└──────────────────────────────────────┘
```

**Key modules:**
- `joystick_adc.py` — reads MCP3008, applies deadzone/calibration, outputs -1.0..+1.0
- `udp_transport.py` — sends T,R,H,E,C packets, receives status responses
- `command_builder.py` — maps joystick values + button states to protocol string
- `display_ui.py` — pygame framebuffer UI, renders telemetry and joystick visualization
- `main.py` — 20Hz control loop tying everything together

## BOM (preliminary)

| Part | Est. Cost | Notes |
|---|---|---|
| Raspberry Pi Zero 2 W | $15 | Check stock — often backordered |
| MCP3008 ADC | $4 | 8-channel SPI, DIP or breakout |
| 3.5" SPI TFT (ILI9486) | $15–25 | Pi-compatible header mount preferred |
| 2× analog thumbstick module | $3–5 | KY-023 or equivalent |
| E-stop button (red, momentary) | $2 | Large tactile, panel mount |
| E-stop clear button (momentary) | $1 | Smaller, recessed |
| Power switch (slide/toggle) | $1 | |
| LiPo battery (3.7V, 2500mAh) | $8–12 | Single cell |
| TP4056 charge board (USB-C) | $2 | With protection circuit |
| 5V boost converter | $3 | 3.7V → 5V, 1A+ output |
| Enclosure (3D printed or project box) | $5–15 | |
| Misc (wires, headers, perfboard, screws) | $5 | |
| **Total estimate** | **$65–90** | |

## Implementation Phases

### Phase HC-1: Breadboard prototype
- Pi Zero 2 W + MCP3008 + one joystick on a breadboard
- Python script reads joystick, prints values to terminal
- Verify ADC reads clean analog values with proper deadzone

### Phase HC-2: UDP control link
- Connect Pi to rover's Wi-Fi AP
- Send T,R,H,E,C packets over UDP at 20 Hz
- Drive the rover from the breadboard prototype
- Verify latency is acceptable

### Phase HC-3: Display integration
- Connect 3.5" TFT to Pi Zero
- Build pygame UI with joystick visualization and telemetry
- Display local joystick values in real-time

### Phase HC-4: Full prototype
- Add second joystick, e-stop button, e-stop clear button
- Two-way communication: receive status from rover, display on screen
- Full control loop: read inputs → build command → send → receive status → update display

### Phase HC-5: Enclosure and polish
- Design and print (or build) enclosure
- Install LiPo + charge circuit + power switch
- Final wiring and assembly
- Comfort and ergonomics testing

## Dependencies

- **Stage 2 Phase S2-5 (UDP listener)** must be complete on the rover before Phase HC-2 can be tested end-to-end.
- **Stage 1 must be complete** (encoders installed, motors working) before meaningful driving tests.
- Pi Zero 2 W stock availability — order early.

## Out of scope

- Camera/video feed (future stage)
- Haptic feedback / vibration motors (future)
- Multiple controller support (one controller at a time for now)
- Bluetooth fallback from the controller (Wi-Fi only)
