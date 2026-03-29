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
  // Layer 0: Base (macOS)
  [0] = LAYOUT_ergodox_pretty(
    // left hand                                                   // right hand
    KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LPRN, KC_RPRN, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL,  KC_LALT, KC_LGUI, KC_F20,  ALL_T(KC_NO),                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,

                                           LGUI(KC_C), LGUI(KC_V), KC_HOME, KC_END,
                                                     DF(1),        KC_PGUP,
                               KC_SPC,    KC_LGUI,    MO(2),       KC_PGDN, KC_BSPC, KC_ENT
  ),
  // Layer 1: Base (Windows) — sticky via DF()
  [1] = LAYOUT_ergodox_pretty(
    // left hand                                                   // right hand
    KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LPRN, KC_RPRN, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LGUI,  KC_LALT, KC_LCTL, KC_F20,  ALL_T(KC_NO),                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,

                                           LCTL(KC_C), LCTL(KC_V), KC_HOME, KC_END,
                                                     DF(0),        KC_PGUP,
                               KC_SPC,    KC_LCTL,    MO(2),       KC_PGDN, KC_BSPC, KC_ENT
  ),
  // Media Layer
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

void update_leds(void) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  // LED 1: Windows default layer active
  if (biton(default_layer_state) == 1) {
    ergodox_right_led_1_on();
  }

  // LED 2: Media layer active
  if (layer_state_is(2)) {
    ergodox_right_led_2_on();
  }
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  update_leds();
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  update_leds();
  return state;
}

