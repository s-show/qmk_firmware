// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY_US_US = 0, // keycap is US, OS keyboard layout is US.
    _QWERTY_US_JIS, // keycap is US, OS keyboard layout is JIS.
    _QWERTY_JIS_US, // keycap is JIS, OS keyboard layout is JIS.
    _QWERTY_JIS_JIS, // keycap is JIS, OS keyboard layout is JIS.
    _LOWER_US_US,
    _LOWER_US_JIS,
    _LOWER_JIS_US,
    _LOWER_JIS_JIS,
    _RAISE_US_US,
    _RAISE_US_JIS,
    _RAISE_JIS_US,
    _RAISE_JIS_JIS,
    _ADJUST_US_US,
    _ADJUST_US_JIS,
    _ADJUST_JIS_US,
    _ADJUST_JIS_JIS,
};

// External variables
extern enum layer_number isCurrentLayer;
extern enum layer_number isDefaultLayer;
