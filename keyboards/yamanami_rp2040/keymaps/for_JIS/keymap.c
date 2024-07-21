/* Copyright 2021 s-show
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

/**
 * Cool Function where a single key does ALT+TAB
 * From: https://beta.docs.qmk.fm/features/feature_macros#super-alt-tab
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/dz60/keymaps/_bonfire/not-in-use/super-alt-tab.c
 */
bool     is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.

// Defines names for use in layer keycodes and the keymap
enum layer_number { _QWERTY = 0, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    ALT_TAB,
    SFT_SPC,
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
    // JK_IME_ON,
    // DF_IME_OFF,
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
// const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
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
    // [JK_IME_ON] = COMBO_ACTION(jk_combo),
    // [DF_IME_OFF] = COMBO_ACTION(df_combo),
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
        /* case JK_IME_ON:
          if (pressed) {
            tap_code16(KC_LNG1);
          }
          break;
        case DF_IME_OFF:
          if (pressed) {
            tap_code16(KC_LNG2);
          }
          break; */
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
const key_override_t **key_overrides = (const key_override_t *[]){
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
    NULL // Null terminate the array of overrides!
};
// key override setting end

/* keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,  KC_T,    KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    JP_GRV, \
        KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,  KC_G,    KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, JP_QUOT, \
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,  KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
        ALT_TAB, KC_ESC, KC_LALT, KC_LGUI, LOWER, SFT_SPC, KC_BSPC, RAISE, KC_RGUI, KC_RALT, KC_RCTL, ALT_TAB \
    ),
    [_LOWER] = LAYOUT(
        JP_ZKHK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    JP_BSLS, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_MINS, JP_EQL,  JP_LBRC, JP_RBRC, _______, \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_APP,  JP_LPRN, JP_RPRN, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_DEL, _______, _______, _______, _______, _______ \
    ),
    [_RAISE] = LAYOUT(
        KC_AGRV, KC_NO,      KC_PGUP,    KC_ESC,     KC_NO,     KC_TAB, KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO, \
        _______, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,     KC_NO,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO, \
        _______, A(KC_HOME), C(KC_PGDN), C(KC_PGUP), C(KC_END), KC_NO,  KC_NO,   KC_NO,   _______, _______, _______, _______, \
        _______, _______,    _______,    _______,    _______,   KC_ENT, _______, _______, _______, _______, _______, _______ \
    ),
    [_ADJUST] = LAYOUT(
        QK_BOOT, JP_EXLM,  JP_AT,   JP_HASH, JP_DLR,   JP_PERC,   JP_CIRC,    JP_AMPR,    JP_ASTR,  JP_LPRN,    JP_RPRN,  KC_NO, \
        DB_TOGG, KC_ASPC,  KC_NO,   KC_NO,   A(KC_F4), G(KC_TAB), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), KC_APSCR, KC_NO, \
        _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,      _______,  _______,    _______,  _______, \
        KC_CAD,  KC_CSESC, _______, _______, _______,  _______,   _______,    _______,    _______,  _______,    _______,  _______ \
    ),
};

static uint16_t lower_pressed_time    = 0;
static uint16_t raise_pressed_time    = 0;
static uint16_t sft_spc_pressed_time  = 0;
static _Bool shift_keys_pressed_flag          = false;
static _Bool sft_spc_pressed_flag             = false;
static _Bool sft_spc_to_any_keys_pressed_flag = false;
static _Bool lower_pressed_flag               = false;
static _Bool lower_to_any_keys_pressed_flag   = false;
static _Bool raise_pressed_flag               = false;
static _Bool raise_to_any_keys_pressed_flag   = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                lower_pressed_flag = true;
                lower_pressed_time = record->event.time;
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                lower_pressed_flag = false;
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                if (lower_to_any_keys_pressed_flag) {
                    lower_to_any_keys_pressed_flag = false;
                } else {
                    if (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM) {
                        tap_code(KC_LNG2);
                    }
                }
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                raise_pressed_flag = true;
                raise_pressed_time = record->event.time;
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                raise_pressed_flag = false;
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                if (raise_to_any_keys_pressed_flag) {
                    raise_to_any_keys_pressed_flag = false;
                } else {
                    if (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM) {
                        tap_code(KC_LNG1);
                    }
                }
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        case SFT_SPC:
            if (record->event.pressed) {
                sft_spc_pressed_flag = true;
                sft_spc_pressed_time = record->event.time;
                if (shift_keys_pressed_flag) {
                    register_code(KC_SPC);
                } else {
                    register_code(KC_LSFT);
                }
            } else {
                sft_spc_pressed_flag = false;
                if (shift_keys_pressed_flag) {
                    unregister_code(KC_SPC);
                } else {
                    unregister_code(KC_LSFT);
                    if (sft_spc_to_any_keys_pressed_flag) {
                        sft_spc_to_any_keys_pressed_flag = false;
                    } else {
                        if (TIMER_DIFF_16(record->event.time, sft_spc_pressed_time) < TAPPING_TERM) {
                            if (is_alt_tab_active) {
                                unregister_code(KC_LALT);
                                tap_code(KC_SPC);
                            } else {
                                tap_code(KC_SPC);
                            }
                        }
                    }
                }
            }
            return false;
            break;
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
        case KC_RIGHT:
        case KC_LEFT:
        case KC_DOWN:
        case KC_UP:
        case KC_TAB:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                    alt_tab_timer = timer_read();
                }
                if (sft_spc_pressed_flag) {
                    sft_spc_to_any_keys_pressed_flag = true;
                } else {
                    sft_spc_to_any_keys_pressed_flag = false;
                }
                if (lower_pressed_flag) {
                    lower_to_any_keys_pressed_flag = true;
                } else {
                    lower_to_any_keys_pressed_flag = false;
                }
                if (raise_pressed_flag) {
                    raise_to_any_keys_pressed_flag = true;
                } else {
                    raise_to_any_keys_pressed_flag = false;
                }
            }
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
                if (sft_spc_pressed_flag) {
                    sft_spc_to_any_keys_pressed_flag = true;
                } else {
                    sft_spc_to_any_keys_pressed_flag = false;
                }
                if (lower_pressed_flag) {
                    lower_to_any_keys_pressed_flag = true;
                } else {
                    lower_to_any_keys_pressed_flag = false;
                }
                if (raise_pressed_flag) {
                    raise_to_any_keys_pressed_flag = true;
                } else {
                    raise_to_any_keys_pressed_flag = false;
                }
            } else {
                if (is_alt_tab_active) {
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
                if (sft_spc_pressed_flag) {
                    sft_spc_to_any_keys_pressed_flag = true;
                } else {
                    sft_spc_to_any_keys_pressed_flag = false;
                }
                if (lower_pressed_flag) {
                    lower_to_any_keys_pressed_flag = true;
                } else {
                    lower_to_any_keys_pressed_flag = false;
                }
                if (raise_pressed_flag) {
                    raise_to_any_keys_pressed_flag = true;
                } else {
                    raise_to_any_keys_pressed_flag = false;
                }
            } else {
                if (is_alt_tab_active) {
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
                if (sft_spc_pressed_flag) {
                    sft_spc_to_any_keys_pressed_flag = true;
                } else {
                    sft_spc_to_any_keys_pressed_flag = false;
                }
                if (lower_pressed_flag) {
                    lower_to_any_keys_pressed_flag = true;
                } else {
                    lower_to_any_keys_pressed_flag = false;
                }
                if (raise_pressed_flag) {
                    raise_to_any_keys_pressed_flag = true;
                } else {
                    raise_to_any_keys_pressed_flag = false;
                }
            } else {
                if (is_alt_tab_active) {
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
                    register_code(KC_RIGHT);
                    return false;
                    break;
                }
                if (sft_spc_pressed_flag) {
                    sft_spc_to_any_keys_pressed_flag = true;
                } else {
                    sft_spc_to_any_keys_pressed_flag = false;
                }
                if (lower_pressed_flag) {
                    lower_to_any_keys_pressed_flag = true;
                } else {
                    lower_to_any_keys_pressed_flag = false;
                }
                if (raise_pressed_flag) {
                    raise_to_any_keys_pressed_flag = true;
                } else {
                    raise_to_any_keys_pressed_flag = false;
                }
            } else {
                if (is_alt_tab_active) {
                    unregister_code(KC_RIGHT);
                    return false;
                    break;
                }
            }
            return true;
            break;
        case KC_LSFT:
        case KC_RSFT:
            if (record->event.pressed) {
                shift_keys_pressed_flag = true;
            } else {
                shift_keys_pressed_flag = false;
            }
        default:
            if (record->event.pressed) {
                if (sft_spc_pressed_flag) {
                    sft_spc_to_any_keys_pressed_flag = true;
                } else {
                    sft_spc_to_any_keys_pressed_flag = false;
                }
                if (lower_pressed_flag) {
                    lower_to_any_keys_pressed_flag = true;
                } else {
                    lower_to_any_keys_pressed_flag = false;
                }
                if (raise_pressed_flag) {
                    raise_to_any_keys_pressed_flag = true;
                } else {
                    raise_to_any_keys_pressed_flag = false;
                }
            } else {
            }
            if (is_alt_tab_active) {
                unregister_code(KC_LALT);
                is_alt_tab_active = false;
            }
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

// The very important timer.
void matrix_scan_user(void) {
    if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 1000) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
}
