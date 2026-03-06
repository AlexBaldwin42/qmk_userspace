// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

// Weak functions — overridable per-keyboard
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    keyboard_post_init_keymap();
}

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case RGUI_T(KC_SCLN):
        case LALT_T(KC_S):
        case LALT_T(KC_L):
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

#ifdef POINTING_DEVICE_ENABLE
    switch (keycode) {
        case DPI_UP:
            if (record->event.pressed) {
                extern void simian_dpi_up(void);
                simian_dpi_up();
            }
            return false;

        case DPI_DOWN:
            if (record->event.pressed) {
                extern void simian_dpi_down(void);
                simian_dpi_down();
            }
            return false;

        case DPI_CYCLE:
            if (record->event.pressed) {
                extern void simian_dpi_cycle(void);
                simian_dpi_cycle();
            }
            return false;

        case SNIPING_MODE:
            sniping_enabled = record->event.pressed;
            {
                extern void simian_update_cpi(void);
                simian_update_cpi();
            }
            return false;

        case SNIPING_TOGGLE:
            if (record->event.pressed) {
                sniping_enabled = !sniping_enabled;
                extern void simian_update_cpi(void);
                simian_update_cpi();
            }
            return false;

        case DRGSCRL:
            simian_set_pointer_dragscroll_enabled(record->event.pressed);
            return false;

        case DRG_TOG:
            if (record->event.pressed) {
                simian_set_pointer_dragscroll_enabled(!simian_get_pointer_dragscroll_enabled());
            }
            return false;

        // Don't exit drag scroll for mouse/pointing device keys
        case MS_BTN1:
        case MS_BTN2:
        case MS_BTN3:
        case MS_BTN4:
        case MS_BTN5:
        case MS_WHLU:
        case MS_WHLD:
        case MS_WHLL:
        case MS_WHLR:
            return true;

        // ESC exits drag scroll mode
        case KC_ESC:
            if (record->event.pressed && simian_get_pointer_dragscroll_enabled()) {
                simian_set_pointer_dragscroll_enabled(false);
                return false;
            }
            return true;

        default:
            // Exit drag scroll mode on any other key press
            if (record->event.pressed && simian_get_pointer_dragscroll_enabled()) {
                simian_set_pointer_dragscroll_enabled(false);
            }
            return true;
    }
#endif // POINTING_DEVICE_ENABLE

    return true;
}
