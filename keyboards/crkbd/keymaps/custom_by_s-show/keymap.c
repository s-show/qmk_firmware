#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
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
  BACKLIT,
  RGBRST,
  FN
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
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

// #define KC_LOWER MO(_LOWER)
// #define KC_RAISE MO(_RAISE)
#define KC_ADJUST MO(_ADJUST)
#define KC_FN MO(_FN)

//for the x tap dance. Put it here so it can be used in any keymap
void triple_functions_each_tap (qk_tap_dance_state_t *state, void *user_data);
void triple_functions_finished (qk_tap_dance_state_t *state, void *user_data);
void triple_functions_reset (qk_tap_dance_state_t *state, void *user_data); 

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
// #define KC_CTLTB CTL_T(KC_TAB)
// #define KC_GUIEI GUI_T(KC_LANG2)
// #define KC_ALTKN ALT_T(KC_LANG1)
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)
#define KC_AGRV LALT(KC_GRV)

// For Double Tap & Triple Function
#define KC_T_LBRC TD(TD_LBRC_LPRN)
#define KC_T_RBRC TD(TD_RBRC_RPRN)
#define KC_T_SCLN TD(TD_SCLN_COLN)
#define KC_T_PDOT TD(TD_PERIOD_COMMA)
#define KC_T_MINS TD(TD_MINS_UNDERSCORE)
#define KC_T_EQL  TD(TD_EQL_PLUS)
#define KC_T_QUOT TD(TD_QUOT_DQUO)
#define KC_T_RAISE TD(TRD_HENK_RAISE)
#define KC_T_LOWER TD(TRD_MHEN_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,T_SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,    FN,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI,  LOWER,  SPC,      SPC,  RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX,   DEL, XXXXX, XXXXX,                   BSPC,T_MINS, T_EQL,T_LBRC,T_RBRC, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,   APP, XXXXX,  RALT,  RGUI, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,      ENT, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       AGRV, XXXXX,  PGUP,   ESC, XXXXX,   TAB,                  XXXXX, XXXXX,   INS, XXXXX,  PSCR,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  HOME,  PGDN,   END, XXXXX, XXXXX,                   LEFT,  DOWN,    UP,  RGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,   APP, XXXXX,  RALT,  RGUI, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____,   ENT,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,   CAD, APSCR, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,      ENT, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_FN] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        F11,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,   F12,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,      ENT, _____, _____ \
                              //`--------------------'  `--------------------'
  )
};

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
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    // case LOWER:
    //   if (record->event.pressed) {
    //     layer_on(_LOWER);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   } else {
    //     layer_off(_LOWER);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   }
    //   return false;
    //   break;
    // case RAISE:
    //   if (record->event.pressed) {
    //     layer_on(_RAISE);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   } else {
    //     layer_off(_RAISE);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   }
    //   return false;
    //   break;
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        lower_pressed_time = record->event.time;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG2); // for macOS
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
          unregister_code(KC_LANG2);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG1); // for macOS
          register_code(KC_HENK);
          unregister_code(KC_HENK);
          unregister_code(KC_LANG1);
        }
        raise_pressed = false;
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
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
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
