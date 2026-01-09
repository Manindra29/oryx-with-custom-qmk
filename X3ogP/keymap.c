#include QMK_KEYBOARD_H
#include "version.h"

#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_86_255_128,
  HSV_172_255_255,
  HSV_27_255_255,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    // left hand                                                   // right hand
    KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LPRN, KC_RPRN, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL,  KC_LALT, KC_LGUI, TT(2),   ALL_T(KC_NO),                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,

                                           LGUI(KC_C), LGUI(KC_V), KC_HOME, KC_END,
                                                     TT(1),        KC_PGUP,
                               KC_SPC,    KC_LGUI,    TT(1),       KC_PGDN, KC_BSPC, KC_ENT
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    // left hand                                                                                                                    // right hand
    RGB_SLD,        UG_HUED,       UG_HUEU,       KC_TRNS,        KC_LBRC,        KC_RBRC,        M_BRACKET_IN_CBR,               M_BRACKET_OUT_CBR, KC_TRNS,       KC_NUM_LOCK,   KC_KP_SLASH,   KC_KP_ASTERISK,KC_KP_MINUS,    KC_TRNS,
    KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,        M_ARROW_REQL,   M_BRACKET_IN_PRN,               M_BRACKET_OUT_PRN, M_ARROW_LEQL,  KC_KP_7,       KC_KP_8,       KC_KP_9,       KC_KP_PLUS,     KC_TRNS,
    KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,        M_ARROW_RMINUS,                                                               M_ARROW_LMINUS,   KC_KP_4,       KC_KP_5,       KC_KP_6,       KC_KP_PLUS,     KC_TRNS,
    KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,        M_BRACKET_IN_ANG,M_BRACKET_IN_BRC,              M_BRACKET_OUT_BRC, M_BRACKET_OUT_ANG,KC_KP_1,      KC_KP_2,       KC_KP_3,       KC_KP_ENTER,    KC_TRNS,
    KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,                                                                                      KC_KP_0,        KC_TRNS,       KC_KP_DOT,     KC_KP_ENTER,   KC_TRNS,

                                           KC_TRNS,        KC_TRNS,                KC_TRNS,        KC_TRNS,
                                                     KC_TRNS,                      KC_TRNS,
                                KC_TRNS,   KC_TRNS,  KC_TRNS,                      KC_TRNS,        KC_TRNS,       KC_TRNS
  ),
  [2] = LAYOUT_ergodox_pretty(
    // left hand                                                   // right hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,  KC_TRNS, KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, MS_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,  KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, MS_LEFT, MS_DOWN, MS_RGHT, KC_TRNS,          KC_TRNS,  KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, MS_BTN2, MS_BTN3, MS_BTN1, KC_TRNS, KC_TRNS, KC_VOLD,  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                           KC_TRNS, KC_TRNS, KC_MRWD, KC_MFFD,
                                                     KC_TRNS, KC_MPRV,
                               KC_TRNS,   KC_TRNS, KC_TRNS,  KC_MNXT, KC_TRNS, KC_MPLY
  ),
};









bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QK_MODS ... QK_MODS_MAX: 
    // Mouse keys with modifiers work inconsistently across operating systems, this makes sure that modifiers are always
    // applied to the mouse key that was pressed.
    if (IS_MOUSE_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
    if (record->event.pressed) {
        add_mods(QK_MODS_GET_MODS(keycode));
        send_keyboard_report();
        wait_ms(2);
        register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
        return false;
      } else {
        wait_ms(2);
        del_mods(QK_MODS_GET_MODS(keycode));
      }
    }
    break;

  }
  return true;
}

uint8_t layer_state_set_user(uint8_t state) {
    uint8_t layer = biton(state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};

