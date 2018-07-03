/* Copyright 2015-2017 Jack Humbert
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

#include "niu_mini.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV
};

enum custom_keycodes {
    MACRO01 = SAFE_RANGE,
    MACRO02
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO   // No-op (no key in this location on Mitosis' fake matrix)
#define _______ KC_TRNS // Transparent, because I haven't decided a mapping yet
#define ___M___ KC_TRNS // Transparent, as required by modifier key on another layer
#define KC_LMTA KC_LALT // For fun, name the mods like the space cadet keyboard does
#define KC_RMTA KC_RALT // META
#define KC_LSUP KC_LGUI // SUPER
#define KC_RSUP KC_RGUI //
#define KC_RHYP KC_INT4 // HYPER (actually muhenkan 無変換 and henkan 変換)
#define KC_LHYP KC_INT5 // or NFER/XFER.
#define RGB_FOR RGB_MODE_FORWARD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  {KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    _______},
  {KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_QUOT, KC_RSFT },
  {KC_LCTL, KC_LHYP, KC_LMTA, KC_LSUP, LOWER,   KC_BSPC, KC_SPC,  RAISE,   KC_LSUP, KC_RMTA, KC_RHYP, KC_RCTL}
},

[_LOWER] = {
  {_______, _______, _______, KC_UP,   _______, _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TILD, KC_DEL},
  {_______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_CIRC, KC_AMPR, KC_PIPE, KC_GRV,  KC_UNDS, _______},
  {_______, KC_BSLS, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, KC_SLSH, _______},
  {_______, _______, _______, RAISE,   _______, KC_DEL,  KC_ENT,  _______, LOWER,   _______, _______, _______}
},

[_RAISE] = {
  {RGB_TOG, _______, RGB_VAI, RGB_SAI, RGB_HUI, _______, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_P0,   _______},
  {RGB_FOR, MACRO01, RGB_VAD, RGB_SAD, RGB_HUD, _______, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______},
  {_______, MACRO02, _______, _______, _______, _______, KC_PMNS, KC_P1,   KC_P2,   KC_P3,   KC_EQUAL, _______},
  {_______, _______, _______, RAISE,   _______, KC_DEL,  KC_ENT, _______,  LOWER,   _______, _______, _______}
},

[_ADJUST] = {
  {RESET,   _______, _______, KC_PGUP, _______, KC_VOLU, KC_F13,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______},
  {DEBUG,   MACRO01, KC_HOME, KC_PGDN, KC_END,  KC_VOLD, KC_F14,  KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______},
  {_______, MACRO02, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_F15,  KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______},
  {KC_NUMLOCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool comm_shifted = false;
bool ques_shifted = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  uint8_t shifted;
  uint16_t s_keycode = keycode;
  bool *k_shifted = false;

  switch (keycode) {
    case KC_COMM:
      s_keycode = KC_SLSH;
      k_shifted = &comm_shifted;
      break;
    case KC_DOT:
      s_keycode = KC_1;
      k_shifted = &ques_shifted;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
      case MACRO01:
        if(record->event.pressed){
          SEND_STRING(SS_LSFT("'")"a");
          return false;
        }
        break;
      case MACRO02:
        if(record->event.pressed){
          SEND_STRING(SS_LSFT("'")"o");
          return false;
        }
        break;
  }
  
  shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));

  if (record->event.pressed && shifted) {
    *k_shifted = true;
    register_code(s_keycode);
    return false;
    // Keyup. If shift was pressed back when the key was pressed, unregister
    // its alternate keycode.
  }else if (!(record->event.pressed) && *k_shifted) {
    *k_shifted = false;
    unregister_code(s_keycode);
    return false;
    // Otherwise, behave as normal.
  } else {
    return true;
  }
}
