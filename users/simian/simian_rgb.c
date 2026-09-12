// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

#ifdef RGB_MATRIX_ENABLE

// Gaming mode is the one state that must never be mistaken for another, and
// every hue is already close to some other indicator. So it gets a pattern
// instead of just a colour: a purple wash with the keys that matter picked out
// in white — WASD on the game layer, the numbers while GAME_FN is held. No
// other mode lights individual keys.
static bool game_key_highlighted(uint16_t keycode) {
    switch (keycode) {
        case KC_W:
        case KC_A:
        case KC_S:
        case KC_D:
        case KC_1 ... KC_0:
            return true;
        default:
            return false;
    }
}

// Indicators never outshine the brightness the user has set.
static RGB indicator_rgb(HSV hsv) {
    hsv.v = MIN(hsv.v, rgb_matrix_get_val());
    return hsv_to_rgb(hsv);
}

static void set_color_range(HSV hsv, uint8_t led_min, uint8_t led_max) {
    RGB rgb = indicator_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}

static void game_indicators(uint8_t led_min, uint8_t led_max) {
    set_color_range((HSV){HSV_PURPLE}, led_min, led_max);

    RGB rgb = indicator_rgb((HSV){HSV_WHITE});

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index == NO_LED || index < led_min || index >= led_max) {
                continue;
            }
            keypos_t pos = {.row = row, .col = col};
            if (game_key_highlighted(keymap_key_to_keycode(layer_switch_get_layer(pos), pos))) {
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_LAYER_ON(LAYER_GAME)) {
        game_indicators(led_min, led_max);
        return true;
    }

    HSV hsv = {0, 0, 0};

    // Priority-based indicators
#ifdef POINTING_DEVICE_ENABLE
    if (sniping_enabled) {
        hsv = (HSV){HSV_RED};
    } else if (simian_get_pointer_dragscroll_enabled()) {
        hsv = (HSV){HSV_ORANGE};
    } else
#endif
    if (IS_LAYER_ON(LAYER_POINTER)) {
        hsv = (HSV){HSV_GREEN};
    } else if (IS_LAYER_ON(LAYER_NUMPAD)) {
        hsv = (HSV){HSV_BLUE};
    } else if (IS_LAYER_ON(LAYER_RAISE)) {
        hsv = (HSV){HSV_MAGENTA};
    } else if (IS_LAYER_ON(LAYER_LOWER)) {
        hsv = (HSV){HSV_TEAL};
    }

    if (hsv.h != 0 || hsv.s != 0 || hsv.v != 0) {
        set_color_range(hsv, led_min, led_max);
    }
    return true;
}

#endif // RGB_MATRIX_ENABLE
