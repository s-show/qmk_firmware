#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  LAYOUT_all(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_GRV,    \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSLS,   \
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,             KC_ENT,    \
      KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    KC_DEL,      \
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                          KC_RGUI, MO(1),    KC_LEFT, KC_DOWN,  KC_RIGHT),

  // 1: Function Layer
  LAYOUT_all(
      RESET,   KC_F1,         KC_F2,     KC_F3,     KC_F4,           KC_F5,           KC_F6,        KC_F7,   KC_F8,          KC_F9,     KC_F10,     KC_F11,   KC_F12,  KC_F13,   KC_F14,    \
      KC_NO,   KC_ALT_ERASE,  KC_SYSREQ, KC_CANCEL, KC_CLEAR,        KC_PRIOR,        KC_SEPARATOR, KC_OUT,  KC_CLEAR_AGAIN, KC_CRSEL,  KC_EXECUTE, KC_MENU,  KC_SELECT,           KC_DEL,    \
      KC_NO,   KC_STOP,       KC_AGAIN,  KC_POWER,  KC_DEL,          KC_END,          KC_PGDN,      KC_NO,   KC_NO,          KC_NO,     KC_HOME,    KC_PGUP,  KC_NO,             KC_ENT,    \
      KC_LSFT, KC_SCROLLLOCK, KC_PAUSE,  KC_POWER,  KC_SYSTEM_WAKE,  KC_MEDIA_EJECT,  KC_WFAV,      KC_VOLD, KC_VOLU,        KC_MUTE,   KC_END,     KC_PGDN,  KC_RSFT, KC_PGUP,  KC_INS,      \
      KC_LCTL, KC_LGUI,       KC_LALT,                          KC_SPC,                          KC_RGUI, MO(1),    KC_HOME, KC_PGDOWN,KC_END),

};

// Loop
void matrix_scan_user(void) {
  // Empty
};
