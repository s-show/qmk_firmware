// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "combos.h"

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
