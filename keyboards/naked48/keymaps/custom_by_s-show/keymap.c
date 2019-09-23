/* Copyright 2018 Salicylic_Acid
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _FN 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SEND_SUM,
  SEND_AVERAGE,
  SEND_COUNTIF,
  SEND_MAX,
  SEND_MIN,
  FN,
  RGB_RST,
  SCLN_COLN,
  LBRC_LPRN,
  RBRC_RPRN,
  MINS_UNDERSCORE,
  EQL_PLUS,
  QUOT_DQUO,
  PERIOD_COMMA
};

//Tap Dance Declarations
enum {
  TD_LBRC_LPRN = 0,
  TD_RBRC_RPRN,
  TD_SCLN_COLN,
  TD_PERIOD_COMMA,
  TD_MINS_UNDERSCORE,
  TD_EQL_PLUS,
  TD_QUOT_DQUO,
  TRD_HENK_RAISE,
  TRD_MHEN_LOWER
};

//Triple Functions
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void triple_functions_each_tap (qk_tap_dance_state_t *state, void *user_data);
void triple_functions_finished (qk_tap_dance_state_t *state, void *user_data);
void triple_functions_reset (qk_tap_dance_state_t *state, void *user_data); 

// Fillers to make layering more clear
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJUST ADJUST
#define KC_FN FN

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_RST   RESET
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_LRST  RGB_RST
#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP

#define KC_JRPRN KC_LPRN  // )
#define KC_JEQL LSFT(KC_MINS)  // =

#define KC_SNUBS S(KC_NUBS)
#define KC_SNUHS S(KC_NUHS)
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)

#define KC_SSUM  SEND_SUM
#define KC_SAVE  SEND_AVERAGE
#define KC_SCOU  SEND_COUNTIF
#define KC_SMAX  SEND_MAX
#define KC_SMIN  SEND_MIN

#define KC_RPDO LT(_RAISE, KC_PDOT)
#define KC_LP0 LT(_LOWER, KC_P0)
#define KC_NAD LT(_ADJUST, KC_NLCK)

// For Double Tap & Triple Function
#define KC_TAP_LBRC TD(TD_LBRC_LPRN)
#define KC_TAP_RBRC TD(TD_RBRC_RPRN)
#define KC_TAP_SCLN TD(TD_SCLN_COLN)
#define KC_TAP_PDOT TD(TD_PERIOD_COMMA)
#define KC_TAP_MINS TD(TD_MINS_UNDERSCORE)
#define KC_TAP_EQL  TD(TD_EQL_PLUS)
#define KC_TAP_QUOT TD(TD_QUOT_DQUO)
#define KC_TAP_RAISE TD(TRD_HENK_RAISE)
#define KC_TAP_LOWER TD(TRD_MHEN_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_With_Setta21_kc( \
  //,-----------------------------------------|             |-----------------------------------------------|  |-----------------------------------------|
        GRV,     Q,     W,     E,     R,     T,                   Y,     U,     I,       O,       P,    BSPC,      LP0,    P1,    P4,    P7,   NAD,   ESC, \
  //|------+------+------+------+------+------|             |------+------+------+--------+--------+--------|  |------+------+------+------+------+------|
      LCTRL,     A,     S,     D,     F,     G,                   H,     J,     K,       L,TAP_SCLN,TAP_QUOT,              P2,    P5,    P8,  PSLS,    F2, \
  //|------+------+------+------+------+------|             |------+------+------+--------+--------+--------|  |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                   N,     M,  COMM,TAP_PDOT,    SLSH,      FN,     RPDO,    P3,    P6,    P9,  PAST,  JEQL, \
  //|------+------+------+------+------+------|------+------+------+------+------+--------+--------|--------|  |-------------+-------------+------+------|
               ESC, LALT ,ADJUST,  LGUI,TAP_LOWER,SPC,  SPC,TAP_RAISE,MINS,  EQL,    LBRC,    RBRC,                     PENT,         PPLS,  PMNS,   DEL  \
          //`--------------------------------------------------------------------------------------|           |-----------------------------------------|
  ),
  
  [_LOWER] = LAYOUT_With_Setta21_kc( \
  //,-----------------------------------------|             |------------------------------------------------|   |-----------------------------------------|
       TILD,     1,     2,     3,     4,     5,                   6,       7,      8,       9,       0,  BSLS,     LOWER,   F11,    F4,    F7,  SMIN,   ESC, \
  //|------+------+------+------+------+------|             |------+--------+-------+--------+--------+------|   |------+------+------+------+------+------|
      _____, XXXXX, XXXXX,  DEL , XXXXX, XXXXX,                BSPC,TAP_MINS,TAP_EQL,TAP_LBRC,TAP_RBRC, XXXXX,             DOWN,  DOWN,    UP,  PSLS,    F2, \
  //|------+------+------+------+------+------|             |------+--------+-------+--------+--------+------|   |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,               XXXXX,     APP,  XXXXX,    LALT,    LGUI, XXXXX,     RAISE, XXXXX, RIGHT, XXXXX,  PAST,  JEQL, \
  //|------+------+------+------+------+------|------+------|------+--------+-------+--------+--------+------|   |-------------+-------------+------+------|
             _____, _____, _____, _____, _____, _____,   ENT, _____,    UNDS,   PLUS,    LCBR,    RCBR,                    PENT,         PPLS,  PMNS,  BSPC  \
          //`-----------------------------------------------------------------------------------------|          |-----------------------------------------|
  ),


  [_RAISE] = LAYOUT_With_Setta21_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |-----------------------------------------|
      XXXXX, XXXXX,  PGUP,   ESC, XXXXX,   TAB,               XXXXX, XXXXX,   INS, XXXXX,  PSCR, XXXXX,        LOWER,   F11,    F4,    F7,  SMIN,   ESC, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____,  HOME,  PGDN,   END, XXXXX, XXXXX,                LEFT,  DOWN,    UP,  RGHT, XXXXX, XXXXX,                 F12,    F5,    F8,  SMAX,    F2, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,               XXXXX,   APP, XXXXX,  LALT,  LGUI, XXXXX,        RAISE,    F3,    F6,    F9,  SCOU,  JEQL, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |-------------+-------------+------+------|
             _____, _____, _____, _____, _____, _____, _____, _____, XXXXX, XXXXX, XXXXX, XXXXX,                      JRPRN,         SSUM,  SAVE,   DEL  \
          //`----------------------------------------------------------------------------------|             |-----------------------------------------|
  ),
 

  [_ADJUST] = LAYOUT_With_Setta21_kc( /* Base */
  //,-----------------------------------------|             |-----------------------------------------|      |-----------------------------------------|
        RST,  EXLM,    AT,  HASH,   DLR,  PERC,                CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  LRST,       LOWER,  LVAD,  LHUD,  LSAD,ADJUST,  LTOG, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LTOG,  LMOD, XXXXX,   CAD, APSCR, XXXXX,                LVAI,  LHUI,  LSAI, XXXXX, _____, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LVAD,  LVAI,  LHUD,  LHUI,  LSAD,  LSAI,        RAISE, XXXXX, XXXXX, XXXXX, XXXXX, _____, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |-------------+-------------+------+------|
             _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,                       LMOD,         LRST, _____, _____  \
          //`----------------------------------------------------------------------------------|             |-----------------------------------------|
  ),

  [_FN] = LAYOUT_With_Setta21_kc( /* Base */
  //,-----------------------------------------|             |-----------------------------------------|      |-----------------------------------------|
        F11,    F1,    F2,    F3,    F4,    F5,                  F6,    F7,    F8,    F9,   F10,   F12,        LOWER,  LVAD,  LHUD,  LSAD,ADJUST,  LTOG, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,               XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LVAI,  LHUI,  LSAI, XXXXX, _____, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,               XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,        RAISE, XXXXX, XXXXX, XXXXX, XXXXX, _____, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |-------------+-------------+------+------|
             _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,                       LMOD,        _____, _____, _____  \
          //`----------------------------------------------------------------------------------|             |-----------------------------------------|
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        persistent_default_layer_set(1UL<<_QWERTY);
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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case FN:
        if (record->event.pressed) {
          layer_on(_FN);
        } else {
          layer_off(_FN);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGB_RST:
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        RGB_current_mode = rgblight_config.mode;
      }
      break;
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("_SUM*");
      }
      return false;
      break;
    case SEND_AVERAGE:
      if (record->event.pressed) {
        SEND_STRING("_AVERAGE*");
      }
      return false;
      break;
    case SEND_COUNTIF:
      if (record->event.pressed) {
        SEND_STRING("_COUNTIF*");
      }
      return false;
      break;
    case SEND_MAX:
      if (record->event.pressed) {
        SEND_STRING("_MAX*");
      }
      return false;
      break;
    case SEND_MIN:
      if (record->event.pressed) {
        SEND_STRING("_MIN*");
      }
      return false;
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
void dance_each_tap (qk_tap_dance_state_t *state, void *user_data) {  // キーが押下される都度実行される
  switch (state->keycode) {
    case TD(TD_LBRC_LPRN):
      if (state->count == 1) {
        register_code (KC_LBRC);
        unregister_code (KC_LBRC);
      }
      break;
    case TD(TD_RBRC_RPRN):
      if (state->count == 1) {
        register_code (KC_RBRC);
        unregister_code (KC_RBRC);
      }
      break;
    case TD(TD_SCLN_COLN):
      if (state->count == 1) {
        register_code (KC_SCLN);
        unregister_code (KC_SCLN);
      }
      break;
    case TD(TD_MINS_UNDERSCORE):
      if (state->count == 1) {
        register_code (KC_MINS);
        unregister_code (KC_MINS);
      }
      break;
    case TD(TD_EQL_PLUS):
      if (state->count == 1) {
        register_code (KC_EQL);
        unregister_code (KC_EQL);
      }
      break;
    case TD(TD_QUOT_DQUO):
      if (state->count == 1) {
        register_code (KC_QUOT);
        unregister_code (KC_QUOT);
      }
      break;
    case TD(TD_PERIOD_COMMA):
      if (state->count == 1) {
        register_code (KC_PDOT);
        unregister_code (KC_PDOT);
      }
      break;
  }
}

