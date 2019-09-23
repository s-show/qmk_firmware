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
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE

#define JP_CLON KC_QUOT  // : and +
#define JP_AT   KC_LBRC  // @ and `
#define JP_HAT  KC_EQL   // ^ and ~
#define JP_ENUN KC_RO    // \ and _ (EN mark and UNder score)
#define JP_ENVL KC_JYEN  // \ and | (EN mark and Vertical Line)
#define JP_LBRC KC_RBRC  // [ and {
#define JP_RBRC KC_BSLS  // ] and }
#define JP_AMPR KC_CIRC  // &
#define JP_QUES LSFT(KC_SLSH)  // ?
#define JP_TILD LSFT(KC_EQL)  // ~
#define JP_QUOT LSFT(KC_7)  // '
#define JP_LPRN KC_ASTR  // (
#define JP_RPRN KC_LPRN  // )
#define JP_LCBR KC_RCBR  // {
#define JP_RCBR KC_PIPE  // }
#define JP_PIPE LSFT(KC_JYEN)  // |
#define JP_ASTR LSFT(KC_QUOT)  // *
#define JP_EQL LSFT(KC_MINS)  // =
#define JP_PLUS LSFT(KC_SCLN)  // +
#define JP_DQUO LSFT(KC_2)  // "

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------.                ,-------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |    [   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+--------|
     * | Shift|   A  |   S  |   D  |   F  |   G  |                |   H  |   J  |   K  |   L  |   -  |    ]   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+--------|
     * |  Ctrl|   Z  |   X  |   C  |   V  |   B  |                |   N  |   M  |   ,  |   .  |   /  |    \   |
     * `-------------------------------------------------. ,--------------------------------------------------'
     *                     | MHEN/Win | ENT/LOWER|  Bsp  | | Del | spc/RAISE | HENK/Alt |
     *                     `-----------------------------' `-------------------------------'
     */
  [_QWERTY] = LAYOUT(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,        KC_Y, KC_U, KC_I,    KC_O,   KC_P,      JP_LBRC,
        KC_LSFT,  KC_A, KC_S, KC_D, KC_F, KC_G,       KC_H, KC_J, KC_K,    KC_L,   KC_MINS,   JP_RBRC,
        KC_LCTL,  KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,   JP_ENUN,
  LGUI_T(KC_MHEN), LT(_LOWER, KC_ENT), KC_BSPC,     KC_DEL, LT(_RAISE, KC_SPC),ALT_T(KC_HENK)
  ),
/*
  [_QWERTY] = LAYOUT(
        JP_LBRC,   KC_P,  KC_O,   KC_I, KC_U, KC_Y,       KC_T, KC_R, KC_E, KC_W, KC_Q,  KC_TAB,
        JP_RBRC,KC_MINS,  KC_L,   KC_K, KC_J, KC_H,       KC_G, KC_F, KC_D, KC_S, KC_A, KC_LSFT,
        JP_ENUN,KC_SLSH,KC_DOT,KC_COMM, KC_M, KC_N,       KC_B, KC_V, KC_C, KC_X, KC_Z, KC_LCTL,
           ALT_T(KC_HENK),LT(_RAISE, KC_SPC),KC_DEL,  KC_BSPC,LT(_LOWER, KC_ENT),LGUI_T(KC_MHEN)
  ),
*/


/*  [_QWERTY] = LAYOUT(
        RGB_TOG,   KC_P,  KC_O,   KC_I, KC_U, KC_Y,       KC_T, KC_R, KC_E, KC_W, KC_Q,  RGB_TOG,
        RGB_MOD,JP_LBRC,  KC_L,   KC_K, KC_J, KC_H,       KC_G, KC_F, KC_D, KC_S, KC_A, RGB_MOD,
        JP_ENUN,KC_SLSH,KC_DOT,KC_COMM, KC_M, KC_N,       KC_B, KC_V, KC_C, KC_X, KC_Z, KC_LCTL,
           ALT_T(KC_HENK),LT(_RAISE, KC_SPC),KC_DEL,  KC_BSPC,LT(_LOWER, KC_ENT),LGUI_T(KC_MHEN)
  ),*/
    /* Lower
     * ,-----------------------------------------.                ,------------------------------------------.
     * |  Esc |   !  |   ?  |   [  |   ]  |   ~  |                |   6  |   7  |   8  |   9  |   *  |   /   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |   '  |   #  |   "  |   (  |   )  |   @  |                |      |   4  |   5  |   6  |   -  |   =   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |   ^  |   %  |   &  |   ;  |   :  |   |  |                |   0  |   1  |   2  |   3  |   +  |  Ent  |
     * `-------------------------------------------------. ,-------------------------------------------------'
     *                             |ZENHAN| LOWER|       | |      | RAISE|   .  |
     *                             `---------------------' `-------------------'
     */
  [_LOWER] = LAYOUT(
         KC_ESC, KC_EXLM,JP_QUES,  JP_LBRC, JP_RBRC, JP_TILD,      KC_6,   KC_7, KC_8, KC_9, JP_ASTR, KC_SLSH,
        JP_QUOT, KC_HASH,JP_DQUO,  JP_LPRN, JP_RPRN, JP_AT,       KC_NO,   KC_4, KC_5, KC_6, KC_MINS, JP_EQL,
         JP_HAT, KC_PERC,JP_AMPR,  KC_SCLN, JP_CLON, JP_PIPE,      KC_0,   KC_1, KC_2, KC_3, JP_PLUS, KC_ENT,
                                   KC_ZKHK, KC_LOWER, KC_TRNS,  KC_TRNS, KC_RAISE, KC_DOT
  ),
