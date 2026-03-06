// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

#ifdef POINTING_DEVICE_ENABLE

// Drag scroll state
static bool drag_scroll_enabled = false;

void simian_set_pointer_dragscroll_enabled(bool enable) {
    drag_scroll_enabled = enable;
}

bool simian_get_pointer_dragscroll_enabled(void) {
    return drag_scroll_enabled;
}

// DPI management
static uint16_t dpi_levels[] = {400, 800, 1200, 1600, 2000};
static uint8_t  dpi_index    = 1; // Start at 800 DPI
static uint16_t sniping_dpi  = 200;
bool            sniping_enabled = false;

void simian_update_cpi(void) {
    if (sniping_enabled) {
        pointing_device_set_cpi(sniping_dpi);
    } else {
        pointing_device_set_cpi(dpi_levels[dpi_index]);
    }
}

void simian_dpi_up(void) {
    if (dpi_index < (sizeof(dpi_levels) / sizeof(dpi_levels[0]) - 1)) {
        dpi_index++;
        simian_update_cpi();
    }
}

void simian_dpi_down(void) {
    if (dpi_index > 0) {
        dpi_index--;
        simian_update_cpi();
    }
}

void simian_dpi_cycle(void) {
    dpi_index = (dpi_index + 1) % (sizeof(dpi_levels) / sizeof(dpi_levels[0]));
    simian_update_cpi();
}

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
    pointing_device_set_cpi(800);
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (drag_scroll_enabled) {
        static int16_t scroll_buffer_x = 0;
        static int16_t scroll_buffer_y = 0;

        scroll_buffer_x += mouse_report.x;
        scroll_buffer_y += mouse_report.y;

        mouse_report.x = 0;
        mouse_report.y = 0;

        if (abs(scroll_buffer_x) > 6) {
            mouse_report.h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > 6) {
            mouse_report.v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }

    return mouse_report;
}

#endif // POINTING_DEVICE_ENABLE
