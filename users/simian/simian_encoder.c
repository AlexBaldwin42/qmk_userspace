// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(LAYER_ADJUST)) {
        tap_code_delay(clockwise ? KC_VOLU : KC_VOLD, 10);
    } else if (IS_LAYER_ON(LAYER_LOWER)) {
        tap_code16(clockwise ? C(KC_TAB) : C(S(KC_TAB)));
    } else if (IS_LAYER_ON(LAYER_RAISE)) {
        for (int i = 0; i < 5; i++) {
            tap_code16(clockwise ? MS_WHLU : MS_WHLD);
        }
    } else if (IS_LAYER_ON(LAYER_NUMPAD)) {
        tap_code16(clockwise ? KC_RIGHT : KC_LEFT);
    } else {
        tap_code16(clockwise ? MS_WHLU : MS_WHLD);
    }
    return false;
}

#endif // ENCODER_ENABLE
