# Stage 2 Design: Wi-Fi Transport and Web Dashboard

_Last updated: 2026-04-10_

## Goal

Add Wi-Fi as a second transport alongside BLE, and serve a web-based control dashboard directly from the ESP32. The rover becomes controllable from any device with a browser — no app install required.

## Architecture Decisions

### Wi-Fi mode: Configurable AP + STA

The ESP32 supports both Access Point and Station modes. Stage 2 implements both, selectable at compile time (with AP as the default).

**Access Point (AP) mode — default:**
- ESP32 creates its own network: `rc-rover` (password configurable)
- Dashboard available at `192.168.4.1`
- No router dependency, works anywhere
- Client loses internet while connected

**Station (STA) mode — optional:**
- ESP32 joins an existing Wi-Fi network
- SSID and password set via `config::WIFI_SSID` / `config::WIFI_PASS`
- Dashboard available at the ESP32's DHCP-assigned IP (printed to serial on boot)
- Requires a router, but client keeps internet access

A compile-time `#define WIFI_MODE_AP` / `WIFI_MODE_STA` selects the mode. A future enhancement could allow runtime switching via a BLE command or physical button.

### Transport protocols: WebSocket + UDP

Both protocols feed into the existing `parseCommand()` function — the command format (T,R,H,E,C) is unchanged.

**WebSocket (port 81):**
- Primary transport for the web dashboard and future mobile app
- Provides connection/disconnection events (maps to existing BLE connect/disconnect flow)
- Slightly higher latency than UDP, but well within the 20–50 Hz control loop requirement
- Library: `ESPAsyncWebServer` + `AsyncWebSocket`

**UDP (port 4210):**
- Reserved for the handheld physical controller (Stage 2+)
- Lowest possible latency for real-time joystick input
- No connection state — deadman timeout handles dropped controllers
- Library: `AsyncUDP` or native `WiFiUDP`

### Source arbitration

Only one command source is active at a time. The active source is determined by last-writer-wins with a 1-second switchover cooldown:

- If BLE commands are arriving, Wi-Fi commands are ignored (and vice versa)
- If the active source stops sending for >1 second, any source can take over
- The deadman timeout (300ms) still applies independently — if the active source stops, motors stop regardless of whether another source could take over

This prevents two controllers from fighting over the rover while allowing seamless handoff.

### Status reporting

The existing status characteristic (BLE notify) is mirrored over WebSocket:
- WebSocket clients receive the same status strings: `BOOT`, `IDLE_DISARMED`, `BLE_CONNECTED`, `ESTOP_LATCHED`, etc.
- New status: `WIFI_CONNECTED`, `WIFI_DISCONNECTED`, `WS_CLIENT_CONNECTED`, `WS_CLIENT_DISCONNECTED`
- Serial telemetry line gains `wifi=<0|1>` and `ws_clients=<n>` fields

## Web Dashboard

The dashboard is a single HTML page served from the ESP32's flash (SPIFFS/LittleFS). It provides:

### Controls
- **Virtual joystick** — touch/mouse draggable pad that maps to T (throttle) and R (turn)
- **E-stop button** — large red button, sends E:1
- **E-stop clear** — available only when e-stop is latched and joystick is centered

### Telemetry display
- Battery voltage (from existing ADC)
- Connection state (WebSocket connected/disconnected)
- Active command source (BLE / WebSocket / UDP)
- Heartbeat counter
- Motor state (ACTIVE / DEADMAN / ESTOP)

### Technical details
- Single `index.html` file with inline CSS and JS (no external dependencies)
- WebSocket connection to `ws://<esp32-ip>:81/ws`
- Sends T,R,H,E,C packets at 20 Hz while joystick is active
- Heartbeat counter increments with each packet
- Auto-reconnect on WebSocket disconnect

## Firmware Changes

### New files
- `firmware/stage2-esp32-wifi/` — new PlatformIO project (copy of stage1 baseline + Wi-Fi additions)

### New dependencies (platformio.ini)
- `me-no-dev/ESPAsyncWebServer`
- `me-no-dev/AsyncTCP`

### Code structure
The existing firmware is well-structured for this. Changes are additive:

1. **WiFi setup** — new `setupWifi()` function alongside `setupBle()`, called from `setup()`
2. **WebSocket handler** — new callback class, calls `parseCommand()` on incoming messages
3. **HTTP server** — serves `index.html` from SPIFFS at `/`
4. **Source arbitration** — new `g_activeSource` enum and timestamp tracking in the command path
5. **UDP listener** — placeholder for handheld controller (can be enabled later)

The motor output, battery ADC, deadman timeout, and e-stop logic are completely unchanged.

### Memory budget
- ESP32 has 320KB RAM; current firmware uses 6.6% (~21KB)
- Wi-Fi stack adds ~40-60KB
- AsyncWebServer + WebSocket adds ~20-30KB
- SPIFFS for dashboard HTML adds ~10-20KB
- Total estimated: ~120-130KB (~38-40%) — well within limits

## File system (SPIFFS/LittleFS)

The dashboard HTML is stored in the ESP32's flash filesystem:
- `data/index.html` — the complete dashboard (HTML + CSS + JS in one file)
- Uploaded via `pio run -t uploadfs`
- LittleFS preferred over SPIFFS (faster, more reliable, supports directories)

## Phases

### Phase S2-1: Wi-Fi AP + WebSocket echo
- Add Wi-Fi AP mode to firmware
- Add WebSocket server that echoes received messages to serial
- Verify a browser can connect and send text
- **No motor control yet** — just proving the transport works

### Phase S2-2: Command routing
- Wire WebSocket messages into `parseCommand()`
- Add source arbitration logic
- Add Wi-Fi status to serial telemetry
- Verify motor control works over WebSocket (using a simple test page or browser console)

### Phase S2-3: Web dashboard
- Build the dashboard HTML (virtual joystick, e-stop, telemetry display)
- Upload to LittleFS
- Serve from ESP32 HTTP server
- End-to-end test: connect phone/laptop to AP, open dashboard, drive rover

### Phase S2-4: STA mode
- Add Station mode as compile-time option
- Print assigned IP to serial on boot
- Test dashboard over home Wi-Fi

### Phase S2-5: UDP listener (placeholder)
- Add UDP socket on port 4210
- Wire into command parser with source arbitration
- Test with a simple Python script sending T,R,H,E,C over UDP
- This prepares the path for the handheld controller

## Success criteria

- [ ] Rover controllable from a web browser over Wi-Fi (AP mode)
- [ ] Virtual joystick provides smooth, responsive control
- [ ] E-stop and deadman timeout work identically to BLE
- [ ] BLE and WebSocket can coexist without interference
- [ ] Source arbitration prevents controller fights
- [ ] Battery voltage displayed on dashboard
- [ ] STA mode works as a compile-time option
- [ ] UDP listener accepts and routes commands

## Out of scope for Stage 2

- Mobile app (uses same WebSocket endpoint, but native app is a later project)
- Handheld physical controller hardware (design planning is separate)
- Encoder telemetry (depends on Stage 1 completion with encoder kit)
- Current sensing or advanced telemetry
- OTA firmware updates (future convenience feature)
- Authentication/security on the Wi-Fi network (WPA2 password only for now)
