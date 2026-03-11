// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

// Combos
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
#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE]    = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE)),
    [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
    [LAYER_LOWER]   = LAYOUT_wrapper(HOME_ROW_MOD_LEFT_GACS(LAYOUT_LAYER_LOWER)),
    [LAYER_RAISE]   = LAYOUT_wrapper(LAYOUT_LAYER_RAISE),
    [LAYER_ADJUST]  = LAYOUT_wrapper(LAYOUT_LAYER_ADJUST),
    [LAYER_NUMPAD]  = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_NUMPAD)),
};
// clang-format on
