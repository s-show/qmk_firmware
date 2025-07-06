// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "alt_tab.h"
#include "keycodes.h"

bool     is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
bool     is_win_tab_active = false; // ADD this near the begining of keymap.c
uint16_t win_tab_timer     = 0;     // we will be using them soon.

bool process_alt_tab(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case WIN_TAB:
            if (record->event.pressed) {
                if (!is_win_tab_active) {
                    is_win_tab_active = true;
                    tap_code16(G(KC_TAB));
                }
                win_tab_timer = timer_read();
            }
            break;
        case KC_DOWN:
        case KC_RGHT:
        case KC_LEFT:
        case KC_UP:
        case KC_TAB:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                    alt_tab_timer = timer_read();
                }
                if (is_win_tab_active) {
                    win_tab_timer = timer_read();
                }
            }
            return true;
            break;
        case KC_J:
        case KC_S:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                    alt_tab_timer = timer_read();
                    register_code(KC_DOWN);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    win_tab_timer = timer_read();
                    register_code(KC_DOWN);
                    return false;
                    break;
                }
            } else {
                if (is_alt_tab_active) {
                    unregister_code(KC_DOWN);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    unregister_code(KC_DOWN);
                    return false;
                    break;
                }
            }
            return true;
            break;
        case KC_K:
        case KC_W:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                    alt_tab_timer = timer_read();
                    register_code(KC_UP);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    win_tab_timer = timer_read();
                    register_code(KC_UP);
                    return false;
                    break;
                }
            } else {
                if (is_alt_tab_active) {
                    unregister_code(KC_UP);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    unregister_code(KC_UP);
                    return false;
                    break;
                }
            }
            return true;
            break;
        case KC_H:
        case KC_A:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                    alt_tab_timer = timer_read();
                    register_code(KC_LEFT);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    win_tab_timer = timer_read();
                    register_code(KC_LEFT);
                    return false;
                    break;
                }
            } else {
                if (is_alt_tab_active) {
                    unregister_code(KC_LEFT);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    unregister_code(KC_LEFT);
                    return false;
                    break;
                }
            }
            return true;
            break;
        case KC_L:
        case KC_D:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                    alt_tab_timer = timer_read();
                    register_code(KC_RGHT);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    win_tab_timer = timer_read();
                    register_code(KC_RIGHT);
                    return false;
                    break;
                }
            } else {
                if (is_alt_tab_active) {
                    unregister_code(KC_RGHT);
                    return false;
                    break;
                }
                if (is_win_tab_active) {
                    unregister_code(KC_RIGHT);
                    return false;
                    break;
                }
            }
            return true;
            break;
        default:
            if (is_alt_tab_active) {
                unregister_code(KC_LALT);
                is_alt_tab_active = false;
            }
            break;
    }
    return true;
}

// The very important timer for ALT-TAB key.
void alt_tab_matrix_scan(void) {
    if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 1000) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
    if (is_win_tab_active && timer_elapsed(win_tab_timer) > 1000) {
        is_win_tab_active = false;
    }
}
