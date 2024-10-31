// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

/**
 * Cool Function where a single key does ALT+TAB
 * From: https://beta.docs.qmk.fm/features/feature_macros#super-alt-tab
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/dz60/keymaps/_bonfire/not-in-use/super-alt-tab.c
 */
bool     is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
bool     is_win_tab_active = false; // ADD this near the begining of keymap.c
uint16_t win_tab_timer     = 0;     // we will be using them soon.

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY_US_US = 0, // keycap is US, OS keyboard layout is US.
    _QWERTY_US_JIS, // keycap is US, OS keyboard layout is JIS.
    _LOWER_US_US,
    _LOWER_US_JIS,
    _RAISE_US_US,
    _RAISE_US_JIS,
    _ADJUST_US_US,
    _ADJUST_US_JIS,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    ALT_TAB,
    WIN_TAB,
};

// alias other keycode
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)
#define KC_AGRV LALT(KC_GRV)
#define KC_ASPC LALT(KC_SPACE)
#define KC_CSESC LCTL(LSFT(KC_ESC))

// combo setting start
enum combo_events {
    SDF_ALT_SPACE,
    JK_IME_ON,
    DF_IME_OFF,
    DOTSLSH_ALT,
    ZX_ALT,
    MCOMM_WIN,
    CV_WIN,
    SD_CTRL,
    KL_CTRL,
    XC_SALT,
    COMMDOT_SALT,
};

const uint16_t PROGMEM sdf_combo[] = {KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM dotslsh_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM zx_combo[]      = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM mcomm_combo[]   = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM cv_combo[]      = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM sd_combo[]      = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM kl_combo[]      = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM xc_combo[]      = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM commdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    [SDF_ALT_SPACE] = COMBO_ACTION(sdf_combo),
    [JK_IME_ON] = COMBO_ACTION(jk_combo),
    [DF_IME_OFF] = COMBO_ACTION(df_combo),
    [DOTSLSH_ALT]  = COMBO(dotslsh_combo, KC_LALT),
    [ZX_ALT]       = COMBO(zx_combo, KC_LALT),
    [MCOMM_WIN]    = COMBO(mcomm_combo, KC_LWIN),
    [CV_WIN]       = COMBO(cv_combo, KC_LWIN),
    [SD_CTRL]      = COMBO(sd_combo, KC_LCTL),
    [KL_CTRL]      = COMBO(kl_combo, KC_LCTL),
    [XC_SALT]      = COMBO_ACTION(xc_combo),
    [COMMDOT_SALT] = COMBO_ACTION(commdot_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case SDF_ALT_SPACE:
            if (pressed) {
                tap_code16(LALT(KC_SPACE));
            }
            break;
        case JK_IME_ON:
          if (pressed) {
            tap_code16(KC_LNG1);
          }
          break;
        case DF_IME_OFF:
          if (pressed) {
            tap_code16(KC_LNG2);
          }
          break;
        case XC_SALT:
            if (pressed) {
                register_code(KC_LSFT);
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
            }
            break;
        case COMMDOT_SALT:
            if (pressed) {
                register_code(KC_LSFT);
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
            }
            break;
    }
}
// combo setting end

// key override setting start
// 全てのレイヤーでキーオーバーライドを有効化
// Ctrl, Win, Altキーを押していたらキーオーバーライドを発動しない
// JP_* を使わなくても実装可能だが、キーマップの読みやすさを優先して使っている。
const key_override_t JP_GRV_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_GRV, S(KC_EQL), ~0, MOD_MASK_CAG);
const key_override_t KC_SCLN_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_SCLN, KC_QUOT, ~0, MOD_MASK_CAG);
const key_override_t JP_QUOT_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_QUOT, S(KC_2), ~0, MOD_MASK_CAG);
const key_override_t KC_2_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_2, KC_LBRC, ~0, MOD_MASK_CAG);
const key_override_t KC_6_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_6, KC_EQL, ~0, MOD_MASK_CAG);
const key_override_t KC_7_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_7, S(KC_6), ~0, MOD_MASK_CAG);
const key_override_t KC_8_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_8, S(KC_QUOT), ~0, MOD_MASK_CAG);
const key_override_t KC_9_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_9, S(KC_8), ~0, MOD_MASK_CAG);
const key_override_t KC_0_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_0, S(KC_9), ~0, MOD_MASK_CAG);
const key_override_t JP_BSLS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_BSLS, S(KC_INT3), ~0, MOD_MASK_CAG);
const key_override_t KC_MINS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_MINS, S(KC_INT1), ~0, MOD_MASK_CAG);
const key_override_t JP_EQL_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_EQL, S(KC_SCLN), ~0, MOD_MASK_CAG);
const key_override_t JP_LBRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_LBRC, S(KC_RBRC), ~0, MOD_MASK_CAG);
const key_override_t JP_RBRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_RBRC, S(KC_NUHS), ~0, MOD_MASK_CAG);

