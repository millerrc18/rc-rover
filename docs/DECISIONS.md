# Decisions

This file records important decisions made in the project.  Each entry should include a date, a status (proposed/accepted/rejected/superseded), the decision, the rationale and any implications.

---

**Date:** 2026‑03‑11
**Status:** Accepted
**Decision:** Use a documentation‑driven memory system in the repository to capture project state, decisions, next steps and learnings.
**Rationale:** The project will span many sessions and the chat history cannot be assumed to persist.  A durable memory system in the repository ensures that future agents and contributors can recover context.
**Implications:** All work must be accompanied by updates to the documentation.  Agents must follow the workflow defined in `AGENTS.md`.

---

**Date:** 2026‑03‑11
**Status:** Accepted
**Decision:** Adopt a modular growth plan for the rover: start as a simple manual RC platform and progressively add sensors, telemetry and autonomy.
**Rationale:** A modular approach allows incremental learning and development while avoiding scope creep.
**Implications:** Early stages should focus on simplicity and reliability.  Later stages can layer complexity without rewriting the base.

---

**Date:** 2026‑03‑11
**Status:** Assumption
**Decision:** Use the temporary name `rc-rover` until a permanent name is chosen.
**Rationale:** The project needs a working identifier, but the final branding will be determined later.
**Implications:** Avoid tying external dependencies (e.g. printed labels, domain names) to the temporary name.
---

**Date:** 2026-03-11
**Status:** Accepted
**Decision:** Use a robotics-first differential-drive rover as the Stage 0/1 base-platform direction.
**Rationale:** Differential drive gives the project the cleanest path into sensing, encoders, telemetry, and later autonomy while keeping the mechanical system simple at the beginning.
**Consequences:** Early work should optimize for flat deck space, simple motor control, clear wiring, and repeatable documentation rather than car-like steering or custom-frame aesthetics.

---

**Date:** 2026-03-11
**Status:** Accepted
**Decision:** Use an ESP32-class development board as the primary early-stage controller.
**Rationale:** ESP32 provides a practical bridge between basic embedded control and wireless experimentation without requiring a Linux-class compute stack in the first build.
**Consequences:** The first firmware work should target simple motor control, serial debug, and battery-voltage reporting, with wireless teleop as a likely next step.

---

**Date:** 2026-03-12
**Status:** Accepted
**Decision:** Standardize on **Espressif ESP32-DevKitC-32E** as the Stage 1 development board.
**Rationale:** It is a broadly documented, low-friction ESP32 baseline with straightforward USB flashing/debug and predictable bring-up behavior for early firmware work.
**Consequences:** Firmware examples, pin planning, and assembly documentation should target DevKitC-32E pinout assumptions first; equivalents are allowed only when functionally compatible.

---

**Date:** 2026-03-12
**Status:** Accepted
**Decision:** Use **Pololu Romi Motor Driver and Power Distribution Board** as the primary Stage 1 motor-driver path.
**Rationale:** Romi-native integration reduces mechanical and wiring uncertainty versus generic driver breakout combinations during first build.
**Consequences:** Stage 1 assembly and interface docs prioritize this board; alternate driver paths may be evaluated only after Stage 1 baseline is validated.

---

**Date:** 2026-03-12
**Status:** Accepted
**Decision:** Use **Bluetooth (BLE) teleop** as the initial manual-control method for Stage 1.
**Rationale:** BLE uses ESP32 built-in radios without extra hardware and avoids early Wi-Fi network/config complexity while still enabling phone-based control.
**Consequences:** Initial firmware scaffold should implement BLE command/heartbeat handling; Wi-Fi teleop remains a later optional enhancement.

---

**Date:** 2026-03-12
**Status:** Accepted
**Decision:** Freeze Stage 1 ESP32 logic-power path as `Motor Driver/Power Board regulated 5V output -> ESP32-DevKitC-32E 5V pin` for untethered operation, and freeze bench bring-up cable as `USB-A to Micro-USB data cable`.
**Rationale:** Previous docs allowed board-dependent and power-source ambiguity that could block bench bring-up reproducibility.
**Consequences:** Wiring docs, BOM, and bring-up workflow now use a single explicit power path and connector standard for Stage 1.



---

**Date:** 2026-03-13
**Status:** Accepted
**Decision:** Implement Stage 1 firmware as a minimal single-loop PlatformIO/Arduino baseline with a plain-text BLE write protocol (`T,R,H,E,C`) for fastest bench bring-up.
**Rationale:** Stage 1 success depends on fast, debuggable hardware validation rather than protocol sophistication; a compact ASCII control packet is easy to send from generic phone BLE tools and inspect over serial.
**Consequences:** Control protocol is intentionally simple and may be superseded later by a binary or schema-validated profile after Stage 1 acceptance is complete.


---

