// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

// Layer definitions — consistent across all keyboards
enum simian_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
    LAYER_NUMPAD,
    LAYER_POINTER,
};

// Custom keycodes — portable across keyboards (uses SAFE_RANGE, not QK_KB)
enum simian_keycodes {
    DRGSCRL = QK_USER_0,
    DRG_TOG,
    DPI_UP,
    DPI_DOWN,
    DPI_CYCLE,
    SNIPING_MODE,
    SNIPING_TOGGLE,
    NEW_SAFE_RANGE,
};

// Drag scroll state (implemented in simian_pointing.c)
#ifdef POINTING_DEVICE_ENABLE
bool simian_get_pointer_dragscroll_enabled(void);
void simian_set_pointer_dragscroll_enabled(bool enable);
#endif

// Sniping state (implemented in simian_pointing.c)
#ifdef POINTING_DEVICE_ENABLE
extern bool sniping_enabled;
#endif

// Weak functions for per-keyboard overrides
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void keyboard_post_init_keymap(void);

#include "wrappers.h"
