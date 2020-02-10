#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    //_COLEMAK,
    //_DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FN
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  //COLEMAK,
  //DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  IMEON,
  IMEOFF,
  //RGBRST,
  FN
};

//Tap Dance Declarations
enum {
  TD_LBRC_LPRN = 0,
  TD_RBRC_RPRN,
  TD_SCLN_COLN,
  TD_MINS_UNDERSCORE,
  TD_EQL_PLUS,
  TD_QUOT_DQUO
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC_IMEON  IMEON
#define KC_IMEOFF IMEOFF
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)
#define KC_AGRV LALT(KC_GRV)

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

// For Double Tap
#define KC_T_LBRC TD(TD_LBRC_LPRN)
#define KC_T_RBRC TD(TD_RBRC_RPRN)
#define KC_T_SCLN TD(TD_SCLN_COLN)
#define KC_T_PDOT TD(TD_PERIOD_COMMA)
#define KC_T_MINS TD(TD_MINS_UNDERSCORE)
#define KC_T_EQL  TD(TD_EQL_PLUS)
#define KC_T_QUOT TD(TD_QUOT_DQUO)
#define KC_T_RAISE TD(TRD_HENK_RAISE)
#define KC_T_LOWER TD(TRD_MHEN_LOWER)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  [_QWERTY] = LAYOUT_ortho_4x12(
      KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_T_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, FN, \
      KC_ESC,  ADJUST,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,                    KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  [_LOWER] = LAYOUT_ortho_4x12( \
      KC_AGRV, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,     KC_7,       KC_8,     KC_9,      KC_0,      KC_BSLS, \
      _______, KC_NO,   KC_NO,   KC_DEL,  KC_NO,   KC_NO,                     KC_BSPC,  KC_T_MINS,  KC_T_EQL, KC_T_LBRC, KC_T_RBRC, KC_NO, \
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_IMEOFF,                 KC_IMEON, KC_APP ,    _______,  KC_RALT,   KC_RGUI,   _______, \
      _______, _______, _______, _______, _______, _______,                   KC_ENT ,  _______,    KC_MNXT,  KC_VOLD,   KC_VOLU,   KC_MPLY \
      ),

  [_RAISE] = LAYOUT_ortho_4x12( \
      KC_GRV,  KC_NO,   KC_PGUP, KC_ESC,  KC_NO,   KC_TAB,                    KC_NO,   KC_NO,   KC_INS,  KC_NO,   KC_PSCR, KC_PIPE, \
      _______, KC_HOME, KC_PGDN, KC_END,  KC_NO,   KC_NO,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO, \
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_RALT, KC_RGUI, _______, \
      _______, _______, _______, _______, _______, KC_ENT,                    _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

    [_ADJUST] =  LAYOUT_ortho_4x12( \
      RESET,    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_NO, \
      _______,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_CAD,  KC_APSCR, KC_PAUS,\
      _______,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    _______, \
      _______,  _______, _______, _______, _______, _______,                   _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END\
      ),

  [_FN] = LAYOUT_ortho_4x12( \
      KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      )
};

// define variables for reactive RGB
bool TOG_STATUS = false;  

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      rgblight_mode_noeeprom(RGB_current_config.mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
           rgblight_mode_noeeprom(16);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode_noeeprom(RGB_current_config.mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode_noeeprom(15);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode_noeeprom(RGB_current_config.mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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

      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    // case RGB_MOD:
    //   #ifdef RGBLIGHT_ENABLE
    //     if (record->event.pressed) {
    //       rgblight_mode_noeeprom(RGB_current_config.mode);
    //       rgblight_step();
    //       RGB_current_config.mode = rgblight_config.mode;
    //     }
    //   #endif
    //   return false;
    //   break;

    // case EISU:
    //   if (record->event.pressed) {
    //     if(keymap_config.swap_lalt_lgui==false){
    //       register_code(KC_LANG2);
    //     }else{
    //       SEND_STRING(SS_LALT("`"));
    //     }
    //   } else {
    //     unregister_code(KC_LANG2);
    //   }
    //   return false;
    //   break;
    // case KANA:
    //   if (record->event.pressed) {
    //     if(keymap_config.swap_lalt_lgui==false){
    //       register_code(KC_LANG1);
    //     }else{
    //      SEND_STRING(SS_LALT("`"));
    //     }
    //   } else {
    //     unregister_code(KC_LANG1);
    //   }
    //   return false;
    //   break;

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

    // case RGBRST:
    //   #ifdef RGBLIGHT_ENABLE
    //     if (record->event.pressed) {
    //       eeconfig_update_rgblight_default();
    //       rgblight_enable();
    //       RGB_current_config = rgblight_config;
    //     }
    //   #endif
    //   break;
  }
  return true;
}


void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      rgblight_init();
      RGB_current_config = rgblight_config;
    #endif
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
  }
}

/* All tap dance functions would go here. Only showing this one.
# ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)
# - on_each_tap_fn -> キー押下の都度実行される
# - on_dance_finished_fn -> TAPPING_TERMで設定した時間が経過した時点 or 設定していないキーが押された場合に実行される
# - on_dance_reset_fn -> on_dance_finished_fnが実行された後、TapDanceの処理をリセットする際に実行される。
*/
qk_tap_dance_action_t tap_dance_actions[] = {
  // [TD_PERIOD_COMMA]    = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMM),
  [TD_LBRC_LPRN]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_RBRC_RPRN]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_SCLN_COLN]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_MINS_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_EQL_PLUS]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
  [TD_QUOT_DQUO]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset)
};
