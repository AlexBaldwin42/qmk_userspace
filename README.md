# Simian QMK Userspace

External QMK userspace for the **simian** keymap. Contains the full simityl keyboard definition and shared keymap code that works across multiple keyboards.

## Keyboards

| Keyboard | Layout | Notes |
|---|---|---|
| **simityl** | 36-key split (3x5+3) | Custom skeletyl + PMW3389 trackball + encoder, RP2040 |
| **crkbd** (corne) | 42-key split (3x6+3) | Uses shared 36-key core with outer columns |
| **bastardkb/scylla** | 58-key split (4x6+5) | Uses shared 36-key core with number row + outer columns |

## Setup from scratch

1. **Set up QMK** (vanilla upstream — no fork needed):
   ```
   qmk setup
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
   ```

## Build all targets at once

```
qmk userspace-compile
```

## File structure

```
users/simian/
├── simian.h            — layers, custom keycodes, weak function declarations
├── simian.c            — process_record_user, tapping term, shared behavior
├── wrappers.h          — home row mod macros, layer definitions, layout wrappers
├── simian_pointing.c   — drag scroll, DPI, sniping (only if POINTING_DEVICE_ENABLE)
├── simian_encoder.c    — layer-aware encoder (only if ENCODER_ENABLE)
├── simian_rgb.c        — priority layer color indicators (only if RGB_MATRIX_ENABLE)
├── config.h            — shared config (tapping term, permissive hold, caps word)
└── rules.mk            — conditional source inclusion, feature enables

keyboards/simityl/      — full keyboard definition (pins, matrix, LED map)
keyboards/simityl/keymaps/simian/   — thin keymap using shared wrappers
keyboards/crkbd/keymaps/simian/     — corne keymap
keyboards/bastardkb/scylla/keymaps/simian/  — scylla keymap
```

## PMW3360 variant

One simityl keyboard uses a PMW3360 sensor instead of PMW3389. To build for it, change the driver in `keyboards/simityl/keymaps/simian/rules.mk`:
```
POINTING_DEVICE_DRIVER = pmw3360
```