/*
  [_LOWER] = LAYOUT(
     KC_SLSH, JP_ASTR,   KC_9,     KC_8,    KC_7,    KC_6,   JP_TILD,JP_RBRC,JP_LBRC,JP_QUES,KC_EXLM, KC_ESC,
      JP_EQL, KC_MINS,   KC_6,     KC_5,    KC_4,   KC_NO,     JP_AT,JP_RPRN,JP_LPRN,JP_DQUO,KC_HASH,JP_QUOT,
      KC_ENT, JP_PLUS,   KC_3,     KC_2,    KC_1,    KC_0,   JP_PIPE,JP_CLON,KC_SCLN,JP_AMPR,KC_PERC, JP_HAT,
                          KC_DOT,KC_RAISE,KC_TRNS,   KC_TRNS,KC_LOWER,KC_ZKHK
  ),
*/
    /* Raise
     * ,-----------------------------------------.                ,------------------------------------------.
     * | Esc  |   1  |   2  |   3  |   4  |   5  |                |  6   |      |  ª  |      |  PGUP|  Bsp  |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |F11/Shift| F1|  F2  |  F3  |  F4  |  F5  |                |      |  ©  |  «  |  ¨  |PGDOWN|  ENT  |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |F12/Ctrl | F6|  F7  |  F8  |  F9  |  F10 |                |      |      |      |      |      |       |
     * `------------------------------------------------. ,-------------------------------------------------'
     *                          |       | LOWER  |      | |       |RAISE |      |
     *                          `-----------------------' `--------------------'
     */

  [_RAISE] = LAYOUT(
         KC_ESC,  KC_1, KC_2,   KC_3,   KC_4,   KC_5,         KC_6,   KC_NO,   KC_UP,   KC_NO,  KC_PGUP, KC_BSPC,
   SFT_T(KC_F11),KC_F1, KC_F2, KC_F3,  KC_F4,  KC_F5,         KC_NO, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_PGDN,  KC_ENT,
  LCTL_T(KC_F12),KC_F6, KC_F7, KC_F8,  KC_F9, KC_F10,         KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,
                           KC_LGUI, KC_LOWER, KC_TRNS,     KC_TRNS, KC_RAISE, KC_LALT
  ),

/*
  [_RAISE] = LAYOUT(
         KC_BSPC,KC_PGUP,   KC_NO,   KC_UP,  KC_NO,   KC_6,      KC_5,  KC_4, KC_3, KC_2, KC_1, KC_ESC,
          KC_ENT,KC_PGDN,KC_RIGHT, KC_DOWN,KC_LEFT,  KC_NO,     KC_F5, KC_F4,KC_F3,KC_F2,KC_F1,SFT_T(KC_F11),
           KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,    KC_F10, KC_F9,KC_F8,KC_F7,KC_F6,LCTL_T(KC_F12),
                           KC_LALT,KC_RAISE,KC_TRNS,  KC_TRNS,KC_LOWER,KC_LGUI
  ),
*/
    /* Adjust
     * ,-----------------------------------------.                ,------------------------------------------.
     * |  Esc |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  |  Del  |
     * |------+------+--------+------+--------+--|                |------+------+------+------+------+-------|
     * |F11/Shift| F1|  F2  |  F3  |  F4  |  F5  |                | LTOG | LMOD |      | C A D| A Prt| PrtScn|
     * |------+------+--------+------+--------+--|                |------+------+------+------+------+-------|
     * |F12/Ctrl | F6|  F7  |  F8  |  F9  |  F10 |                |  VAD |  VAI |  HUD |  HUI |  SAD |  SAI  |
     * `------------------------------------------------. ,-------------------------------------------------'
     *                             |      | LOWER|      | |       | RAISE|      |
     *                             `---------------------' `--------------------'
     */

  [_ADJUST] = LAYOUT(
          KC_ESC, KC_1,  KC_2,  KC_3,   KC_4,   KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL,
   SFT_T(KC_F11),KC_F1, KC_F2, KC_F3,  KC_F4,  KC_F5,       RGB_TOG, RGB_MOD,   KC_NO,LCA(KC_DEL), LALT(KC_PSCR),KC_PSCR,
  LCTL_T(KC_F12),KC_F6, KC_F7, KC_F8,  KC_F9, KC_F10,       RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD,  RGB_SAI,
                          KC_TRNS, KC_RAISE, KC_TRNS,      KC_TRNS, KC_LOWER, KC_TRNS
   )
/*
  [_ADJUST] = LAYOUT(
          KC_DEL, KC_0,  KC_9,  KC_8,   KC_7,   KC_6,          KC_5,    KC_4,    KC_3,    KC_2,    KC_1,   KC_ESC,
  KC_PSCR,LALT(KC_PSCR),LCA(KC_DEL),KC_NO,RGB_MOD,RGB_TOG,    KC_F5,   KC_F4,   KC_F3,   KC_F2,   KC_F1,SFT_T(KC_F11),
    RGB_SAI,RGB_SAD, RGB_HUI,RGB_HUD,RGB_VAI,RGB_VAD,        KC_F10,   KC_F9,   KC_F8,   KC_F7,   KC_F6,LCTL_T(KC_F12),
                          KC_TRNS, KC_RAISE,KC_TRNS,        KC_TRNS,KC_LOWER, KC_TRNS
   )
*/
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
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

#endif
