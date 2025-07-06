// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include "layers.h"
#include "keycodes.h"
#include "features/combos.h"
#include "features/overrides.h"
#include "features/tap_dance.h"
#include "display/oled.h"
#include "features/alt_tab.h"
#include "features/dip_switch.h"

// Layer state variables
enum layer_number isCurrentLayer;
enum layer_number isDefaultLayer;

// alias other keycode
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)
#define KC_AGRV LALT(KC_GRV)
#define KC_ASPC LALT(KC_SPACE)
#define KC_CSESC LCTL(LSFT(KC_ESC))

// Combo array - must be in keymap.c for QMK to access
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

// Tap dance array - must be in keymap.c for QMK to access
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT_F4] = ACTION_TAP_DANCE_DOUBLE(KC_NO, LALT(KC_F4)),
    [TD_SC_CL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN))
};

// Key overrides array - must be in keymap.c for QMK to access
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
    NULL // Null terminate the array of overrides!
};

/* keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
    // Keycap is US, OS layout is US.
    [_QWERTY_US_US] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,               KC_T,          KC_Y,    KC_U,             KC_I,    KC_O,    KC_P,    KC_GRV,  \
        KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,               KC_G,          KC_H,    KC_J,             KC_K,    KC_L,    TD(TD_SC_CL), KC_QUOT, \
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
        DB_TOGG, KC_NO,    PDF(1),  PDF(2), PDF(3),         KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        ),

    // Keycap is US, OS layout is JIS.
    [_ADJUST_US_JIS] =  LAYOUT( \
        QK_BOOT, JP_EXLM,  JP_AT,   JP_HASH, JP_DLR,        JP_PERC,   JP_CIRC,    JP_AMPR,    JP_ASTR,  JP_LPRN,    JP_RPRN,  KC_NO, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   TD(TD_ALT_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO, \
        DB_TOGG, PDF(0),   KC_NO,   PDF(2),  PDF(3),        KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        ),

    // Keycap is JIS, OS layout is US.
    [_ADJUST_JIS_US] =  LAYOUT( \
        QK_BOOT, KC_EXLM,  KC_DQUO, KC_HASH, KC_DLR,        KC_PERC,   KC_AMPR,    KC_QUOT,    KC_LPRN,  KC_RPRN,    KC_EQL,   KC_TILD, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   TD(TD_ALT_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO,\
        DB_TOGG, PDF(0),   PDF(1),  KC_NO,   PDF(3),        KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        ),

    // Keycap is JIS, OS layout is JIS.
    [_ADJUST_JIS_JIS] =  LAYOUT( \
        QK_BOOT, JP_EXLM,  JP_DQUO, JP_HASH, JP_DLR,        JP_PERC,   JP_AMPR,    JP_QUOT,    JP_LPRN,  JP_RPRN,    JP_EQL,   JP_TILD, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   TD(TD_ALT_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO, \
        DB_TOGG , PDF(0),   PDF(1),  PDF(2),  KC_NO,         KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,       _______,   _______,    _______,    _______,  _______,    _______,  QK_BOOT \
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // ALT+TAB and WIN+TAB functionality
    if (!process_alt_tab(keycode, record)) {
        return false;
    }

    return true;
}

/* Layer setting */
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER_US_US, _RAISE_US_US, _ADJUST_US_US);
    state = update_tri_layer_state(state, _LOWER_US_JIS, _RAISE_US_JIS, _ADJUST_US_JIS);
    state = update_tri_layer_state(state, _LOWER_JIS_US, _RAISE_JIS_US, _ADJUST_JIS_US);
    state = update_tri_layer_state(state, _LOWER_JIS_JIS, _RAISE_JIS_JIS, _ADJUST_JIS_JIS);

    if (get_highest_layer(state) == 0) {
        if (isDefaultLayer == 0) {
            isCurrentLayer = _QWERTY_US_US;
        } else if (isDefaultLayer == 1) {
            isCurrentLayer = _QWERTY_US_JIS;
        } else if (isDefaultLayer == 2) {
            isCurrentLayer = _QWERTY_JIS_US;
        } else {
            isCurrentLayer = _QWERTY_JIS_JIS;
        }
    } else {
        isCurrentLayer = get_highest_layer(state);
    }
    return state;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    isDefaultLayer = get_highest_layer(state);
    return state;
}

// The very important timer for ALT-TAB key.
void matrix_scan_user(void) {
    alt_tab_matrix_scan();
}
