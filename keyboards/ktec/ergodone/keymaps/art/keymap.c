#include "art.h"
#include "sendstring_workman_zxcvm.h"

bool is_win = true;

enum custom_keycodes {
  keyboardSpecificKeyCode = NEW_SAFE_RANGE //not used
};

void led_show_current_os(void) {
  if (is_win) {
    ergodox_right_led_1_on();
    wait_ms(50);
    ergodox_right_led_1_off();
    wait_ms(50);
    ergodox_right_led_1_on();
    wait_ms(50);
    ergodox_right_led_1_off();
    wait_ms(50);
    ergodox_right_led_1_on();
    wait_ms(50);
    ergodox_right_led_1_off();
    wait_ms(50);
  } else {
    ergodox_right_led_3_on();
    wait_ms(50);
    ergodox_right_led_3_off();
    wait_ms(50);
    ergodox_right_led_3_on();
    wait_ms(50);
    ergodox_right_led_3_off();
    wait_ms(50);
    ergodox_right_led_3_on();
    wait_ms(50);
    ergodox_right_led_3_off();
    wait_ms(50);
  }
}

void matrix_init_user(void) {
  led_show_current_os();
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    ergodox_right_led_2_on();
  } else {
    ergodox_right_led_2_off();
  }
}



layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_3_off();
  switch (get_highest_layer(state)) {
    case NAV:
    case CTRL_NAV:
    case SHIFT_NAV:
      ergodox_right_led_1_on();
      break;
    case FKEYS:
      ergodox_right_led_3_on();
      break;
  }
  return state;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base qwerty layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ` ~   |   1  |   2  |   3  |   4  |   5  |  ESC |           | - _  |   6  |   7  |   8  |   9  |   0  |   ]    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | ???  |           |  =   |   Y  |   U  |   I  |   O  |   P  |   [    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |   '    |
 * |--------+------+------+------+------+------| FKEYS|           | FKEYS|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  | / git| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |Media\| Win  |Alt   | NAV  |                                       | Home | End  |Workmn|      | RCtrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | Del  |  Ins |       | Left |  Right |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | PgUp |       |SFT_NV|        |      |
 *                                 | Space|BSpace|------|       |------|  NAV   |Enter |
 *                                 |      |      | PgDn |       |CTR_NV|        |      |
 *                                 `--------------------'       `----------------------'
 */