**Date:** 2026-03-14
**Status:** Accepted
**Decision:** Treat the full Romi chassis kit (`Pololu #3506`, blue) as the Stage 1 baseline purchase and avoid duplicating included drivetrain components in the initial order.
**Rationale:** The full kit already includes motors, wheels, caster, and integrated 6xAA holder; separate purchases at initial procurement add avoidable cost and confusion.
**Consequences:** BOM and procurement tracker must distinguish buy-now items from optional spares and included-with-kit components.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Treat Stage 1 Romi platform (Rover A / Mk1) as the learning baseline, not the final payload platform.
**Rationale:** Stage 1 execution should optimize learning speed, safety, and reproducibility rather than payload scale.
**Consequences:** Stage 1 hardware baseline remains unchanged while future generations handle higher payload/tow requirements.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Define Rover B / Mk2 as the next target platform when payload/towing needs exceed Mk1 learning envelope.
**Rationale:** Planned payload-class work requires a larger and more stable physical platform than Romi-class hardware.
**Consequences:** Mk2 is documented as planned scope only and does not change current Stage 1 execution priorities.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Maintain Rover C / Mk3 and Rover D / Mk4 as structured future targets.
**Rationale:** Explicit future targets improve long-range planning, skill progression, and architecture portability decisions.
**Consequences:** Mk3/Mk4 are documented for roadmap clarity only; no implementation has started.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Separate platform generations (`Mk#`) from implementation iterations (`v#.#`).
**Rationale:** Physical platform shifts and firmware/document iteration are different axes of change and must not be conflated.
**Consequences:** Docs should reference Mk-level platform strategy independently from version-level iteration tracking.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Preserve electric traction as the core mobility architecture across rover generations; if hybrid is explored later, prefer serial hybrid / range-extender architecture over direct mechanical gas drive.
**Rationale:** This preserves low-speed controllability, preserves indoor battery-only operation, and minimizes drivetrain complexity relative to dual-propulsion or direct gas-drive approaches.
**Consequences:** Hybrid propulsion remains future-planning-only, out of scope for Rover A / Mk1 and Rover B / Mk2, with no change to the current Stage 1 hardware baseline.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Accept GPIO14 as the Stage 1 right motor direction pin with a documented LOW-initialization constraint and a no-external-pull-up rule.
**Rationale:** GPIO14 is a boot-strapping pin, but the direction signal is a static digital output initialized LOW at startup, which is safe. The Romi Motor Driver board M2DIR input does not pull the pin HIGH. No pull-up resistor is to be added. If boot instability is observed in hardware bring-up, the fallback is GPIO33.
**Consequences:** `STAGE_1_PIN_MAP.md` documents the constraint. The firmware must initialize GPIO14 LOW before any other operation. Pull-up resistors on this line are prohibited.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Add a dedicated `firmware/stage1-motor-test/` sketch for first hardware bring-up motor validation, separate from the BLE production baseline.
**Rationale:** The production firmware requires a BLE app to send commands before any motor responds, which creates a dependency that can block or confuse first bring-up. A standalone test sketch eliminates that dependency and confirms motor wiring independently.
**Consequences:** The motor test sketch must maintain the same frozen pin map as the production firmware. The build guide Phase 7 instructs builders to flash it first, then reflash the production baseline.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Set Stage 1 battery voltage divider resistor values to R1=20kΩ and R2=10kΩ (ratio 3.0×), matching the existing firmware `BATTERY_DIVIDER_RATIO = 3.0f` constant.
**Rationale:** The firmware constant was already set to 3.0× but the physical resistor values were never specified in any document. R1=20kΩ / R2=10kΩ gives exactly 3.0× step-down, keeps the ADC pin within 3.3V at 8.4V maximum pack voltage (freshly charged NiMH), and uses common standard values.
**Consequences:** `STAGE_1_WIRING_DIAGRAM.md` now specifies these values explicitly. `STAGE_1_TUNING.md` includes a calibration procedure for the `BATTERY_CALIBRATION` firmware constant.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Target a multi-platform control architecture with a handheld physical controller (with integrated screen) as the primary long-term control surface.
**Rationale:** The project vision is to drive the rover from multiple surfaces — web dashboard, mobile app, and a purpose-built handheld controller with screen and physical joysticks. The physical controller is the most compelling target and should guide architecture decisions now rather than be retrofitted later.
**Consequences:** Control surface work is out of scope for Stage 1 but should be planned starting in Stage 2. All three surfaces (web, mobile, physical controller) are valid targets and should share a common command protocol.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Add Wi-Fi as a second transport alongside BLE in Stage 2, exposing the same T,R,H,E,C command protocol over both transports.
**Rationale:** BLE is sufficient for Stage 1 bring-up but limits control surface options. Wi-Fi is already available on the ESP32 with no additional hardware. Keeping the command protocol identical across transports means the firmware control loop does not change — only the ingestion path does. This directly enables the web dashboard, mobile app, and physical controller targets.
**Consequences:** Stage 1 firmware remains BLE-only. Stage 2 adds Wi-Fi command intake alongside BLE. The T,R,H,E,C packet format is frozen as the cross-transport protocol standard. BLE is not removed — it remains a fallback transport.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Design the physical handheld controller as a standalone device (Raspberry Pi Zero class + small touchscreen + physical joysticks) communicating with the rover over Wi-Fi.
**Rationale:** A self-contained handheld with a screen and physical controls is the most capable and satisfying long-term control surface. Using Wi-Fi as the transport keeps it consistent with the broader multi-platform architecture. A Pi Zero class board provides enough compute for a display, joystick input, and a telemetry UI without being over-engineered for the task.
**Consequences:** Physical controller is a future project (post Stage 2 Wi-Fi transport). It is recorded now so architecture decisions along the way do not inadvertently close off this path. No hardware is purchased or scope opened for it until Stage 1 is complete.

---

**Date:** 2026-03-17
**Status:** Accepted
**Decision:** Substitute R1=22kΩ for the originally specified 20kΩ in the battery voltage divider.
**Rationale:** 22kΩ was available in the resistor assortment; 20kΩ was not. R1=22kΩ / R2=10kΩ gives a 3.2× ratio. Maximum ADC pin voltage at 8.4V pack is 2.625V — safely within the ESP32 3.3V limit. No change to the physical safety margin.
**Consequences:** `BATTERY_DIVIDER_RATIO` in firmware updated from `3.0f` to `3.2f`. `STAGE_1_WIRING_DIAGRAM.md` updated to reflect R1=22kΩ and 3.2× ratio. One-time calibration against a multimeter reading still recommended after first power-on.
