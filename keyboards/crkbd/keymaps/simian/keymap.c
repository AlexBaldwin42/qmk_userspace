// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

// Combos (same as simityl — reference home row mod keys)
enum combos {
    DF_DQT,
    SD_QT,
};

const uint16_t PROGMEM df_combo[] = {LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM sd_combo[] = {LALT_T(KC_S), LSFT_T(KC_D), COMBO_END};

combo_t key_combos[] = {
    [DF_DQT] = COMBO(df_combo, KC_DQT),
    [SD_QT]  = COMBO(sd_combo, KC_QUOT),
};

// clang-format off

// Corne: 42 keys = 36-key core + outer columns (Tab/Ctrl/Shift left, Bspc/Quot/Enter right)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  ADJ_KCQ, KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,
                                KC_H, RCTL_T(KC_J), RSFT_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
        KC_LSFT, LCTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  ADJ_SLSH, KC_ENT,
                                    NUM_TAB, LW_BSPC, RAI_DEL,    RAI_ENT, LW_SPC, NUM_ESC
    ),

    [LAYER_POINTER] = LAYOUT_split_3x6_3(
        _______, _______, _______, _______, _______, _______,    MS_BTN1, DRGSCRL, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,    MS_BTN2, SNIPING_MODE, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,    _______, SNIPING_TOGGLE, _______, _______, _______, _______,
                                   _______, MS_BTN1, MS_BTN2,    _______, _______, _______
    ),

    [LAYER_LOWER] = LAYOUT_split_3x6_3(
        _______, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5),    G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0), _______,
        _______, LGUI_T(KC_WBAK), LALT_T(KC_WFWD), LSFT_T(KC_HOME), LCTL_T(KC_END), KC_APP,
                                KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_F6, _______,
        _______, CTL_F1, ALT_F2, C(G(KC_LEFT)), C(G(KC_RIGHT)), KC_F5,
                                KC_F5, KC_F7, KC_F8, ALT_F9, CTL_F10, _______,
                                   _______, _______, _______,    _______, _______, _______
    ),

    [LAYER_RAISE] = LAYOUT_split_3x6_3(
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV,  _______,
        _______, KC_QUOT, KC_DQT,  KC_LPRN, KC_RPRN, KC_PGUP,    KC_MINS, CTL_EQL, KC_LCBR, KC_RCBR, KC_BSLS, _______,
        _______, KC_ESC,  _______, KC_ESC,  KC_ENT,  KC_PGDN,    KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE, _______,
                                   _______, _______, _______,    _______, _______, _______
    ),

    [LAYER_ADJUST] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, TG(LAYER_NUMPAD), KC_CAPS, XXXXXXX, XXXXXXX,    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG, _______,
        _______, RM_TOGG, RM_NEXT, RM_VALU, RM_VALD, XXXXXXX,    XXXXXXX, KC_WBAK, KC_WFWD, KC_APP,  DRG_TOG, _______,
        _______, RM_NEXT, RM_PREV, RM_HUEU, RM_HUED, QK_BOOT,    XXXXXXX, XXXXXXX, DPI_DOWN, DPI_UP, DPI_CYCLE, _______,
                                   _______, _______, _______,    KC_VOLD, KC_VOLU, KC_MPLY
    ),

    [LAYER_NUMPAD] = LAYOUT_split_3x6_3(
        _______, TG(LAYER_NUMPAD), KC_F9, KC_F8, KC_F7, KC_F12,    KC_CIRC, KC_7, KC_8, KC_9, KC_ASTR, _______,
        _______, KC_NO, KC_F6, KC_F5, KC_F4, KC_F11,               KC_MINS, KC_4, KC_5, KC_6, KC_EQL,  _______,
        _______, KC_LSFT, KC_F3, KC_F2, KC_F1, KC_F10,             KC_PLUS, KC_1, KC_2, KC_3, KC_SLSH, _______,
                                   _______, _______, _______,    KC_ENT, KC_0, KC_DOT
    ),
};
// clang-format on
