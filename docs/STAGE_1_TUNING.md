# Stage 1 Tuning Notes

_Last updated: 2026-03-13_

Field-ready notes for first tuning passes after baseline firmware flash.

## Initial tuning variables

- **Deadman timeout:** `300 ms` (conservative default)
- **PWM frequency:** `18 kHz`
- **PWM resolution:** `8-bit`
- **PWM floor:** `0` (safest initial behavior)
- **Turn scaling:** `1.0`
- **Low-voltage behavior:** warning/reporting only (no automatic power limiting in baseline)

## Bench tuning checklist

1. Start with wheels elevated.
2. Verify neutral (`T=0,R=0`) gives no wheel motion.
3. Raise throttle slowly and note first effective PWM for each side.
4. Apply left/right turn at low throttle and check controllability symmetry.
5. Trigger deadman and e-stop repeatedly before floor testing.
6. Record any low-voltage sag symptoms under light drive.

## Test note table

| Date | Firmware commit | Deadman (ms) | PWM floor | Turn scaling | Low-voltage observations | Notes |
|---|---|---:|---:|---:|---|---|
| 2026-03-13 | _TBD_ | 300 | 0 | 1.0 | _TBD after hardware test_ | Baseline values established in firmware |
