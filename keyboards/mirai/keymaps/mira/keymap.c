/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "ronin.h"

#define _ML 0
#define _U1 1
#define _U2 2

#define _____ KC_TRNS


#define MACRO_GUI           99
#define BACK_TAB            0

#define M_GUI  M(MACRO_GUI)
#define B_TAB  M(BACK_TAB)

enum custom_keycodes {
    MACRO01 = SAFE_RANGE,
    MACRO02,
    MACRO03
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_ML] = KEYMAP(
  KC_GESC,  KC_F1,    KC_F2,   KC_F3,     KC_F4,   KC_F5,  KC_F6,   KC_F7,  KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,            KC_HOME,  KC_DELETE,  KC_SCLN, \
  KC_NUHS,  KC_1,     KC_2,    KC_3,      KC_4,    KC_5,   KC_6,    KC_7,   KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,                      KC_BSPC,    KC_QUOT, \
  KC_TAB,   KC_Q,     KC_W,    KC_E,      KC_R,    KC_T,   KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,     MACRO03,                     KC_RBRC,  KC_BSLS,    KC_LBRC, \
  KC_CAPS,  KC_A,     KC_S,    KC_D,      KC_F,    KC_G,   KC_H,    KC_J,   KC_K,     KC_L,     MACRO02,            MACRO01,                     KC_ENT,     KC_PGUP, \
  KC_LSFT,  KC_Z,              KC_X,      KC_C,    KC_V,   KC_B,    KC_N,   KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                     KC_RSHF,  KC_UP,      KC_PGDOWN, \
  KC_LCTRL, KC_LGUI,  KC_LALT,                             KC_SPACE,                            KC_RALT,  KC_INS,   KC_LOCKING_SCROLL, KC_LEFT,  KC_DOWN,    KC_RGHT

  ) ,
};
/*
KC_SCLN, KC_QUOT
*/
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case MACRO01:
          if(record->event.pressed){
            SEND_STRING(SS_LSFT("'")"a");
            return false;
          }
        case MACRO02:
          if(record->event.pressed){
            SEND_STRING(SS_LSFT("'")"o");
            return false;
          }
        case MACRO03:
          if(record->event.pressed){
            SEND_STRING(SS_RALT("a"));
            return false;
          }
        default:
          return true;
        }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
