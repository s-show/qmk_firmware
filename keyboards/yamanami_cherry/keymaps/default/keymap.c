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
// Keycap > US && OS -> JIS の設定
const key_override_t JP_GRV_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_GRV,  JP_TILD, 1 << _QWERTY_US_JIS, MOD_MASK_CAG);
const key_override_t KC_SCLN_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_SCLN, KC_QUOT, 1 << _QWERTY_US_JIS, MOD_MASK_CAG);
const key_override_t JP_QUOT_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_QUOT, JP_DQUO, 1 << _QWERTY_US_JIS, MOD_MASK_CAG);
const key_override_t JP_BSLS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_BSLS, JP_PIPE, 1 << _LOWER_US_JIS, MOD_MASK_CAG);
const key_override_t KC_MINS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_MINS, JP_UNDS, 1 << _LOWER_US_JIS, MOD_MASK_CAG);
const key_override_t JP_EQL_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_EQL,  JP_PLUS, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t JP_LBRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_LBRC, JP_LCBR, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t JP_RBRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_RBRC, JP_RCBR, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t KC_2_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_2,    KC_LBRC, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t KC_6_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_6,    KC_EQL,  1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t KC_7_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_7,    JP_AMPR, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t KC_8_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_8,    JP_ASTR, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t KC_9_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_9,    JP_LPRN, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
const key_override_t KC_0_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_0,    JP_RPRN, 1 << _LOWER_US_JIS,  MOD_MASK_CAG);
// Keycap > JIS && OS -> US の設定
const key_override_t JIS_US_KC_SCLN_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_SCLN, KC_PLUS, 1 << _QWERTY_JIS_US, MOD_MASK_CAG);
const key_override_t JIS_US_KC_COLN_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_COLN, KC_ASTR, 1 << _QWERTY_JIS_US, MOD_MASK_CAG);
const key_override_t JIS_US_KC_AT_key_override   = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_AT,   KC_GRV,  1 << _QWERTY_JIS_US, MOD_MASK_CAG);
const key_override_t JIS_US_KC_MINS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_MINS, KC_EQL,  1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_CIRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_CIRC, KC_TILD, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_BSLS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_BSLS, KC_UNDS, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_JP_YEN_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_YEN,  KC_PIPE, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_2_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_2,    KC_DQUO, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_6_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_6,    KC_AMPR, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_7_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_7,    KC_QUOT, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_8_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_8,    KC_LPRN, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_9_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_9,    KC_RPRN, 1 << _LOWER_JIS_US,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_0_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_0,    KC_NO,   1 << _LOWER_JIS_US,  MOD_MASK_CAG);
// Keycap > JIS && OS -> JIS の設定
const key_override_t JIS_JIS_JP_SLSH_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_SLSH, JP_PIPE, 1 << _LOWER_JIS_JIS, MOD_MASK_CAG);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    // Keycap > US && OS -> JIS の設定
    &JP_GRV_key_override,
    &KC_SCLN_key_override,
    &JP_QUOT_key_override,
    &JP_BSLS_key_override,
    &KC_MINS_key_override,
    &JP_EQL_key_override,
    &JP_LBRC_key_override,
    &JP_RBRC_key_override,
    &KC_2_key_override,
    &KC_6_key_override,
    &KC_7_key_override,
    &KC_8_key_override,
    &KC_9_key_override,
    &KC_0_key_override,
    // Keycap > JIS && OS -> US の設定
    &JIS_US_KC_SCLN_key_override,
    &JIS_US_KC_COLN_key_override,
    &JIS_US_KC_AT_key_override,
    &JIS_US_KC_MINS_key_override,
    &JIS_US_KC_CIRC_key_override,
    &JIS_US_KC_BSLS_key_override,
    &JIS_US_JP_YEN_key_override,
    &JIS_US_KC_2_key_override,
    &JIS_US_KC_6_key_override,
    &JIS_US_KC_7_key_override,
    &JIS_US_KC_8_key_override,
    &JIS_US_KC_9_key_override,
    &JIS_US_KC_0_key_override,
    // Keycap > JIS && OS -> JIS の設定
    &JIS_JIS_JP_SLSH_key_override,
    // NULL // Null terminate the array of overrides!
};
// key override setting end

// tap dance setting start
enum {
    TD_ALT_F4,
};
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT_F4] = ACTION_TAP_DANCE_DOUBLE(KC_NO, LALT(KC_F4))
};
// tap dance setting end

/* keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
    // Keycap is US, OS layout is US.
    [_QWERTY_US_US] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,               KC_T,          KC_Y,    KC_U,             KC_I,    KC_O,    KC_P,    KC_GRV,  \
        KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,               KC_G,          KC_H,    KC_J,             KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,               KC_B,          KC_N,    KC_M,             KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
        WIN_TAB, KC_ESC, KC_LALT, KC_LGUI, MO(_LOWER_US_US),   SFT_T(KC_SPC), KC_BSPC, MO(_RAISE_US_US), KC_RGUI, KC_RALT, KC_RCTL, ALT_TAB \
    ),

    // Keycap is US, OS layout is JIS.
    [_QWERTY_US_JIS] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,               KC_T,          KC_Y,    KC_U,              KC_I,    KC_O,    KC_P,    JP_GRV, \
        KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,               KC_G,          KC_H,    KC_J,              KC_K,    KC_L,    KC_SCLN, JP_QUOT, \
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,               KC_B,          KC_N,    KC_M,              KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
        WIN_TAB, KC_ESC, KC_LALT, KC_LGUI, MO(_LOWER_US_JIS),  SFT_T(KC_SPC), KC_BSPC, MO(_RAISE_US_JIS), KC_RGUI, KC_RALT, KC_RCTL, ALT_TAB \
    ),

    // Keycap is JIS, OS layout is US.
    [_QWERTY_JIS_US] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,               KC_T,          KC_Y,    KC_U,              KC_I,    KC_O,    KC_P,    KC_AT,  \
        KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,               KC_G,          KC_H,    KC_J,              KC_K,    KC_L,    KC_SCLN, KC_COLN, \
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,               KC_B,          KC_N,    KC_M,              KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
        WIN_TAB, KC_ESC, KC_LALT, KC_LGUI, MO(_LOWER_JIS_US),  SFT_T(KC_SPC), KC_BSPC, MO(_RAISE_JIS_US), KC_RGUI, KC_RALT, KC_RCTL, ALT_TAB \
    ),

    // Keycap is JIS, OS layout is JIS.
    [_QWERTY_JIS_JIS] = LAYOUT(
        KC_TAB,  JP_Q,   JP_W,    JP_E,    JP_R,               JP_T,          JP_Y,    JP_U,               JP_I,    JP_O,    JP_P,    JP_AT,  \
        KC_LCTL, JP_A,   JP_S,    JP_D,    JP_F,               JP_G,          JP_H,    JP_J,               JP_K,    JP_L,    JP_SCLN, JP_COLN, \
        KC_LSFT, JP_Z,   JP_X,    JP_C,    JP_V,               JP_B,          JP_N,    JP_M,               JP_COMM, JP_DOT,  JP_SLSH, KC_ENT,  \
        WIN_TAB, KC_ESC, KC_LALT, KC_LGUI, MO(_LOWER_JIS_JIS), SFT_T(KC_SPC), KC_BSPC, MO(_RAISE_JIS_JIS), KC_RGUI, KC_RALT, KC_RCTL, ALT_TAB \
    ),

    // Keycap is US, OS layout is US.
    [_LOWER_US_US] = LAYOUT( \
        KC_LNG5, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,   \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_APP,  KC_LPRN, KC_RPRN, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______ \
        ),

    // Keycap is US, OS layout is JIS.
    [_LOWER_US_JIS] = LAYOUT( \
        JP_ZKHK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_BSLS, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, JP_EQL,  JP_LBRC, JP_RBRC, _______, \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_APP,  JP_LPRN, JP_RPRN, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______ \
        ),

    // Keycap is JIS, OS layout is US.
    [_LOWER_JIS_US] = LAYOUT( \
        KC_LNG5, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_YEN, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_CIRC, KC_LBRC, KC_RBRC, _______,   \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_APP,  KC_LPRN, KC_RPRN, _______, KC_BSLS, \
        _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______ \
        ),

    // Keycap is JIS, OS layout is JIS.
    [_LOWER_JIS_JIS] = LAYOUT( \
        KC_LNG5, JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_SLSH, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   JP_MINS, JP_CIRC, JP_LBRC, JP_RBRC, _______,   \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_APP,  JP_LPRN, JP_RPRN, _______, JP_BSLS, \
        _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______ \
        ),

    // Keycap is US, OS layout is US.
    [_RAISE_US_US] = LAYOUT( \
        KC_AGRV, KC_NO,      KC_PGUP,    KC_ESC,     KC_NO,     KC_TAB, KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO,   \
        _______, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,     KC_NO,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,   \
        _______, A(KC_HOME), C(KC_PGDN), C(KC_PGUP), C(KC_END), KC_NO,  KC_NO,   KC_NO,   _______, _______, _______, _______, \
        _______, _______,    _______,    _______,    _______,   KC_ENT, _______, _______, _______, _______, _______, _______ \
        ),

    // Keycap is US, OS layout is JIS.
    [_RAISE_US_JIS] = LAYOUT( \
        KC_AGRV, KC_NO,      KC_PGUP,    KC_ESC,     KC_NO,     KC_TAB, KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO, \
        _______, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,     KC_NO,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO, \
        _______, A(KC_HOME), C(KC_PGDN), C(KC_PGUP), C(KC_END), KC_NO,  KC_NO,   KC_NO,   _______, _______, _______, _______, \
        _______, _______,    _______,    _______,    _______,   KC_ENT, _______, _______, _______, _______, _______, _______ \
        ),

    // Keycap is JIS, OS layout is US.
    [_RAISE_JIS_US] = LAYOUT( \
        KC_AGRV, KC_NO,      KC_PGUP,    KC_ESC,     KC_NO,     KC_TAB, KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO,   \
        _______, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,     KC_NO,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,   \
        _______, A(KC_HOME), C(KC_PGDN), C(KC_PGUP), C(KC_END), KC_NO,  KC_NO,   KC_NO,   _______, _______, _______, _______, \
        _______, _______,    _______,    _______,    _______,   KC_ENT, _______, _______, _______, _______, _______, _______ \
        ),

    // Keycap is JIS, OS layout is JIS.
    [_RAISE_JIS_JIS] = LAYOUT( \
        KC_AGRV, KC_NO,      KC_PGUP,    KC_ESC,     KC_NO,     KC_TAB, KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO, \
        _______, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,     KC_NO,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO, \
        _______, A(KC_HOME), C(KC_PGDN), C(KC_PGUP), C(KC_END), KC_NO,  KC_NO,   KC_NO,   _______, _______, _______, _______, \
        _______, _______,    _______,    _______,    _______,   KC_ENT, _______, _______, _______, _______, _______, _______ \
        ),

    // Keycap is US, OS layout is US.
    [_ADJUST_US_US] =  LAYOUT( \
        QK_BOOT, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,        KC_PERC,   KC_CIRC,    KC_AMPR,    KC_ASTR,  KC_LPRN,    KC_RPRN,  KC_NO, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   TD(TD_ALT_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO,\
        _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,         KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        ),

    // Keycap is US, OS layout is JIS.
    [_ADJUST_US_JIS] =  LAYOUT( \
        QK_BOOT, JP_EXLM,  JP_AT,   JP_HASH, JP_DLR,        JP_PERC,   JP_CIRC,    JP_AMPR,    JP_ASTR,  JP_LPRN,    JP_RPRN,  KC_NO, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   TD(TD_ALT_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO, \
        _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,         KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        ),

    // Keycap is JIS, OS layout is US.
    [_ADJUST_JIS_US] =  LAYOUT( \
        QK_BOOT, KC_EXLM,  KC_DQUO, KC_HASH, KC_DLR,        KC_PERC,   KC_AMPR,    KC_QUOT,    KC_LPRN,  KC_RPRN,    KC_EQL,   KC_TILD, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   TD(TD_ALT_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO,\
        _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,         KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        ),

    // Keycap is JIS, OS layout is JIS.
    [_ADJUST_JIS_JIS] =  LAYOUT( \
        QK_BOOT, JP_EXLM,  JP_DQUO, JP_HASH, JP_DLR,        JP_PERC,   JP_AMPR,    JP_QUOT,    JP_LPRN,  JP_RPRN,    JP_EQL,   JP_TILD, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   TD(TD_ALT_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO, \
        _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,         KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
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
    state = update_tri_layer_state(state, _LOWER_JIS_US, _RAISE_JIS_US, _ADJUST_JIS_US);
    state = update_tri_layer_state(state, _LOWER_JIS_JIS, _RAISE_JIS_JIS, _ADJUST_JIS_JIS);
    switch (get_highest_layer(state)) {
        case _QWERTY_US_JIS:
            isCurrentLayer = 1;
            break;
        case _QWERTY_JIS_US:
            isCurrentLayer = 2;
            break;
        case _QWERTY_JIS_JIS:
            isCurrentLayer = 3;
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
    #ifdef CONSOLE_ENABLE
        uprintf("switch state: %lu\n", state);
    #endif

    switch (state) {
        // keycap is US, OS layout is US.
        case 0:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 1:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        // keycap is JIS, OS layout is US.
        case 2:
            set_single_persistent_default_layer(2);
            isDefaultLayer = 2;
            isCurrentLayer = 2;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        // keycap is JIS, OS layout is JIS.
        case 3:
            set_single_persistent_default_layer(3);
            isDefaultLayer = 3;
            isCurrentLayer = 3;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        // keycap is US, OS layout is US.
        case 4:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 5:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            key_override_on();
            break;
        // keycap is JIS, OS layout is US.
        case 6:
            set_single_persistent_default_layer(2);
            isDefaultLayer = 2;
            isCurrentLayer = 2;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            break;
        // keycap is JIS, OS layout is JIS.
        case 7:
            set_single_persistent_default_layer(3);
            isDefaultLayer = 3;
            isCurrentLayer = 3;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = false;
            break;
        // keycap is US, OS layout is US.
        case 8:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 9:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            key_override_on();
            break;
        // keycap is JIS, OS layout is US.
        case 10:
            set_single_persistent_default_layer(2);
            isDefaultLayer = 2;
            isCurrentLayer = 2;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            break;
        // keycap is JIS, OS layout is JIS.
        case 11:
            set_single_persistent_default_layer(3);
            isDefaultLayer = 3;
            isCurrentLayer = 3;
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_control_capslock = true;
            break;
        // keycap is US, OS layout is US.
        case 12:
            set_single_persistent_default_layer(0);
            isDefaultLayer = 0;
            isCurrentLayer = 0;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            key_override_off();
            break;
        // keycap is US, OS layout is JIS.
        case 13:
            set_single_persistent_default_layer(1);
            isDefaultLayer = 1;
            isCurrentLayer = 1;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            key_override_on();
            break;
        // keycap is JIS, OS layout is US.
        case 14:
            set_single_persistent_default_layer(2);
            isDefaultLayer = 2;
            isCurrentLayer = 2;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            break;
        // keycap is JIS, OS layout is JIS.
        case 15:
            set_single_persistent_default_layer(3);
            isDefaultLayer = 3;
            isCurrentLayer = 3;
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_control_capslock = true;
            break;
    }
    return true;
}

/* OLED Setting */
static void render_logo(void) {
    static const unsigned char PROGMEM raw_logo[] = {
        // 'logo_and_text', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x02, 0x03, 0x02, 0x0c, 0x30,
        0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x1c, 0x70, 0xc0, 0x00, 0xc0, 0x70, 0x1c, 0x00, 0x00, 0x40, 0x40, 0x40,
        0x40, 0x40, 0x40, 0xc0, 0x00, 0x00, 0xe0, 0x80, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0x00,
        0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x00, 0x00, 0xe0, 0x80, 0x40, 0x40, 0x40, 0xc0,
        0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x00, 0x00, 0xe0, 0x80, 0x40, 0x40, 0xc0,
        0x40, 0x40, 0x40, 0xc0, 0x00, 0x00, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x06, 0x0c, 0x30, 0xc0,
        0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42,
        0x42, 0x42, 0x42, 0x3f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00,
        0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x7f,
        0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f,
        0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x03, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x0c, 0xb0, 0xce, 0xe1, 0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x60, 0x80, 0x00, 0x00, 0x00, 0x80, 0x60, 0x00, 0x00,
        0x00, 0xfc, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0x20, 0x20,
        0xc0, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xe0, 0x00, 0x00, 0x00, 0xe0,
        0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0xfc, 0x00, 0x00, 0x00,
        0x40, 0x60, 0x70, 0x78, 0x76, 0x71, 0x78, 0x7c, 0x7e, 0x7f, 0x7f, 0x7f, 0x7e, 0x7c, 0x78, 0x7c,
        0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
        0x7e, 0x7c, 0x7e, 0x7f, 0x7f, 0x7f, 0x7e, 0x7c, 0x78, 0x73, 0x7c, 0x78, 0x70, 0x60, 0x40, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x1f, 0x24, 0x24,
        0x24, 0x24, 0x24, 0x24, 0x13, 0x00, 0x00, 0x00, 0x41, 0x46, 0x78, 0x06, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x3f, 0x10, 0x20, 0x20, 0x20, 0x10, 0x0f, 0x00, 0x00, 0x07, 0x18, 0x20, 0x20, 0x20, 0x20,
        0x18, 0x07, 0x00, 0x00, 0x00, 0x1e, 0x21, 0x21, 0x21, 0x21, 0x21, 0x1f, 0x00, 0x00, 0x00, 0x3f,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x20, 0x20, 0x20, 0x10, 0x3f, 0x00, 0x00, 0x00
    };
    oled_write_raw_P((const char *)raw_logo, sizeof(raw_logo));
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
    // keymap_config.raw = eeconfig_read_keymap();
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
            case 2:
                oled_clear();
                oled_write_ln_P(
                    PSTR("Default layer\n- Keycap: JIS\n- OS Layout: US"),
                    false
                );
                break;
            case 3:
                oled_clear();
                oled_write_ln_P(
                    PSTR("Default layer\n- Keycap: JIS\n- OS Layout: JIS"),
                    false
                );
                break;
        }
        if (keymap_config.swap_lalt_lgui && keymap_config.swap_control_capslock) {
            oled_write_ln_P(
                PSTR("Alt<->Win ctrl<->caps"),
                false
            );
        } else if (keymap_config.swap_lalt_lgui && !keymap_config.swap_control_capslock) {
            oled_write_ln_P(
                PSTR("Alt<->Win"),
                false
            );
        } else if (!keymap_config.swap_lalt_lgui && keymap_config.swap_control_capslock) {
            oled_write_ln_P(
                PSTR("ctrl<->caps"),
                false
            );
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
