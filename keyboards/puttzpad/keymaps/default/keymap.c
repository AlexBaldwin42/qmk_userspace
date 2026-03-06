// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum puttzpad_layers {
    _NUMPAD = 0,
    _NAV,
};

// clang-format off

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_NUMPAD] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [_NAV]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};

/*  ╭─────┬─────┬─────┬─────╮
 *  │NmLk │  /  │  *  │Bspc │
 *  ├─────┼─────┼─────┼─────┤
 *  │  7  │  8  │  9  │  -  │
 *  ├─────┼─────┼─────┼─────┤
 *  │  4  │  5  │  6  │  +  │
 *  ├─────┼─────┼─────┼─────┤
 *  │  1  │  2  │  3  │  =  │
 *  ├─────┼─────┼─────┼─────┤
 *  │  0  │ NAV │  .  │Enter│
 *  ╰─────┴─────┴─────┴─────╯ */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT_ortho_5x4(
        KC_NUM,  KC_PSLS, KC_PAST, KC_BSPC,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_EQL,
        KC_P0,   MO(_NAV),KC_PDOT, KC_PENT
    ),

    [_NAV] = LAYOUT_ortho_5x4(
        QK_BOOT, _______, _______, KC_DEL,
        KC_HOME, KC_UP,   KC_PGUP, _______,
        KC_LEFT, XXXXXXX, KC_RGHT, _______,
        KC_END,  KC_DOWN, KC_PGDN, _______,
        KC_INS,  _______, _______, _______
    ),
};
// clang-format on
