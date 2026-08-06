// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simian.h"

#ifdef POINTING_DEVICE_ENABLE

// Drag scroll state

// Counts of ball travel per wheel detent. Larger = slower scrolling.
#ifndef SIMIAN_DRAG_SCROLL_DIVISOR
#    define SIMIAN_DRAG_SCROLL_DIVISOR 6
#endif

// Many applications implement their own scroll smoothing and assume only one
// axis moves at a time; feeding them simultaneous H and V wheel input makes
// scrolling slow or jittery. QMK's pointing device docs call this out
// specifically for hi-res drag scroll. Lock to whichever axis wins first and
// release once the ball has been still this long. Set to 0 to disable.
#ifndef SIMIAN_DRAG_SCROLL_SNAP_TIMEOUT_MS
#    define SIMIAN_DRAG_SCROLL_SNAP_TIMEOUT_MS 100
#endif

static bool drag_scroll_enabled = false;

// Accumulated wheel units not yet reported. Kept across polls so the remainder
// below one detent is carried instead of discarded — otherwise scroll distance
// stops being proportional to ball travel and fast drags under-scroll.
static int32_t  scroll_accum_h    = 0;
static int32_t  scroll_accum_v    = 0;
static uint16_t scroll_last_motion = 0;
static bool     scroll_axis_locked = false;
static bool     scroll_lock_vertical = false;

static void simian_reset_dragscroll(void) {
    scroll_accum_h       = 0;
    scroll_accum_v       = 0;
    scroll_axis_locked   = false;
    scroll_lock_vertical = false;
}

void simian_set_pointer_dragscroll_enabled(bool enable) {
    if (enable != drag_scroll_enabled) {
        simian_reset_dragscroll();
    }
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
        // One detent is this many wheel units. Without hi-res scrolling the
        // host expects whole detents, so a unit and a detent are the same
        // thing and the arithmetic below collapses to the plain case.
#ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
        const int32_t units_per_detent = pointing_device_get_hires_scroll_resolution();
#else
        const int32_t units_per_detent = 1;
#endif

#if SIMIAN_DRAG_SCROLL_SNAP_TIMEOUT_MS > 0
        const bool moved = (mouse_report.x != 0 || mouse_report.y != 0);
#endif

        scroll_accum_h += (int32_t)mouse_report.x * units_per_detent;
        scroll_accum_v += (int32_t)mouse_report.y * units_per_detent;

        mouse_report.x = 0;
        mouse_report.y = 0;

#if SIMIAN_DRAG_SCROLL_SNAP_TIMEOUT_MS > 0
        if (moved) {
            scroll_last_motion = timer_read();
        } else if (scroll_axis_locked && timer_elapsed(scroll_last_motion) > SIMIAN_DRAG_SCROLL_SNAP_TIMEOUT_MS) {
            simian_reset_dragscroll();
        }
#endif

        int32_t ticks_h = scroll_accum_h / SIMIAN_DRAG_SCROLL_DIVISOR;
        int32_t ticks_v = scroll_accum_v / SIMIAN_DRAG_SCROLL_DIVISOR;

#if SIMIAN_DRAG_SCROLL_SNAP_TIMEOUT_MS > 0
        if (!scroll_axis_locked && (ticks_h != 0 || ticks_v != 0)) {
            scroll_axis_locked   = true;
            scroll_lock_vertical = (abs(ticks_v) >= abs(ticks_h));
        }

        if (scroll_axis_locked) {
            if (scroll_lock_vertical) {
                ticks_h        = 0;
                scroll_accum_h = 0;
            } else {
                ticks_v        = 0;
                scroll_accum_v = 0;
            }
        }
#endif

        // Subtract only what was reported, so sub-detent motion carries over.
        if (ticks_h != 0) {
            mouse_report.h = ticks_h;
            scroll_accum_h -= ticks_h * SIMIAN_DRAG_SCROLL_DIVISOR;
        }
        if (ticks_v != 0) {
            mouse_report.v = ticks_v;
            scroll_accum_v -= ticks_v * SIMIAN_DRAG_SCROLL_DIVISOR;
        }
    }

    return mouse_report;
}

#endif // POINTING_DEVICE_ENABLE
