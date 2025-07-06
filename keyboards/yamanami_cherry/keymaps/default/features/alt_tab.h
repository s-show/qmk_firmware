// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include <stdbool.h>

/**
 * Cool Function where a single key does ALT+TAB
 * From: https://beta.docs.qmk.fm/features/feature_macros#super-alt-tab
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/dz60/keymaps/_bonfire/not-in-use/super-alt-tab.c
 */
extern bool     is_alt_tab_active;
extern uint16_t alt_tab_timer;
extern bool     is_win_tab_active;
extern uint16_t win_tab_timer;

bool process_alt_tab(uint16_t keycode, keyrecord_t *record);
void alt_tab_matrix_scan(void);
