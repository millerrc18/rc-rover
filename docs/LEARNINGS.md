# Learnings

This file captures lessons learned, mistakes made and heuristics discovered during the project.  Entries should include a date and a brief description.

## 2026‑03‑11

- Establishing a documentation‑driven memory system early on prevents loss of context between sessions and reduces reliance on chat history.
## 2026-03-12

- Aligning `PROJECT_STATE.md` with `HANDOFF.md` and `NEXT_STEPS.md` prevents conflicting phase signals that can misdirect future sessions.
- A freeze package is more actionable when architecture, interface map, and build plan are split into separate docs rather than merged into one long narrative.
- Freezing both bench-power mode and untethered-power mode in the same wiring package prevents hidden integration ambiguity that BOM-only updates often miss.

## 2026-03-13

- A plain-text BLE control packet with explicit heartbeat (`T,R,H,E,C`) is fast to validate on bench hardware and reduces tooling friction during first bring-up.
- Maintaining a dedicated bench bring-up log template prevents ad-hoc test notes and makes acceptance evidence easier to compare across runs.

## 2026-03-17

- Keeping "capability stages" separate from "platform generations" reduces planning confusion and helps protect Stage 1 execution focus from premature scope expansion.

## 2026-03-17

- A build guide written for the wrong board (DRV8833 vs the actual Romi Motor Driver board) will send a builder to wrong terminal names and wiring steps that physically do not exist on the correct hardware. Always name the exact target board in the first sentence of a wiring guide and verify that every terminal label in the document exists on that specific board.
- A pin conflict between a build guide (GPIO33) and a frozen pin map (GPIO14) can survive multiple review passes undetected because they sit in separate documents. Cross-document pin consistency checks should be an explicit step in any wiring documentation review.
- Production firmware that requires BLE app connectivity before any motor moves creates a hidden dependency that blocks first hardware validation. A no-dependency motor test sketch that runs automatically on boot eliminates an entire class of "nothing works and I don't know why" scenarios.
- Firmware constants that reference physical component values (divider ratios, calibration factors) must be traced back to explicit component values in the hardware documentation. A ratio of 3.0 in firmware means nothing to a builder choosing resistors unless the doc says R1=20kΩ / R2=10kΩ.
- Historical documents that accumulate alongside canonical docs confuse agents unless they carry an explicit superseded notice at the top and are listed separately in the index. An agent scanning the repo cannot tell an old roadmap from the current one without a clear signal.

## 2026-03-19

- Documentation-driven projects accumulate files faster than code projects. A periodic consolidation pass (merging small single-purpose files into their parent docs, archiving superseded files) is essential to keep the repo navigable for humans.
- When a substitution changes a value (20kΩ → 22kΩ), every living doc that states the old value must be updated in the same commit. Historical records (BUILD_LOG, DECISIONS) should preserve the original values as history, but operational docs (PROJECT_STATE, HANDOFF, NEXT_STEPS, wiring diagrams) must always reflect the as-built state.
- If documentation claims a firmware feature exists (e.g. "8-sample moving average"), the implementation must actually contain it. Doc-first is good, but doc-only is a bug.

## 2026-03-20

- PlatformIO CLI (`pio`) is not on the system PATH in Windows PowerShell by default. The PlatformIO terminal inside VS Code resolves this. Build guides should mention this as the recommended terminal, not assume `pio` is globally available.
- CP2102 driver installation is a required first step on Windows for ESP32-DevKitC-32E boards. The "Ports (COM & LPT)" section in Device Manager does not appear at all until the driver is installed. Build guides should lead with driver installation before "confirm serial port appears".
- A build guide for a visual learner needs external photo references at every physical phase. Manufacturer documentation (Pololu in this case) already has professional step-by-step photos — linking directly to the right section at each phase is more effective than trying to describe what parts look like in text.
- The DRV8838 motor driver on the Romi board uses DIR LOW = forward by convention, but firmware may use DIR HIGH = forward. This mismatch is harmless — the motor test step exists specifically to catch it — but the build guide should warn that wheels may spin "backward" on first test and that this is expected and fixable in firmware.

## 2026-04-10

- The Romi Motor Driver board's included female headers are designed for the Romi Encoder Pair Kit (#3542), not for bare motor tabs. Without encoders installed, the motors have no electrical connection to the board. The Pololu docs mention this but it's easy to miss — the build guide should explicitly state that encoder boards or terminal blocks are required for motor connection.
- ESP32 boards can fail with a stuck BOOT button or shorted GPIO0, causing permanent DOWNLOAD_BOOT mode. Symptoms: `boot:0x1 (DOWNLOAD_BOOT)` on every reset even with nothing connected. The fix is to swap the board. Keep a spare ESP32 on hand.
- When an ESP32 enters download mode after a flash, pressing EN (reset) usually fixes it. If it persists across power cycles with all wires disconnected, the board is likely defective.
- Desoldering through-hole pin headers is significantly harder than initial soldering. Solder wick with fresh flux and added solder for heat transfer is the most reliable technique. Prevention (checking orientation before soldering all pins) is far cheaper than correction.
