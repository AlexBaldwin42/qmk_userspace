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
#endif

// Encoder — the simityl fleet has mixed encoders: most are 4 pulses/detent,
// some are 2. If the encoder only scrolls every other click, build with
// ENCODER_RESOLUTION 2 for that unit (double-scroll means go back to 4).
#define ENCODER_RESOLUTION 4
