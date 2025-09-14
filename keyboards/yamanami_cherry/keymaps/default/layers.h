// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY_UU = 0, // keycap is US, OS keyboard layout is US.
    _QWERTY_UJ, // keycap is US, OS keyboard layout is JIS.
    _QWERTY_JU, // keycap is JIS, OS keyboard layout is JIS.
    _QWERTY_JJ, // keycap is JIS, OS keyboard layout is JIS.
    _LOWER_UU,
    _LOWER_UJ,
    _LOWER_JU,
    _LOWER_JJ,
    _RAISE_UU,
    _RAISE_UJ,
    _RAISE_JU,
    _RAISE_JJ,
    _ADJUST_UU,
    _ADJUST_UJ,
    _ADJUST_JU,
    _ADJUST_JJ,
};

// External variables
extern enum layer_number isCurrentLayer;
extern enum layer_number isDefaultLayer;
