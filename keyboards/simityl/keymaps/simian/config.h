// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Simityl-specific pointing device config
#ifdef POINTING_DEVICE_ENABLE
#    define POINTING_DEVICE_RIGHT
#    undef POINTING_DEVICE_INVERT_X
#    define POINTING_DEVICE_INVERT_Y
#    define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#    define SPLIT_LAYER_STATE_ENABLE

// High-resolution scrolling. Adds a resolution multiplier to the HID descriptor
// so the host reads each wheel unit as 1/120 of a detent — drag scroll becomes
// smooth instead of notched.
#    define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#    define POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER 120
#    define POINTING_DEVICE_HIRES_SCROLL_EXPONENT 0

// Wheel reports are now 120x larger, which overflows the default int8 field at
// barely one detent. QMK's own docs pair hi-res scroll with this.
#    define WHEEL_EXTENDED_REPORT

// The resolution multiplier applies to EVERY wheel report, including the left
// half's encoder — it taps MS_WHLU/MS_WHLD, and mousekey is not hi-res aware
// (`wheel_unit()` in quantum/mousekey.c knows nothing about the multiplier).
// Left at the default of 1, each encoder click would send 1 unit = 1/120 of a
// detent and the encoder would feel dead. Send a whole detent per click
// instead, and cap acceleration at the same value so a held wheel key can
// never emit more than one detent per report. MOUSEKEY_WHEEL_MAX is hard
// limited to 127 by quantum/mousekey.h, so 120 is the practical ceiling here.
#    define MOUSEKEY_WHEEL_DELTA 120
#    define MOUSEKEY_WHEEL_MAX 120
#endif

// Encoder — the simityl fleet has mixed encoders: most are 4 pulses/detent,
// some are 2. If the encoder only scrolls every other click, build with
// ENCODER_RESOLUTION 2 for that unit (double-scroll means go back to 4).
#define ENCODER_RESOLUTION 4
