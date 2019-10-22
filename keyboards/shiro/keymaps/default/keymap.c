/* Copyright 2019 T.Shinohara
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
  _NUMBER = 0,
  _CURSOL,
  _MOUSE
};

enum {
  TD_HOGE = 0,
};

#define NUMBER TO(_NUMBER)
#define CURSOL TO(_CURSOL)
#define MOUSE  TO(_MOUSE)
#define KC_HOGE TD(TD_HOGE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMBER] = LAYOUT( 
    NUMBER,   CURSOL,   MOUSE,
    KC_HOGE,  KC_P8,    KC_P9,
    KC_P4,    KC_P5,    KC_P6,
    KC_P1,    KC_P2,    KC_P3,
    KC_P0,    KC_BSPC,  KC_ENT
  ),
  [_CURSOL] = LAYOUT( 
    NUMBER,   CURSOL,   MOUSE,
    KC_HOME,  KC_UP,    KC_PGUP,
    KC_LEFT,  KC_ESC,   KC_RIGHT,
    KC_END,   KC_DOWN,  KC_PGDN,
    KC_DEL,   KC_BSPC,  KC_ENT
  ), 
  [_MOUSE] = LAYOUT( 
    NUMBER,   CURSOL,   MOUSE,
    KC_CUT,   KC_COPY,  KC_PSTE,
    KC_UNDO,  KC_FIND,  KC_AGIN,
    XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_DEL,   KC_BSPC,  KC_ENT
  ),
};

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->keycode) {
    case TD(TD_HOGE):
      if (state->count == 1) {
        register_code (KC_PDOT);
      } else if (state->count == 2) {
        register_code (KC_PCMM);
      }
      break;
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {  // TapDanceの最後のリセット処理で実行される
  switch (state->keycode) {
    case TD(TD_HOGE):
      if (state->count == 1) {
        unregister_code (KC_PDOT);
      } else if (state->count == 2) {
        unregister_code (KC_PCMM);
      }
      break;
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_HOGE]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset)
};