[QWERTY] = LAYOUT_ergodox(
  // -----------------------------------------------------left hand-----------------------------------------------------
  KC_GRAVE,         KC_1,         KC_2,       KC_3,       KC_4,              KC_5,      KC_ESCAPE,
  KC_TAB,           KC_Q,         KC_W,       KC_E,       KC_R,              KC_T,      XXXXXXX,
  KC_CAPS,          KC_A,         KC_S,       KC_D,       KC_F,              KC_G,
  KC_LSFT,          KC_Z,         KC_X,       KC_C,       KC_V,              KC_B,      TT(FKEYS),
  KC_LCTRL,  LT(MEDIA, KC_BSLASH), KC_LWIN,   KC_LALT,    LT(NAV, KC_RIGHT),

                                           KC_DEL,    KC_INS,
                                                      KC_PGUP,
                                  KC_SPC, LT(COMBOS,KC_BSPC), KC_PGDOWN,

  // -----------------------------------------------------right hand-----------------------------------------------------
  KC_MINS,          KC_6,         KC_7,       KC_8,       KC_9,              KC_0,      KC_RBRC,
  KC_EQL,           KC_Y,         KC_U,       KC_I,       KC_O,              KC_P,      KC_LBRC,
                    KC_H,         KC_J,       KC_K,       KC_L,              KC_SCLN,   KC_QUOT,
  TT(FKEYS),        KC_N,         KC_M,       KC_COMM,    KC_DOT,        LT(GIT,KC_SLSH), KC_RSFT,
                                  KC_HOME,    KC_END,     DF(WORKMAN),       KC_RALT,   KC_RCTRL,

    KC_LEFT,                KC_RIGHT,
    LT(SHIFT_NAV, KC_UP),
    LT(CTRL_NAV, KC_DOWN),  MO(NAV),   KC_ENT
),
 /* Workman
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   D  |   R  |   W  |   B  |      |           |      |   J  |   F  |   U  |   P  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |  I   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   M  |      |           |      |   K  |   L  |   ,  |   .  |  /   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |QWERTY|      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[WORKMAN] = LAYOUT_ergodox(  
  // -----------------------------------------------------left hand-----------------------------------------------------
  _______,          _______,      _______,    _______,    _______,           _______,   _______,
  _______,          KC_Q,         KC_D,       KC_R,       KC_W,              KC_B,      _______,
  _______,          KC_A,         KC_S,       KC_H,       KC_T,              KC_G,
  _______,          KC_Z,         KC_X,       KC_C,       KC_V,              KC_M,      _______,
  _______,          _______,      _______,    _______,    _______,

                                            _______,   _______,
                                                       _______,
                                  _______,  _______,   _______,

  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          _______,      _______,    _______,    _______,           _______,   _______,
  _______,          KC_J,         KC_F,       KC_U,       KC_P,              KC_SCLN,   _______,
                    KC_Y,         KC_N,       KC_E,       KC_O,              KC_I,      _______,
  _______,          KC_K,         KC_L,       KC_COMM,    KC_DOT,            KC_SLSH,   _______,
                                  _______,    _______,    DF(QWERTY),        _______,   _______,

    _______,  _______,
    _______,
    _______,  _______, _______
),

[FKEYS] = LAYOUT_ergodox(
  // -----------------------------------------------------left hand-----------------------------------------------------
  _______,          KC_F1,            KC_F2,            KC_F3,            KC_F4,            KC_F5,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,

                                            _______,   _______,
                                                       _______,
                                  _______,  _______,   _______,
  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          KC_F6,            KC_F7,            KC_F8,            KC_F9,            KC_F10,           KC_F11,
  _______,          _______,          _______,          _______,          _______,          _______,          KC_F12,
                    _______,          _______,          _______,          _______,          _______,          KC_PSCREEN,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          _______,          _______,

    _______,     _______,
    _______,
    _______,     _______,    _______
),

[NAV] = LAYOUT_ergodox(
  // -----------------------------------------------------left hand-----------------------------------------------------
  _______,          LALT(KC_F1),      LALT(KC_F2),      LALT(KC_F3),      LALT(KC_F4),      LALT(KC_F5),      _______,
  _______,          _______,          KC_HOME,          KC_UP,            KC_END,           KC_PGUP,          _______,
  _______,          _______,          KC_LEFT,          KC_DOWN,          KC_RIGHT,         KC_PGDOWN,
  _______,          _______,          _______,          _______,          KC_LALT,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,        

                                            _______,   _______,
                                                       _______,
                                  _______,  KC_DEL,    _______,                               
  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          LALT(KC_F6),      LALT(KC_F7),      LALT(KC_F8),      LALT(KC_F9),      LALT(KC_F10),     LALT(KC_F11),
  _______,          _______,          _______,          _______,          _______,          _______,          LALT(KC_F12),
                    _______,          CTR_ALT,          KC_RSFT,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          _______,          _______,

    _______,     _______,
    _______,
    _______,     _______,    _______
),

[CTRL_NAV] = LAYOUT_ergodox(
  // -----------------------------------------------------left hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          CTL_ALT(KC_HOME), CTL_ALT(KC_UP),   CTL_ALT(KC_END),  CTL_ALT(KC_PGUP), _______,
  _______,          _______,          CTL_ALT(KC_LEFT), CTL_ALT(KC_DOWN), CTL_ALT(KC_RIGHT),CTL_ALT(KC_PGDOWN),
  _______,          _______,          CTL_ALT(KC_X),    CTL_ALT(KC_C),    CTL_ALT(KC_V),    _______,          _______,
  _______,          _______,          _______,          _______,          _______,

                                            CTL_ALT(KC_DEL),  _______,
                                                              _______,
                                  _______,  CTL_ALT(KC_BSPC), CTL_ALT(KC_DEL),
  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    CTL_ALT(KC_HOME), CTL_ALT(KC_END),  _______,          _______,          _______,

    CTL_ALT(KC_LEFT), CTL_ALT(KC_RIGHT),
    KC_RSFT,
    _______,       _______,    _______
),

[SHIFT_NAV] = LAYOUT_ergodox(
  // -----------------------------------------------------left hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          LSFT(KC_HOME),    LSFT(KC_UP),      LSFT(KC_END),     LSFT(KC_PGUP),    _______,
  _______,          _______,          LSFT(KC_LEFT),    LSFT(KC_DOWN),    LSFT(KC_RIGHT),   LSFT(KC_PGDOWN),
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,

                                            _______,   _______,
                                                       _______,
                                  _______,  _______,   _______,


  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    LSFT(KC_HOME),    LSFT(KC_END),     _______,          _______,          _______,

    LSFT(KC_LEFT), LSFT(KC_RIGHT),
    _______,
    CTR_ALT,       _______,    _______
),

[COMBOS] = LAYOUT_ergodox(  
  // -----------------------------------------------------left hand-----------------------------------------------------
  TILD_BLOCK,       PRESCRIPTION,          _______,          _______,          FOURS,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          ADMINS,          SARCASM,          _______,          CTRL_CTV,         _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,

                                            _______,   _______,
                                                       _______,
                                  _______,  _______,   _______,

  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          CTRL_LCTV,        _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          _______,          _______,

    _______,     _______,
    _______,
    _______,     _______,    _______
),

// [STRINGS] = LAYOUT_ergodox(  
//   // -----------------------------------------------------left hand-----------------------------------------------------
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,

//                                             _______,   _______,
//                                                        _______,
//                                   _______,  _______,   _______,

//   // -----------------------------------------------------right hand-----------------------------------------------------
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//                     _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//                     _______,          _______,          _______,          _______,          _______,

//     _______,     _______,
//     _______,
//     _______,     _______,    _______
// ),

[MEDIA] = LAYOUT_ergodox(  
  // -----------------------------------------------------left hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          KC_MPRV,          KC_VOLU,          KC_MNXT,          _______,          _______,
  _______,          _______,          _______,          KC_VOLD,          _______,          _______,
  _______,          _______,          _______,          KC_MUTE,          KC_MPLY,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,

                                            _______,   _______,
                                                       _______,
                                  _______,  _______,   _______,

  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          TOG_OS,           _______,          _______,
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
                    _______,          _______,          _______,          _______,          _______,

    _______,     _______,
    _______,
    _______,     _______,    _______
),

[GIT] = LAYOUT_ergodox(  
  // -----------------------------------------------------left hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          G_DIFF,           G_RST,            _______,          G_BRCH,          _______,
  _______,          G_ADD,            G_S,              _______,          _______,          _______,
  _______,          _______,          _______,          G_C,              _______,          G_MERG,          _______,
  _______,          _______,          _______,          _______,          _______,

                                            _______,   _______,
                                                       _______,
                                  _______,  _______,   _______,

  // -----------------------------------------------------right hand-----------------------------------------------------
  _______,          _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          G_FTCH,           _______,          G_P,              _______,          _______,
                    _______,          _______,          _______,          _______,          _______,          _______,
  _______,          _______,          G_LOG,            _______,          G_DEV,            _______,          _______,
                    _______,          _______,          _______,          _______,          _______,

    _______,     _______,
    _______,
    _______,     _______,    _______
),

[GIT_C] = LAYOUT_ergodox(  
  // -----------------------------------------------------left hand-----------------------------------------------------
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          G_CHEC,           XXXXXXX,          XXXXXXX,
  _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,

                                            XXXXXXX,   XXXXXXX,
                                                       XXXXXXX,
                                  XXXXXXX,  KC_BSPC,   XXXXXXX,

  // -----------------------------------------------------right hand-----------------------------------------------------
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
                    XXXXXXX,          XXXXXXX,          XXXXXXX,          G_COMM,           XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          _______,
                    XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,

    XXXXXXX,     XXXXXXX,
    XXXXXXX,
    XXXXXXX,     XXXXXXX,    XXXXXXX
),

[GIT_S] = LAYOUT_ergodox(  
  // -----------------------------------------------------left hand-----------------------------------------------------
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          G_STSH,           G_SHOW,           G_STAT,           XXXXXXX,
  _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,

                                            XXXXXXX,   XXXXXXX,
                                                       XXXXXXX,
                                  XXXXXXX,  KC_BSPC,   XXXXXXX,

  // -----------------------------------------------------right hand-----------------------------------------------------
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
                    XXXXXXX,          XXXXXXX,          XXXXXXX,          G_COMM,           XXXXXXX,          XXXXXXX,
  XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          _______,
                    XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,

    XXXXXXX,     XXXXXXX,
    XXXXXXX,
    XXXXXXX,     XXXXXXX,    XXXXXXX
),


/* Numpad
 *
 *           ,--------------------------------------------------.
 *           |      |      |      |      |      |   /  |        |
 *           |------+------+------+------+------+------+--------|
 *           |      |      |   7  |   8  |   9  |   *  |        |
 *           |      |------+------+------+------+------+--------|
 *           |------|      |   4  |   5  |   6  |   -  |  Enter |
 *           |      |------+------+------+------+------+--------|
 *           |      |      |   1  |   2  |   3  |   +  |  Enter |
 *           `-------------+------+------+------+------+--------'
 *                         |      |   0  |   .  | Calc | Calc   |
 *                         `----------------------------------'
 */

// [] = LAYOUT_ergodox(  
//   // -----------------------------------------------------left hand-----------------------------------------------------
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,

//                                             _______,   _______,
//                                                        _______,
//                                   _______,  _______,   _______,

//   // -----------------------------------------------------right hand-----------------------------------------------------
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//                     _______,          _______,          _______,          _______,          _______,          _______,
//   _______,          _______,          _______,          _______,          _______,          _______,          _______,
//                     _______,          _______,          _______,          _______,          _______,

//     _______,     _______,
//     _______,
//     _______,     _______,    _______
// ),

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  }
  return true;
}