# Stage 2 Design: Wi-Fi Transport and Web Dashboard

_Last updated: 2026-04-10_

## Goal

Add Wi-Fi as a second transport alongside BLE, and serve a web-based control dashboard directly from the ESP32. The rover becomes controllable from any device with a browser — no app install required.

## Architecture Decisions

### Wi-Fi mode: Configurable AP + STA

The ESP32 supports both Access Point and Station modes. Stage 2 implements both, selectable at compile time (with AP as the default).

**Access Point (AP) mode — default:**
- ESP32 creates its own WPA2 network: SSID `rc-rover`, password configurable (default `roverpass`)
- Dashboard available at `192.168.4.1`
- No router dependency, works anywhere (bench, field, demo)
- Client device loses internet while connected to the AP

**Station (STA) mode — optional:**
- ESP32 joins an existing Wi-Fi network
- SSID and password set via `config::WIFI_SSID` / `config::WIFI_PASS`
- mDNS enabled: dashboard available at `http://rc-rover.local` (fallback: DHCP IP printed to serial)
- Requires a router, but client keeps internet access

A compile-time `#define WIFI_MODE_AP` / `WIFI_MODE_STA` selects the mode. A future enhancement could allow runtime switching via a BLE command or physical button.

### BLE + Wi-Fi coexistence

The ESP32 has a single 2.4 GHz radio shared between BLE and Wi-Fi via time-division multiplexing. Both protocols can run simultaneously, but they compete for radio time. Key implications for this project:

- **Source arbitration is our primary mitigation.** Only one command source is active at a time, so BLE and Wi-Fi are not both transferring high-frequency data simultaneously.
- **BLE advertising continues** while Wi-Fi is active (advertising is short-burst and tolerant of scheduling delays). This means the rover remains discoverable via BLE even when a WebSocket client is in control.
- **If both are truly simultaneous** (e.g., BLE connected but idle while WebSocket is active), the ESP-IDF coexistence controller handles scheduling automatically. The Arduino framework enables software coexistence by default (`CONFIG_ESP_COEX_SW_COEXIST_ENABLE=y`).
- **Pin Wi-Fi and BLE to separate cores** in `platformio.ini` build flags if coexistence issues arise during testing. This is a tuning knob, not a Phase S2-1 requirement.

### Transport protocols: WebSocket + UDP

Both protocols feed into the existing `parseCommand()` function — the command format (T,R,H,E,C) is unchanged.

**WebSocket (port 81):**
- Primary transport for the web dashboard and future mobile app
- Provides connection/disconnection events (maps to existing BLE connect/disconnect safety flow)
- On WebSocket disconnect: `safeStop()` is called immediately, same as BLE disconnect behavior
- Only **one WebSocket client** may send commands at a time (first-connected wins). Additional clients connect as read-only spectators receiving status updates only. If the active client disconnects, the next connected client is promoted.
- Library: `ESP32Async/ESPAsyncWebServer` + `ESP32Async/AsyncTCP` (actively maintained fork — `me-no-dev` original and `mathieucarbou` fork are both archived as of Jan 2025)

**UDP (port 4210):**
- Reserved for the handheld physical controller (Stage 2+)
- Lowest possible latency for real-time joystick input
- No connection state — deadman timeout handles dropped controllers
- Library: `AsyncUDP` (event-driven, fits the async architecture)

### Source arbitration

Only one command source is active at a time. The active source is determined by last-writer-wins with a 1-second switchover cooldown:

- If BLE commands are arriving, Wi-Fi commands are ignored (and vice versa)
- If the active source stops sending for >1 second, any source can take over
- The deadman timeout (300ms) still applies independently — if the active source stops, motors stop regardless of whether another source could take over
- **E-stop is source-independent:** any source can latch e-stop at any time. E-stop clear is also accepted from any source (requires zero throttle/turn as before). This prevents a controller handoff from leaving e-stop permanently latched.
- The dashboard displays the currently active source so the user knows if another controller has priority

This prevents two controllers from fighting over the rover while allowing seamless handoff.

### Status reporting

The existing status characteristic (BLE notify) is mirrored over WebSocket:
- WebSocket clients receive the same status strings: `BOOT`, `IDLE_DISARMED`, `BLE_CONNECTED`, `ESTOP_LATCHED`, etc.
- New statuses: `WIFI_AP_STARTED`, `WIFI_STA_CONNECTED`, `WS_CLIENT_CONNECTED`, `WS_CLIENT_DISCONNECTED`
- Serial telemetry line gains `wifi=<0|1>`, `ws_clients=<n>`, and `src=<BLE|WS|UDP|NONE>` fields

## Web Dashboard

The dashboard is a single HTML page served from the ESP32's flash filesystem (LittleFS). Designed mobile-first since the primary use case is a phone connected to the AP.