// TAPPING_TERMで設定した時間が経過した時点 or 設定していないキーが押された場合に実行される
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
    case TD(TD_PERIOD_COMMA):
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
    case TD(TD_PERIOD_COMMA):
      if (state->count == 1) {
        unregister_code (KC_PDOT);
      } else if (state->count == 2) {
        unregister_code (KC_PCMM);
      }
      break;
  }
}

// TAPPING_TERMで設定した時間が経過した時点 or 設定していないキーが押された場合に実行される
void dance_withBS_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (!state->interrupted) {
    switch (state->keycode) {
      case TD(TD_LBRC_LPRN):
        if (state->count == 2) {
          register_code (KC_BSPC);
          unregister_code (KC_BSPC);
          register_code (KC_LSFT);
          register_code (KC_9);
        }
        break;
      case TD(TD_RBRC_RPRN):
        if (state->count == 2) {
          register_code (KC_BSPC);
          unregister_code (KC_BSPC);
          register_code (KC_LSFT);
          register_code (KC_0);
        }
        break;
      case TD(TD_SCLN_COLN):
        if (state->count == 2) {
          register_code (KC_BSPC);
          unregister_code (KC_BSPC);
          register_code (KC_LSFT);
          register_code (KC_SCLN);
        }
        break;
      case TD(TD_MINS_UNDERSCORE):
        if (state->count == 2) {
          register_code (KC_BSPC);
          unregister_code (KC_BSPC);
          register_code (KC_LSFT);
          register_code (KC_MINS);
        }
        break;
      case TD(TD_EQL_PLUS):
        if (state->count == 2) {
          register_code (KC_BSPC);
          unregister_code (KC_BSPC);
          register_code (KC_LSFT);
          register_code (KC_EQL);
        }
        break;
      case TD(TD_QUOT_DQUO):
        if (state->count == 2) {
          register_code (KC_BSPC);
          unregister_code (KC_BSPC);
          register_code (KC_LSFT);
          register_code (KC_QUOT);
        }
        break;
      case TD(TD_PERIOD_COMMA):
        if (state->count == 2) {
          register_code (KC_BSPC);
          unregister_code (KC_BSPC);
          register_code (KC_PCMM);
        }
        break;
    }
  }
}

