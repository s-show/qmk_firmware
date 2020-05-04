/* Copyright 2020 s-show
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

//Tap Dance Declarations
enum {
  TD_LBRC_LPRN = 0,
  TD_RBRC_RPRN,
  TD_SCLN_COLN,
  TD_MINS_UNDERSCORE,
  TD_EQL_PLUS,
  TD_QUOT_DQUO,
  TD_HENK_FN,
  TD_MHEN_SHIFT,
};

// For Tap Dance
#define KC_T_LBRC TD(TD_LBRC_LPRN)
#define KC_T_RBRC TD(TD_RBRC_RPRN)
#define KC_T_SCLN TD(TD_SCLN_COLN)
#define KC_T_PDOT TD(TD_PERIOD_COMMA)
#define KC_T_MINS TD(TD_MINS_UNDERSCORE)
#define KC_T_EQL  TD(TD_EQL_PLUS)
#define KC_T_QUOT TD(TD_QUOT_DQUO)

/* keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  [_QWERTY] = LAYOUT(
      KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,            KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,      KC_GRV,  \
      KC_LCTL,  KC_A,    KC_S,    KC_D,  KC_F,   KC_G,            KC_H,     KC_J,    KC_K,    KC_L,    KC_T_SCLN, KC_QUOT, \
      KC_LSFT,  KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,            KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT,  \
      KC_ESC,   KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_IMEOFF,       KC_IMEON, KC_BSPC, RAISE,   KC_RGUI, KC_RALT,   KC_APP    \
      ),

  [_LOWER] = LAYOUT( \
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,     KC_7,      KC_8,     KC_9,      KC_0,      KC_BSLS, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,    KC_T_MINS, KC_T_EQL, KC_T_LBRC, KC_T_RBRC, KC_NO,   \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,        KC_F12,   KC_NO,     _______,  _______,   _______,   _______, \
      _______, _______, _______, _______, _______, _______,       _______,  KC_DEL,    _______,  _______,   _______,   _______ \
      ),

  [_RAISE] = LAYOUT( \
      KC_AGRV, KC_NO,   KC_PGUP, KC_NO,   KC_NO,   KC_NO,         KC_NO,    KC_NO,   KC_INS,   KC_NO,    KC_PSCR, KC_NO,   \
      _______, KC_HOME, KC_PGDN, KC_END,  KC_NO,   KC_NO,         KC_LEFT,  KC_DOWN, KC_UP,    KC_RGHT,  KC_NO,   KC_NO,   \
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,    KC_NO,   _______,  _______,  _______, _______, \
      _______, _______, _______, _______, _______, _______,       _______,  _______, _______,  _______,  _______, _______ \
      ),

    [_ADJUST] =  LAYOUT( \
      RESET,      KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_NO, \
      DEBUG,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_CAD,  KC_APSCR, KC_PAUS,\
      S(KC_RSFT), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   _______, _______, _______, _______, \
      _______,    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,  _______ \
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

    //IME operations
    case KC_IMEON:
      if (record->event.pressed) {
        register_code(KC_LANG1); // for macOS
        register_code(KC_HENK);
        unregister_code(KC_LANG1);
        unregister_code(KC_HENK);
      }
      break;

    case KC_IMEOFF:
      if (record->event.pressed) {
        register_code(KC_LANG2); // for macOS
        register_code(KC_MHEN);
        unregister_code(KC_LANG2);
        unregister_code(KC_MHEN);
      }
      break;

  }
  return true;
}

/* 
/ This setting for only DoubleTap.
*/

/* Difinition `qk_tap_dance_state_t` (qmk_firmware/quantum/process/process_tap_dance.h > line.24-35)
# typedef struct
# {
#   uint8_t count;
#   uint8_t oneshot_mods;
#   uint8_t weak_mods;
#   uint16_t keycode;
#   uint16_t interrupting_keycode;
#   uint16_t timer;
#   bool interrupted;
#   bool pressed;
#   bool finished;
# qk_tap_dance_state_t; 
*/ 
void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->keycode) {
    case TD(TD_LBRC_LPRN):
      if (state->count == 1) {
        register_code (KC_LBRC);
      } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_9);
      }
      break;
    case TD(TD_RBRC_RPRN):
      if (state->count == 1) {
        register_code (KC_RBRC);
      } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_0);
      }
      break;
    case TD(TD_SCLN_COLN):
      if (state->count == 1) {
        register_code (KC_SCLN);
      } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_SCLN);
      }
      break;
    case TD(TD_MINS_UNDERSCORE):
      if (state->count == 1) {
        register_code (KC_MINS);
      } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_MINS);
      }
      break;
    case TD(TD_EQL_PLUS):
      if (state->count == 1) {
        register_code (KC_EQL);
      } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_EQL);
      }
      break;
    case TD(TD_QUOT_DQUO):
      if (state->count == 1) {
        register_code (KC_QUOT);
      } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_QUOT);
      }
      break;
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->keycode) {
    case TD(TD_LBRC_LPRN):
      if (state->count == 1) {
        unregister_code (KC_LBRC);
      } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        unregister_code (KC_9);
      }
      break;
    case TD(TD_RBRC_RPRN):
      if (state->count == 1) {
        unregister_code (KC_RBRC);
      } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        unregister_code (KC_0);
      }
      break;
    case TD(TD_SCLN_COLN):
      if (state->count == 1) {
        unregister_code (KC_SCLN);
      } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        unregister_code (KC_SCLN);
      }
      break;
    case TD(TD_MINS_UNDERSCORE):
      if (state->count == 1) {
        unregister_code (KC_MINS);
      } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        unregister_code (KC_MINS);
      }
      break;
    case TD(TD_EQL_PLUS):
      if (state->count == 1) {
        unregister_code (KC_EQL);
      } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        unregister_code (KC_EQL);
      }
      break;
    case TD(TD_QUOT_DQUO):
      if (state->count == 1) {
        unregister_code (KC_QUOT);
      } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        unregister_code (KC_QUOT);
      }
      break;
  }
}

/* All tap dance functions would go here. Only showing this one.
# ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)
# - on_each_tap_fn -> キー押下の都度実行される
# - on_dance_finished_fn -> TAPPING_TERMで設定した時間が経過した時点 or 設定していないキーが押された場合に実行される
# - on_dance_reset_fn -> on_dance_finished_fnが実行された後、TapDanceの処理をリセットする際に実行される。
*/
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LBRC_LPRN]       = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, dance_cln_reset, 200),
  [TD_RBRC_RPRN]       = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, dance_cln_reset, 200),
  [TD_SCLN_COLN]       = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, dance_cln_reset, 200),
  [TD_MINS_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, dance_cln_reset, 200),
  [TD_EQL_PLUS]        = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, dance_cln_reset, 200),
  [TD_QUOT_DQUO]       = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, dance_cln_reset, 200)
};
