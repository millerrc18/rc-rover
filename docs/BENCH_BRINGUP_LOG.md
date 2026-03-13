# Bench Bring-up Log

_Last updated: 2026-03-13_

This document is a **future-use template** for each real hardware bring-up session.

Current repository reality: no bench bring-up sessions have been performed yet.

## Run template

### Session metadata
- **Date:**
- **Operator:**
- **Firmware version/commit:**
- **Hardware configuration used:**
  - ESP32 board:
  - Motor driver board:
  - Battery pack:
  - Wiring harness revision/notes:

### Power and startup checks
- **USB power test result:** Pass / Fail
  - Notes:
- **Battery power test result:** Pass / Fail
  - Notes:
- **Safe startup behavior result (no unexpected motion):** Pass / Fail
  - Notes:

### Motion checks (wheels elevated first)
- **Motor left spin test result:** Pass / Fail
  - Forward direction expected?
  - Reverse direction expected?
  - Notes:
- **Motor right spin test result:** Pass / Fail
  - Forward direction expected?
  - Reverse direction expected?
  - Notes:

### Telemetry/safety checks
- **ADC reading result:** Pass / Fail
  - Reported voltage range:
  - Compared with meter (if available):
  - Notes:
- **Deadman result:** Pass / Fail
  - Timeout setting used:
  - Stop delay observed:
  - Notes:
- **E-stop result:** Pass / Fail
  - Latch behavior observed:
  - Clear behavior observed:
  - Notes:

### Outcome
- **Issues found:**
- **Next actions:**
- **Stage 1 acceptance impact:**