// This globally defines all key overrides to be used
// const key_override_t *key_overrides[] = (const key_override_t *[]){
const key_override_t *key_overrides[] = {
    &JP_GRV_key_override,
    &KC_SCLN_key_override,
    &JP_QUOT_key_override,
    &KC_2_key_override,
    &KC_6_key_override,
    &KC_7_key_override,
    &KC_8_key_override,
    &KC_9_key_override,
    &KC_0_key_override,
    &JP_BSLS_key_override,
    &KC_MINS_key_override,
    &JP_EQL_key_override,
    &JP_LBRC_key_override,
    &JP_RBRC_key_override,
    // NULL // Null terminate the array of overrides!
};
// key override setting end

/* keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
    // Keycap is US, OS layout is US.
    [_QWERTY_US_US] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,             KC_T,          KC_Y,    KC_U,             KC_I,    KC_O,    KC_P,    KC_GRV,  \
        KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,             KC_G,          KC_H,    KC_J,             KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,             KC_B,          KC_N,    KC_M,             KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
        WIN_TAB, KC_ESC, KC_LALT, KC_LGUI, MO(_LOWER_US_US), SFT_T(KC_SPC), KC_BSPC, MO(_RAISE_US_US), KC_RGUI, KC_RALT, KC_RCTL, ALT_TAB \
    ),

    // Keycap is US, OS layout is JIS.
    [_QWERTY_US_JIS] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,              KC_T,          KC_Y,    KC_U,              KC_I,    KC_O,    KC_P,    JP_GRV, \
        KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,              KC_G,          KC_H,    KC_J,              KC_K,    KC_L,    KC_SCLN, JP_QUOT, \
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,              KC_B,          KC_N,    KC_M,              KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
        WIN_TAB, KC_ESC, KC_LALT, KC_LGUI, MO(_LOWER_US_JIS), SFT_T(KC_SPC), KC_BSPC, MO(_RAISE_US_JIS), KC_RGUI, KC_RALT, KC_RCTL, ALT_TAB \
    ),

    // For OS layout is US.
    [_LOWER_US_US] = LAYOUT( \
        KC_LNG5, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,   \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_APP,  KC_LPRN, KC_RPRN, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_DEL, _______, _______, _______, _______, _______ \
        ),

    // For OS layout is JIS.
    [_LOWER_US_JIS] = LAYOUT( \
        JP_ZKHK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    JP_BSLS, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_MINS, JP_EQL,  JP_LBRC, JP_RBRC, _______, \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_APP,  JP_LPRN, JP_RPRN, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_DEL, _______, _______, _______, _______, _______ \
        ),

    [_RAISE_US_US] = LAYOUT( \
        KC_AGRV, KC_NO,      KC_PGUP,    KC_ESC,     KC_NO,     KC_TAB, KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO,   \
        _______, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,     KC_NO,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,   \
        _______, A(KC_HOME), C(KC_PGDN), C(KC_PGUP), C(KC_END), KC_NO,  KC_NO,   KC_NO,   _______, _______, _______, _______, \
        _______, _______,    _______,    _______,    _______,   KC_ENT, _______, _______, _______, _______, _______, _______ \
        ),

    [_RAISE_US_JIS] = LAYOUT( \
        KC_AGRV, KC_NO,      KC_PGUP,    KC_ESC,     KC_NO,     KC_TAB, KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO, \
        _______, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,     KC_NO,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO, \
        _______, A(KC_HOME), C(KC_PGDN), C(KC_PGUP), C(KC_END), KC_NO,  KC_NO,   KC_NO,   _______, _______, _______, _______, \
        _______, _______,    _______,    _______,    _______,   KC_ENT, _______, _______, _______, _______, _______, _______ \
        ),

    [_ADJUST_US_US] =  LAYOUT( \
        QK_BOOT, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,   KC_PERC,   KC_CIRC,    KC_AMPR,    KC_ASTR,  KC_LPRN,    KC_RPRN,  KC_NO, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   A(KC_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO,\
        _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,  _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        ),

    [_ADJUST_US_JIS] =  LAYOUT( \
        QK_BOOT, JP_EXLM,  JP_AT,   JP_HASH, JP_DLR,   JP_PERC,   JP_CIRC,    JP_AMPR,    JP_ASTR,  JP_LPRN,    JP_RPRN,  KC_NO, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   A(KC_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO, \
        _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,  _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

/* Layer setting */
int isCurrentLayer = 0;
int isDefaultLayer = 0;
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER_US_US, _RAISE_US_US, _ADJUST_US_US);
    state = update_tri_layer_state(state, _LOWER_US_JIS, _RAISE_US_JIS, _ADJUST_US_JIS);
    switch (get_highest_layer(state)) {
    case _QWERTY_US_JIS:
        isCurrentLayer = 1;
        break;
    case _LOWER_US_US:
        isCurrentLayer = 10;
        break;
    case _LOWER_US_JIS:
        isCurrentLayer = 11;
        break;
    case _RAISE_US_US:
        isCurrentLayer = 20;
        break;
    case _RAISE_US_JIS:
        isCurrentLayer = 21;
        break;
    case _ADJUST_US_US:
        isCurrentLayer = 30;
        break;
    case _ADJUST_US_JIS:
        isCurrentLayer = 31;
        break;
    default:
        if (isDefaultLayer == 0) {
            isCurrentLayer = 0;
        } else {
            isCurrentLayer = 1;
        }
        break;
    }
    return state;
}

