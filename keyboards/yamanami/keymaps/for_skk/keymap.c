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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MOUSE,
  IMEON,
  IMEOFF
};


// alias for custom_keycode
#define KC_IMEON  IMEON
#define KC_IMEOFF IMEOFF


// alias other keycode
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)
#define KC_AGRV LALT(KC_GRV)


// combo setting start
enum combo_events {
  SDF_ALT_SPACE,
  JKL_WIN_SPACE
};

const uint16_t PROGMEM sdf_combo[] = {KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jkl_combo[] = {KC_J, KC_K, KC_L, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [SDF_ALT_SPACE] = COMBO_ACTION(sdf_combo),
  [JKL_WIN_SPACE] = COMBO_ACTION(jkl_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SDF_ALT_SPACE:
      if (pressed) {
        tap_code16(LALT(KC_SPACE));
      }
      break;
    case JKL_WIN_SPACE:
      if (pressed) {
        tap_code16(LGUI(KC_SPACE));
      }
      break;
  }
}
// combo setting end


/* keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  [_QWERTY] = LAYOUT(
      KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,  KC_T,         KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_GRV,  \
      KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,  KC_G,         KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,  KC_B,         KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT),  \
      KC_LANG2, KC_ESC, KC_LALT, KC_LGUI, LOWER, KC_SPC,       KC_BSPC, RAISE, KC_RGUI, KC_RALT, KC_RCTL, KC_LANG1 \
      ),


  [_LOWER] = LAYOUT( \
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_NO,   \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12, KC_APP,  KC_LPRN, KC_RPRN, _______, _______, \
      _______, _______, _______, _______, _______, _______,    KC_DEL, _______, _______, _______, _______, _______ \
      ),


  [_RAISE] = LAYOUT( \
      KC_AGRV, KC_NO,   KC_PGUP, KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO,   \
      _______, KC_HOME, KC_PGDN, KC_END,  KC_NO,   KC_NO,      KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,   \
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LANG2,   KC_LANG1, KC_NO,   _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, KC_ENT,     _______,  _______, _______, _______, _______, _______ \
      ),


    [_ADJUST] =  LAYOUT( \
      RESET,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN,  KC_NO, \
      DEBUG,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,    KC_NO,   KC_CAD,  KC_APSCR, KC_NO,\
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,    _______, _______, _______,  _______, \
      _______, _______, _______, _______, _______, _______,    _______, _______,  _______, _______, _______,  _______ \
      )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
  }
  return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