void dance_withBS_cln_reset (qk_tap_dance_state_t *state, void *user_data) {  // TapDanceの最後のリセット処理で実行される
  if (!state->interrupted) {
    switch (state->keycode) {
      case TD(TD_LBRC_LPRN):
        if (state->count == 2) {
          unregister_code (KC_LSFT);
          unregister_code (KC_9);
        }
        break;
      case TD(TD_RBRC_RPRN):
        if (state->count == 2) {
          unregister_code (KC_LSFT);
          unregister_code (KC_0);
        }
        break;
      case TD(TD_SCLN_COLN):
        if (state->count == 2) {
          unregister_code (KC_LSFT);
          unregister_code (KC_SCLN);
        }
        break;
      case TD(TD_MINS_UNDERSCORE):
        if (state->count == 2) {
          unregister_code (KC_LSFT);
          unregister_code (KC_MINS);
        }
        break;
      case TD(TD_EQL_PLUS):
        if (state->count == 2) {
          unregister_code (KC_LSFT);
          unregister_code (KC_EQL);
        }
        break;
      case TD(TD_QUOT_DQUO):
        if (state->count == 2) {
          unregister_code (KC_LSFT);
          unregister_code (KC_QUOT);
        }
        break;
      case TD(TD_PERIOD_COMMA):
      if (state->count == 2) {
          unregister_code (KC_PCMM);
        }
        break;
    }
  }
}

