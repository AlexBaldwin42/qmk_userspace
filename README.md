# Simian QMK Userspace

External QMK userspace containing keymaps and shared code for multiple keyboards.

## Keyboards

| Keyboard | Layout | Notes |
|---|---|---|
| **simityl** | 36-key split (3x5+3) | Custom skeletyl + PMW3389 trackball + encoder, RP2040 |
| **puttzpad** | 20-key ortho (5x4) | Custom numpad with encoder, RP2040 |
| **crkbd** (corne) | 42-key split (3x6+3) | Uses shared 36-key core with outer columns |
| **bastardkb/scylla** | 58-key split (4x6+5) | Uses shared 36-key core with number row + outer columns |

## Setup from scratch

1. **Set up QMK with the fork** (needed for simityl and puttzpad keyboard definitions):
   ```
   qmk setup AlexBaldwin42/qmk_firmware -b simian_main
   ```

2. **Clone this repo:**
   ```
   git clone git@github.com:AlexBaldwin42/qmk_userspace.git ~/qmk_userspace
   ```

3. **Point QMK at it:**
   ```
   qmk config user.overlay_dir="$(realpath ~/qmk_userspace)"
   ```

4. **Compile:**
   ```
   qmk compile -kb simityl -km simian
   qmk compile -kb puttzpad -km default
   ```

## Build all targets at once

```
qmk userspace-compile
```

## Architecture

Custom keyboard definitions (simityl, puttzpad) live in the **QMK fork** (`AlexBaldwin42/qmk_firmware` branch `simian_main`) because QMK's overlay system only supports keymaps, not new keyboards. Upstream keyboards (crkbd, scylla) need no fork.

All keymap code and shared behavior lives in **this userspace repo**.

## File structure

```
users/simian/               — shared keymap code (used by simityl, crkbd, scylla)
├── simian.h                — layers, custom keycodes, weak function declarations
├── simian.c                — process_record_user, tapping term, shared behavior
├── wrappers.h              — home row mod macros, layer definitions, layout wrappers
├── simian_pointing.c       — drag scroll, DPI, sniping (only if POINTING_DEVICE_ENABLE)
├── simian_encoder.c        — layer-aware encoder (only if ENCODER_ENABLE)
├── simian_rgb.c            — priority layer color indicators (only if RGB_MATRIX_ENABLE)
├── config.h                — shared config (tapping term, permissive hold, caps word)
└── rules.mk                — conditional source inclusion, feature enables

keyboards/simityl/keymaps/simian/           — simityl keymap (thin wrapper)
keyboards/puttzpad/keymaps/default/         — puttzpad keymap (standalone numpad)
keyboards/crkbd/keymaps/simian/             — corne keymap
keyboards/bastardkb/scylla/keymaps/simian/  — scylla keymap
```

## PMW3360 variant

One simityl keyboard uses a PMW3360 sensor instead of PMW3389. To build for it, change the driver in `keyboards/simityl/keymaps/simian/rules.mk`:
```
POINTING_DEVICE_DRIVER = pmw3360
```

## Adding VIA support to puttzpad

The puttzpad was originally a Vial keyboard. To add VIA support (live remapping without recompiling), create a `keyboards/puttzpad/keymaps/via/` keymap with `VIA_ENABLE = yes` in its `rules.mk`. VIA works with vanilla QMK — no special fork needed.
