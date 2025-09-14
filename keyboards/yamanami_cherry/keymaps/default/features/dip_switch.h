// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>

bool dip_switch_update_mask_user(uint32_t state) {
    // #ifdef CONSOLE_ENABLE
    //     uprintf("switch state: %lu\n", state);
    // #endif
    switch (state) {
        // keycap is US, OS layout is US.
        case 0:
            set_single_persistent_default_layer(0);
            isDefaultLayer                      = _QWERTY_UU;
            keymap_config.swap_lalt_lgui        = false;
            keymap_config.swap_control_capslock = false;
            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 1:
            set_single_persistent_default_layer(1);
            isDefaultLayer               = _QWERTY_UJ;
            keymap_config.swap_lalt_lgui = false;

            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;

        // keycap is JIS, OS layout is US.
        case 2:
            set_single_persistent_default_layer(2);
            isDefaultLayer                      = _QWERTY_JU;
            keymap_config.swap_lalt_lgui        = false;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        // keycap is JIS, OS layout is JIS.
        case 3:
            set_single_persistent_default_layer(3);
            isDefaultLayer                      = _QWERTY_JJ;
            keymap_config.swap_lalt_lgui        = false;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
            // keycap is US, OS layout is US.

        case 4:
            set_single_persistent_default_layer(0);
            isDefaultLayer                      = _QWERTY_UU;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = false;

            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 5:
            set_single_persistent_default_layer(1);
            isDefaultLayer                      = _QWERTY_UJ;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        // keycap is JIS, OS layout is US.
        case 6:
            set_single_persistent_default_layer(2);
            isDefaultLayer                      = _QWERTY_JU;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = false;
            break;
        // keycap is JIS, OS layout is JIS.
        case 7:
            set_single_persistent_default_layer(3);
            isDefaultLayer                      = _QWERTY_JJ;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = false;
            break;
        // keycap is US, OS layout is US.
        case 8:
            set_single_persistent_default_layer(0);
            isDefaultLayer                      = _QWERTY_UU;
            keymap_config.swap_lalt_lgui        = false;
            keymap_config.swap_control_capslock = true;
            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 9:
            set_single_persistent_default_layer(1);
            isDefaultLayer                      = _QWERTY_UJ;
            keymap_config.swap_lalt_lgui        = false;
            keymap_config.swap_control_capslock = true;

            key_override_on();
            break;
        // keycap is JIS, OS layout is US.
        case 10:
            set_single_persistent_default_layer(2);
            isDefaultLayer                      = _QWERTY_JU;
            keymap_config.swap_lalt_lgui        = false;
            keymap_config.swap_control_capslock = true;
            break;
        // keycap is JIS, OS layout is JIS.
        case 11:

            set_single_persistent_default_layer(3);
            isDefaultLayer                      = _QWERTY_JJ;
            keymap_config.swap_lalt_lgui        = false;
            keymap_config.swap_control_capslock = true;
            break;
        // keycap is US, OS layout is US.
        case 12:
            set_single_persistent_default_layer(0);

            isDefaultLayer                      = _QWERTY_UU;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = true;

            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 13:
            set_single_persistent_default_layer(1);
            isDefaultLayer                      = _QWERTY_UJ;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = true;
            key_override_on();
            break;
        // keycap is JIS, OS layout is US.
        case 14:
            set_single_persistent_default_layer(2);
            isDefaultLayer                      = _QWERTY_JU;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = true;
            break;
        // keycap is JIS, OS layout is JIS.
        case 15:

            set_single_persistent_default_layer(3);
            isDefaultLayer                      = _QWERTY_JJ;
            keymap_config.swap_lalt_lgui        = true;
            keymap_config.swap_control_capslock = true;

            break;
    }
    isCurrentLayer = isDefaultLayer;
    return true;
}
