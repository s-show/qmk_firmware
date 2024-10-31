// #include QMK_KEYBOARD_H
//
// int isCurrentLayer = 0;
//
// /* DIP Switch Setting */
// bool dip_switch_update_mask_kb(uint32_t state) {
//     keymap_config.raw = eeconfig_read_keymap();
//     switch (state) {
//         case 0:
//             // set_single_persistent_default_layer(0);
//             layer_off(_QWERTY_US_JIS);
//             isCurrentLayer = 0;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 1:
//             // set_single_persistent_default_layer(1);
//             layer_on(_QWERTY_US_JIS);
//             isCurrentLayer = 1;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 2:
//             // set_single_persistent_default_layer(2);
//             // isDefaultLayer = 2;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 3:
//             // set_single_persistent_default_layer(3);
//             // isDefaultLayer = 3;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 4:
//             // set_single_persistent_default_layer(0);
//             layer_off(_QWERTY_US_JIS);
//             isCurrentLayer = 0;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 5:
//             // set_single_persistent_default_layer(1);
//             layer_on(_QWERTY_US_JIS);
//             isCurrentLayer = 1;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 6:
//             // set_single_persistent_default_layer(2);
//             // isDefaultLayer = 2;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 7:
//             // set_single_persistent_default_layer(3);
//             // isDefaultLayer = 3;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = false;
//             break;
//         case 8:
//             // set_single_persistent_default_layer(0);
//             layer_off(_QWERTY_US_JIS);
//             isCurrentLayer = 0;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = true;
//             break;
//         case 9:
//             // set_single_persistent_default_layer(1);
//             layer_on(_QWERTY_US_JIS);
//             isCurrentLayer = 1;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = true;
//             break;
//         case 10:
//             // set_single_persistent_default_layer(2);
//             // isDefaultLayer = 2;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = true;
//             break;
//         case 11:
//             // set_single_persistent_default_layer(3);
//             // isDefaultLayer = 3;
//             keymap_config.swap_lalt_lgui = false;
//             keymap_config.swap_control_capslock = true;
//             break;
//         case 12:
//             // set_single_persistent_default_layer(0);
//             layer_off(_QWERTY_US_JIS);
//             isCurrentLayer = 0;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = true;
//             break;
//         case 13:
//             // set_single_persistent_default_layer(1);
//             layer_on(_QWERTY_US_JIS);
//             isCurrentLayer = 1;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = true;
//             break;
//         case 14:
//             // set_single_persistent_default_layer(2);
//             // isDefaultLayer = 2;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = true;
//             break;
//         case 15:
//             // set_single_persistent_default_layer(3);
//             // isDefaultLayer = 3;
//             keymap_config.swap_lalt_lgui = true;
//             keymap_config.swap_control_capslock = true;
//             break;
//     }
//     return true;
// }
//
// /* OLED Setting */
// static void render_logo(void) {
//     static const char PROGMEM qmk_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//         0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//     };
//     oled_write_P(qmk_logo, false);
// }
// oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
//     return OLED_ROTATION_270;
// }
// bool oled_task_kb(void) {
//     if (!is_keyboard_master()) {
//         render_logo();
//     } else {
//         oled_write_ln_P(PSTR("Current layer is \n"), false);
//         switch (isCurrentLayer) {
//             case 0:
//                 // 現在のレイヤーを表示する
//                 oled_write_ln_P(PSTR("_QWERTY_US_US"), false);
//                 break;
//             case 1:
//                 oled_write_ln_P(PSTR("_QWERTY_US_JIS"), false);
//                 break;
//             // case 2:
//             //     oled_write_ln_P(PSTR("_JIS_US"), false);
//             //     break;
//             // case 3:
//             //     oled_write_ln_P(PSTR("_JIS_JIS"), false);
//             //     break;
//             case 10:
//                 oled_write_ln_P(PSTR("_LOWER_US_US"), false);
//                 break;
//             case 11:
//                 oled_write_ln_P(PSTR("_LOWER_US_JIS"), false);
//                 break;
//             case 20:
//                 oled_write_ln_P(PSTR("_RAISE_US_US"), false);
//                 break;
//             case 21:
//                 oled_write_ln_P(PSTR("_RAISE_US_JIS"), false);
//                 break;
//             case 30:
//                 oled_write_ln_P(PSTR("_ADJUST_US_US"), false);
//                 break;
//             case 31:
//                 oled_write_ln_P(PSTR("_ADJUST_US_JIS"), false);
//                 break;
//         }
//     }
//     return false;
// }