### Controls
- **Virtual joystick** — using the [nipplejs](https://github.com/yoannmoinet/nipplejs) library (~10KB minified, zero dependencies, touch + mouse support). Maps joystick X/Y to T (throttle) and R (turn). The nipplejs source is embedded directly in the HTML file (no CDN dependency since the ESP32 AP has no internet).
- **E-stop button** — large red button, sends E:1
- **E-stop clear** — available only when e-stop is latched and joystick is centered

### Telemetry display
- Battery voltage (from existing ADC)
- Connection state (WebSocket connected/disconnected)
- Active command source (BLE / WebSocket / UDP / None)
- Heartbeat counter
- Motor state (ACTIVE / DEADMAN / ESTOP)
- Encoder speed/distance (placeholder — data path added when encoders are integrated)

### Technical details
- Single `index.html` file with inline CSS and JS, including nipplejs source (no external dependencies)
- WebSocket connection to `ws://<esp32-ip>:81/ws`
- **Sends T,R,H,E,C packets at 20 Hz continuously** — including when the joystick is centered (T:0, R:0). This is required to satisfy the 300ms deadman timeout. Packets stop only when the page is closed or WebSocket disconnects.
- Heartbeat counter increments with each packet
- Auto-reconnect on WebSocket disconnect with exponential backoff (100ms → 200ms → 400ms → ... → 5s cap)
- Mobile-first responsive layout: large touch targets, no hover-dependent UI

## Firmware Changes

### New files
- `firmware/stage2-esp32-wifi/` — new PlatformIO project (copy of stage1 baseline + Wi-Fi additions)

### New dependencies (platformio.ini)
```ini
lib_deps =
    ESP32Async/ESPAsyncWebServer
    ESP32Async/AsyncTCP
```

### Code structure
The existing firmware is well-structured for this. Changes are additive:

1. **WiFi setup** — new `setupWifi()` function alongside `setupBle()`, called from `setup()`
2. **mDNS setup** — `MDNS.begin("rc-rover")` in STA mode, enabling `http://rc-rover.local`
3. **WebSocket handler** — new callback class, calls `parseCommand()` on incoming messages; `onDisconnect` calls `safeStop()`
4. **HTTP server** — serves `index.html` from LittleFS at `/`
5. **Source arbitration** — new `g_activeSource` enum and timestamp tracking in the command path
6. **UDP listener** — placeholder for handheld controller (can be enabled later)

The motor output, battery ADC, deadman timeout, and e-stop logic are completely unchanged.

### Memory budget

**RAM (320KB total, 21KB currently used):**
- Wi-Fi stack: ~50KB
- AsyncWebServer + WebSocket: ~20KB
- mDNS: ~5KB
- Application buffers: ~5KB
- **Estimated total: ~100KB (~31%)** — well within limits

**Flash (4MB total):**
- Firmware partition: ~1.5MB (current firmware is 271KB)
- LittleFS partition: 512KB–1MB (dashboard HTML + nipplejs ≈ 30–50KB)
- Requires custom partition table: `default_ffat.csv` or a custom `partitions.csv` allocating a `spiffs` (LittleFS) partition

### Partition table

The default ESP32 partition scheme has no filesystem partition. A custom `partitions.csv` is required:

```csv
# Name,   Type, SubType, Offset,  Size,    Flags
nvs,      data, nvs,     0x9000,  0x5000,
otadata,  data, ota,     0xe000,  0x2000,
app0,     app,  ota_0,   0x10000, 0x1E0000,
spiffs,   data, spiffs,  0x1F0000,0x210000,
```

This gives ~1.9MB for firmware and ~2.1MB for LittleFS. Referenced in `platformio.ini`:
```ini
board_build.partitions = partitions.csv
board_build.filesystem = LittleFS
```

## Phases

### Phase S2-1: Wi-Fi AP + WebSocket echo + latency test
- Add Wi-Fi AP mode to firmware (WPA2, configurable SSID/password)
- Add WebSocket server that echoes received messages to serial
- Verify a browser can connect and send text
- **Measure round-trip latency:** dashboard sends timestamp, firmware echoes it back, dashboard measures delta. Target: <50ms average.
- **No motor control yet** — just proving the transport works

### Phase S2-2: Command routing + safety
- Wire WebSocket messages into `parseCommand()`
- Add source arbitration logic (with `g_activeSource` enum)
- WebSocket `onDisconnect` triggers `safeStop()`
- Enforce single-sender WebSocket policy (first-connected wins, others spectate)
- Add Wi-Fi status to serial telemetry
- Verify motor control works over WebSocket (using a simple test page or browser console)

### Phase S2-3: Web dashboard
- Build the dashboard HTML with nipplejs joystick, e-stop, telemetry display
- Upload to LittleFS
- Serve from ESP32 HTTP server
- End-to-end test: connect phone/laptop to AP, open dashboard, drive rover
- Test on both desktop (mouse) and mobile (touch)

### Phase S2-4: STA mode + mDNS
- Add Station mode as compile-time option
- Initialize mDNS: `rc-rover.local`
- Print assigned IP to serial on boot
- Test dashboard over home Wi-Fi via both IP and mDNS hostname

### Phase S2-5: UDP listener
- Add UDP socket on port 4210
- Wire into command parser with source arbitration
- Test with a simple Python script sending T,R,H,E,C over UDP
- This prepares the path for the handheld controller

### Phase S2-6: OTA firmware updates (stretch goal)
- Add OTA upload endpoint at `/update` (POST binary firmware)
- Protected by a simple password
- Enables firmware iteration without USB cable
- Trivial to implement with ESPAsyncWebServer's built-in OTA handler

## Success criteria

- [ ] Rover controllable from a web browser over Wi-Fi (AP mode)
- [ ] Virtual joystick provides smooth, responsive control (<50ms latency)
- [ ] E-stop and deadman timeout work identically to BLE
- [ ] WebSocket disconnect triggers immediate motor stop
- [ ] BLE and WebSocket coexist without interference
- [ ] Source arbitration prevents controller fights
- [ ] Battery voltage displayed on dashboard
- [ ] STA mode works as a compile-time option with mDNS
- [ ] UDP listener accepts and routes commands
- [ ] Dashboard works on both desktop and mobile browsers

## Out of scope for Stage 2

- Mobile app (uses same WebSocket endpoint, but native app is a later project)
- Handheld physical controller hardware (design planning is separate)
- Encoder telemetry display (placeholder in dashboard; data path added when encoders are integrated)
- Current sensing or advanced telemetry
- Authentication beyond WPA2 password and OTA password
- HTTPS/WSS (unnecessary for local AP; acceptable risk for home Wi-Fi)