/* DIP Switch Setting */
bool dip_switch_update_mask_user(uint32_t state) {
    keymap_config.raw = eeconfig_read_keymap();
    switch (state) {
        case 0:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            key_override_off();
            break;
        case 1:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        case 2:
            // set_single_persistent_default_layer(2);
            // isDefaultLayer = 2;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            break;
        case 3:
            // set_single_persistent_default_layer(3);
            // isDefaultLayer = 3;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            break;
        case 4:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            key_override_off();
            break;
        case 5:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        case 6:
            // set_single_persistent_default_layer(2);
            // isDefaultLayer = 2;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            break;
        case 7:
            // set_single_persistent_default_layer(3);
            // isDefaultLayer = 3;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            break;
        case 8:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            key_override_off();
            break;
        case 9:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            key_override_on();
            break;
        case 10:
            // set_single_persistent_default_layer(2);
            // isDefaultLayer = 2;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            break;
        case 11:
            // set_single_persistent_default_layer(3);
            // isDefaultLayer = 3;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            break;
        case 12:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            key_override_off();
            break;
        case 13:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            key_override_on();
            break;
        case 14:
            // set_single_persistent_default_layer(2);
            // isDefaultLayer = 2;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            break;
        case 15:
            // set_single_persistent_default_layer(3);
            // isDefaultLayer = 3;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            break;
    }
    return true;
}

/* OLED Setting */
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_clear();
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_0;
    }
}
bool oled_task_user(void) {
    if (!is_keyboard_left()) {
        render_logo();
    } else {
        switch (isCurrentLayer) {
            case 0:
                // 現在のレイヤーを表示する
                oled_clear();
                oled_write_ln_P(
                    PSTR("Default layer\n- Keycap: US\n- OS Layout: US"),
                    false
                );
                break;
            case 1:
                oled_clear();
                oled_write_ln_P(
                    PSTR("Default layer\n- Keycap: US\n- OS Layout: JIS"),
                    false
                );
                break;
            // case 2:
            //     oled_write_ln_P(PSTR("_JIS_US"), false);
            //     break;
            // case 3:
            //     oled_write_ln_P(PSTR("_JIS_JIS"), false);
            //     break;
            case 10:
                oled_clear();
                oled_write_ln_P(
                    PSTR("LOWER layer\n- Keycap: US\n- OS Layout: US"),
                    false
                );
                break;
            case 11:
                oled_clear();
                oled_write_ln_P(
                    PSTR("LOWER layer\n- Keycap: US\n- OS Layout: JIS"),
                    false
                );
                break;
            case 20:
                oled_clear();
                oled_write_ln_P(
                    PSTR("RAISE layer\n- Keycap: US\n- OS Layout: US"),
                    false
                );
                break;
            case 21:
                oled_clear();
                oled_write_ln_P(
                    PSTR("RAISE layer\n- Keycap: US\n- OS Layout: JIS"),
                    false
                );
                break;
            case 30:
                oled_clear();
                oled_write_ln_P(
                    PSTR("ADJUST layer\n- Keycap: US\n- OS Layout: US"),
                    false
                );
                break;
            case 31:
                oled_clear();
                oled_write_ln_P(
                    PSTR("ADJUST layer\n- Keycap: US\n- OS Layout: JIS"),
                    false
                );
                break;
        }
    }
    return false;
}

// The very important timer for ALT-TAB key.
void matrix_scan_user(void) {
    if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 1000) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
    if (is_win_tab_active && timer_elapsed(win_tab_timer) > 1000) {
        is_win_tab_active = false;
    }
}
