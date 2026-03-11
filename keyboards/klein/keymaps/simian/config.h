// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Use PIO1 for split serial (PIO0 reserved for WS2812 if added later)
#define SERIAL_PIO_USE_PIO1

// USB is always on the left half
#define MASTER_LEFT
