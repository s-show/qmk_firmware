/* Copyright 2019 Takuya Urakawa (dm9records.com)
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

extern keymap_config_t keymap_config;

enum plaid_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum plaid_keycodes {
  QWERTY = SAFE_RANGE,
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_0
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

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define FN MO(_FN)

// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
    KC_LCTL,
    KC_RCTL,
    KC_LALT,
    KC_RALT,
    KC_LSFT,
    KC_RSFT,
    KC_LGUI,
    KC_RGUI,
    LOWER,
    RAISE
};


//for the x tap dance. Put it here so it can be used in any keymap
void triple_functions_each_tap (qk_tap_dance_state_t *state, void *user_data);
void triple_functions_finished (qk_tap_dance_state_t *state, void *user_data);
void triple_functions_reset (qk_tap_dance_state_t *state, void *user_data); 

//Setup consts for LED modes
#define LEDMODE_ON 1 //always on
#define LEDMODE_OFF 0 //always off
#define LEDMODE_MODS 2 //On with modifiers
#define LEDMODE_BLINKIN 3 //blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4 //On with any keypress, off with key release
#define LEDMODE_ENTER 5 // On with enter key

#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)


// For Double Tap & Triple Function
#define TAP_LBRC TD(TD_LBRC_LPRN)
#define TAP_RBRC TD(TD_RBRC_RPRN)
#define TAP_SCLN TD(TD_SCLN_COLN)
#define TAP_PDOT TD(TD_PERIOD_COMMA)
#define TAP_MINS TD(TD_MINS_UNDERSCORE)
#define TAP_EQL  TD(TD_EQL_PLUS)
#define TAP_QUOT TD(TD_QUOT_DQUO)
#define TAP_RAISE TD(TRD_HENK_RAISE)
#define TAP_LOWER TD(TRD_MHEN_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_plaid_grid(
  //,-----------------------------------------------------------------------------------------------------------|
       KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LCTRL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,TAP_SCLN,TAP_QUOT, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,KC_COMM,TAP_PDOT, KC_SLSH,       FN, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_ESC, KC_LALT,  ADJUST, KC_LGUI,TAP_LOWER, KC_SPC,  KC_SPC,TAP_RAISE,KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC 
  //,-----------------------------------------------------------------------------------------------------------|
),

[_LOWER] = LAYOUT_plaid_grid(
  //,-----------------------------------------------------------------------------------------------------------|
      KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX,  KC_DEL, XXXXXXX, XXXXXXX, KC_BSPC,TAP_MINS, TAP_EQL,TAP_LBRC,TAP_RBRC, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_APP, XXXXXXX, KC_RALT, KC_RGUI,      FN, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,  KC_ENT, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR 
  //,-----------------------------------------------------------------------------------------------------------|
),

[_RAISE] = LAYOUT_plaid_grid(
  //,-----------------------------------------------------------------------------------------------------------|
     KC_LANG5, XXXXXXX, KC_PGUP,  KC_ESC, XXXXXXX,  KC_TAB, XXXXXXX, XXXXXXX,  KC_INS, XXXXXXX, KC_PSCR, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_PGDN,  KC_END, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_APP, XXXXXXX, KC_RALT, KC_RGUI,      FN, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,  KC_ENT, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX 
  //,-----------------------------------------------------------------------------------------------------------|
),

[_ADJUST] = LAYOUT_plaid_grid(
  //,-----------------------------------------------------------------------------------------------------------|
        RESET, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX,  KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_CAD,KC_APSCR, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX 
  //,-----------------------------------------------------------------------------------------------------------|
),

[_FN] = LAYOUT_plaid_grid(
  //,-----------------------------------------------------------------------------------------------------------|
       KC_F11,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F12, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX 
  //,-----------------------------------------------------------------------------------------------------------|
)
};

//Setup config struct for LED
typedef union {
  uint32_t raw;
  struct {
    uint8_t  red_mode :8;
    uint8_t  green_mode :8;
  };
} led_config_t;
led_config_t led_config;

//Set leds to saved state during powerup
void keyboard_post_init_user(void) {
  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  if(led_config.red_mode == LEDMODE_ON) {
      writePinHigh(LED_RED);
  }

  if(led_config.green_mode == LEDMODE_ON) {
      writePinHigh(LED_GREEN);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset! 
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_ON;
  led_config.green_mode = LEDMODE_MODS;
  eeconfig_update_user(led_config.raw);
  eeconfig_update_user(led_config.raw);
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
    switch (led_mode) {
      case LEDMODE_MODS:
        for (int i=0;i<sizeof(modifiers) / sizeof(modifiers[0]);i++) {
          if(keycode==modifiers[i]) {
            if (record->event.pressed) {
              writePinHigh(led);
            }
            else {
              writePinLow(led);
            }
          }
        }
        break;
      case LEDMODE_BLINKIN:
        if (record->event.pressed) {
          if(rand() % 2 == 1) {
            if(rand() % 2 == 0) {
              writePinLow(led);
            }
            else {
              writePinHigh(led);
            }
          }
        }
        break;
      case LEDMODE_KEY:
        if (record->event.pressed) {
          writePinHigh(led);
          return;
        }
        else {
          writePinLow(led);
          return;
        }
        break;
      case LEDMODE_ENTER:
        if (keycode==KC_ENT) {
          writePinHigh(led);
        }
        else {
          writePinLow(led);
        }
        break;

    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* If the either led mode is keypressed based, call the led updater
     then let it fall through the keypress handlers. Just to keep 
     the logic out of this procedure */
  if (led_config.red_mode >= LEDMODE_MODS && led_config.red_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_RED, led_config.red_mode, keycode, record);
  }
  if (led_config.green_mode >= LEDMODE_MODS && led_config.green_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_GREEN, led_config.green_mode, keycode, record);
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
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
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      return false;
      break;
    case LED_1:
      if (record->event.pressed) {
        if (led_config.red_mode==LEDMODE_ON) {
          led_config.red_mode=LEDMODE_OFF;
          writePinLow(LED_RED);
        }
        else {
          led_config.red_mode=LEDMODE_ON;
          writePinHigh(LED_RED);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_2:
      if (record->event.pressed) {
        if (led_config.green_mode==LEDMODE_ON) {
          led_config.green_mode=LEDMODE_OFF;
          writePinLow(LED_GREEN);
        }
        else {
          led_config.green_mode=LEDMODE_ON;
          writePinHigh(LED_GREEN);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_3:
      led_config.red_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_4:
      led_config.green_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_5:
      led_config.red_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_6:
      led_config.green_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_7:
      led_config.red_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_8:
      led_config.green_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_9:
      led_config.red_mode=LEDMODE_ENTER;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_0:
      led_config.green_mode=LEDMODE_ENTER;
      eeconfig_update_user(led_config.raw);
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else if (state->count == 2) {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        register_code(KC_LALT);
      }
      break;
    case TD(TRD_MHEN_LOWER):
      if (state->count == 1) {
        // キーが一回押されたらとりあえずLOWERレイヤーをオンにする
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else if (state->count == 2) {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
