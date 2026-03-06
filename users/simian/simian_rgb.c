// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_user(void) {
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
        hsv.v = MIN(hsv.v, rgb_matrix_get_val());
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
    return true;
}

#endif // RGB_MATRIX_ENABLE
