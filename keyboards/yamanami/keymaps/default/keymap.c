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
  ADJUST
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
};

const uint16_t PROGMEM sdf_combo[] = {KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [SDF_ALT_SPACE] = COMBO_ACTION(sdf_combo),
  [JK_IME_ON] = COMBO_ACTION(jk_combo),
  [DF_IME_OFF] = COMBO_ACTION(df_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SDF_ALT_SPACE:
      if (pressed) {
        tap_code16(LALT(KC_SPACE));
      }
      break;
    case JK_IME_ON:
      if (pressed) {
        tap_code16(KC_LANG1);
      }
      break;
    case DF_IME_OFF:
      if (pressed) {
        tap_code16(KC_LANG2);
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
      KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,  KC_B,         KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
      KC_LANG2, KC_ESC, KC_LALT, KC_LGUI, LOWER, KC_SPC,       KC_BSPC, RAISE, KC_RGUI, KC_RALT, KC_RCTL, KC_LANG1 \
      ),

  [_LOWER] = LAYOUT( \
      KC_LANG5, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,   \
      _______,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12, KC_APP,  KC_LPRN, KC_RPRN, _______, _______, \
      _______,  _______, _______, _______, _______, _______,    KC_DEL, _______, _______, _______, _______, _______ \
      ),

  [_RAISE] = LAYOUT( \
      KC_AGRV, KC_NO,   KC_PGUP, KC_ESC,  KC_NO,   KC_TAB,     KC_NO,    KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_NO,   \
      _______, KC_HOME, KC_PGDN, KC_END,  KC_NO,   KC_NO,      KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,   \
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,   _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, KC_ENT,     _______,  _______, _______, _______, _______, _______ \
      ),

    [_ADJUST] =  LAYOUT( \
      RESET,   KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC,   KC_AMPR,   KC_ASTR, KC_LPRN,   KC_RPRN,  KC_NO, \
      DEBUG,   KC_ASPC,  KC_NO,   KC_NO,   A(KC_F4),G(KC_TAB),  A(KC_LEFT),A(KC_DOWN),A(KC_UP),A(KC_RGHT),KC_APSCR, KC_NO,\
      _______, KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,     KC_NO,     _______, _______,   _______,  _______, \
      KC_CAD,  KC_CSESC, _______, _______, _______, _______,    _______,   _______,   _______, _______,   _______,  _______ \
      )
};

static bool first_lower_pressed = false;
static uint16_t first_lower_pressed_time = 0;
static bool first_raise_pressed = false;
static uint16_t first_raise_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        if (!first_lower_pressed) {
          first_lower_pressed_time = record->event.time;
        } else if (first_lower_pressed && (TIMER_DIFF_16(record->event.time, first_lower_pressed_time) > TAPPING_TERM * 2)) {
          first_lower_pressed_time = record->event.time;
          first_lower_pressed = false;
        }
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (!first_lower_pressed && (TIMER_DIFF_16(record->event.time, first_lower_pressed_time) < TAPPING_TERM)) {
          first_lower_pressed = true;
        } else if (first_lower_pressed && (TIMER_DIFF_16(record->event.time, first_lower_pressed_time) <= TAPPING_TERM * 2)) {
          tap_code(KC_LANG2);
          first_lower_pressed = false;
        } else {
          first_lower_pressed = false;
        }
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        // 1回目のタップ
        if (!first_raise_pressed) {
          first_raise_pressed_time = record->event.time;
        // 一度タップした後に TAPPING_TERM を超える時間が経過して再びタップした場合
        } else if (first_raise_pressed && (TIMER_DIFF_16(record->event.time, first_raise_pressed_time) > TAPPING_TERM * 2)) {
          first_raise_pressed_time = record->event.time;
          first_raise_pressed = false;
        }
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (!first_raise_pressed && (TIMER_DIFF_16(record->event.time, first_raise_pressed_time) < TAPPING_TERM)) {
          first_raise_pressed = true;
        } else if (first_raise_pressed && (TIMER_DIFF_16(record->event.time, first_raise_pressed_time) <= TAPPING_TERM * 2)) {
          tap_code(KC_LANG1);
          first_raise_pressed = false;
        } else {
          first_raise_pressed = false;
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
  }
  first_lower_pressed = false;
  first_raise_pressed = false;
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};