/* 
/ This setting for SingleTap, DoubleTap and Hold.
*/
void triple_functions_each_tap (qk_tap_dance_state_t *state, void *user_data) {  // キーが押下される都度実行される
  switch (state->keycode) {
    case TD(TRD_HENK_RAISE):
      if (state->count == 1) {
        // キーが一回押されたらとりあえずRAISEレイヤーをオンにする
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else if (state->count == 2) {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        register_code(KC_LALT);
      }
      break;
    case TD(TRD_MHEN_LOWER):
      if (state->count == 1) {
        // キーが一回押されたらとりあえずLOWERレイヤーをオンにする
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else if (state->count == 2) {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        register_code(KC_LGUI);
      }
      break;
  }
}

// TAPPING_TERMで設定した時間が経過した時点 or 設定していないキーが押された場合に実行される
void triple_functions_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->keycode) {
    case TD(TRD_HENK_RAISE):
      //if (state->count == 1 && !state->pressed && !state->interrupted) {
        // 「キー押下が1回・押し続けていない・設定したキー以外が押されていない」場合にタップと判断している。
      if (state->count == 1 && !state->pressed) {
        // 「キー押下が1回・押し続けていない」場合にタップと判断している。
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        register_code(KC_LANG1); // for macOS
        register_code(KC_HENK);
      }
      break;
    case TD(TRD_MHEN_LOWER):
      //if (state->count == 1 && !state->pressed && !state->interrupted) {
        // 「キー押下が1回・押し続けていない・設定したキー以外が押されていない」場合にタップと判断している。
      if (state->count == 1 && !state->pressed) {
        // 「キー押下が1回・押し続けていない」場合にタップと判断している。
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        register_code(KC_LANG2); // for macOS
        register_code(KC_MHEN);
      }
      break;
  }
}

void triple_functions_reset (qk_tap_dance_state_t *state, void *user_data) {  // TapDanceの最後のリセット処理で実行される
  switch (state->keycode) {
    case TD(TRD_HENK_RAISE):
      // if (state->count == 1 && !state->pressed && !state->interrupted) {
      if (state->count == 1 && !state->pressed) {
        unregister_code(KC_LANG1); // for macOS
        unregister_code(KC_HENK);
      }
      if (state->count == 2) {
        unregister_code(KC_LALT);
      }
      // レイヤーがオフにならないことがあるので、確実にレイヤーをオフにするため、ここでも`layer_off`メソッドを実行する。
      layer_off(_RAISE);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      break;
    case TD(TRD_MHEN_LOWER):
      // if (state->count == 1 && !state->pressed && !state->interrupted) {
      if (state->count == 1 && !state->pressed) {
        unregister_code(KC_LANG2); // for macOS
        unregister_code(KC_MHEN);
      }
      if (state->count == 2) {
        unregister_code(KC_LGUI);
      }
      // レイヤーがオフにならないことがあるので、確実にレイヤーをオフにするため、ここでも`layer_off`メソッドを実行する。
      layer_off(_LOWER);
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
//  [TD_LBRC_LPRN]       = ACTION_TAP_DANCE_FN_ADVANCED(dance_each_tap, dance_withBS_cln_finished, dance_withBS_cln_reset),
//  [TD_RBRC_RPRN]       = ACTION_TAP_DANCE_FN_ADVANCED(dance_each_tap, dance_withBS_cln_finished, dance_withBS_cln_reset),
//  [TD_SCLN_COLN]       = ACTION_TAP_DANCE_FN_ADVANCED(dance_each_tap, dance_withBS_cln_finished, dance_withBS_cln_reset),
//  [TD_MINS_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(dance_each_tap, dance_withBS_cln_finished, dance_withBS_cln_reset),
//  [TD_EQL_PLUS]        = ACTION_TAP_DANCE_FN_ADVANCED(dance_each_tap, dance_withBS_cln_finished, dance_withBS_cln_reset),
//  [TD_QUOT_DQUO]       = ACTION_TAP_DANCE_FN_ADVANCED(dance_each_tap, dance_withBS_cln_finished, dance_withBS_cln_reset),
  [TD_PERIOD_COMMA]    = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMM),
  [TD_LBRC_LPRN]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_RBRC_RPRN]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_SCLN_COLN]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_MINS_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_EQL_PLUS]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_QUOT_DQUO]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TRD_HENK_RAISE]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(triple_functions_each_tap, triple_functions_finished, triple_functions_reset, 200),
  [TRD_MHEN_LOWER]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(triple_functions_each_tap, triple_functions_finished, triple_functions_reset, 200)
};
