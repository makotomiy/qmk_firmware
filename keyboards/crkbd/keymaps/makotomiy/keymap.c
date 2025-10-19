/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_brazilian_abnt2.h"
#include <stdio.h>
#include "features/custom_shift_keys.h"

enum layers {
  _COLEMAK_DH,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ACCENTS,
  _NUM_ROW,
  _PROG,
  _NAV,
  _TEST,
  _FUNCKEYS,
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  CLMK_DH,
  SWP_DOT,
  COMMDOT,
  ACUT_A,
  ACUT_E,
  ACUT_I,
  ACUT_O,
  ACUT_U,
  TILD_A,
  TILD_O,
  GRAV_A,
  CIRC_A,
  CIRC_E,
  CIRC_O,
  DIAE_U,
  D_GRAV,
  D_ACUT,
  D_TILD,
  D_CIRC,
  CB_CA,
  CB_AO,
  CB_CAO,
  CB_OES,
  CB_COES,
};

#define DEAD_KEY_COMBO(dkey, kc) ({\
  if (record->event.pressed) { \
    if (lshift) unregister_code(KC_LSFT); \
    if (rshift) unregister_code(KC_RSFT); \
    tap_code(dkey); \
    if (lshift) register_code(KC_LSFT); \
    if (rshift) register_code(KC_RSFT); \
    register_code(kc); \
  } else { \
    unregister_code(kc); \
  }\
})

#define SHDEAD_KEY_COMBO(dkey, kc) ({\
  if (record->event.pressed) { \
    if (!lshift) register_code(KC_LSFT); \
    if (!rshift) register_code(KC_RSFT); \
    tap_code(dkey); \
    if (!lshift) unregister_code(KC_LSFT); \
    if (!rshift) unregister_code(KC_RSFT); \
    register_code(kc); \
  } else { \
    unregister_code(kc); \
  }\
})

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ACCTS MO(_ACCENTS)
#define NUMROW MO(_NUM_ROW)
#define FNKEYS MO(_FUNCKEYS)
#define NAV   MO(_NAV)

#define MYLOWER LT(_LOWER, KC_DEL)
#define MYRAISE LT(_RAISE, KC_BSPC)
#define MYPROG  LT(_PROG,  KC_ENT)
#define MYESC   LT(_ADJUST, KC_ESC)
#define MYNUMR  LT(_NUM_ROW,KC_BSPC)
#define MYCTRL  CTL_T(KC_TAB)
#define MYCTSPC CTL_T(KC_SPC)
#define MYLSFT OSM(MOD_LSFT)

#define MYACCTS LT(_ACCENTS, KC_BSPC)
#define MYNAV LT(_NAV, KC_BSPC)

#define CTTAB CTL_T(KC_TAB)

#define SC_UNDO  C(KC_Z)
#define SC_CUT   C(KC_X)
#define SC_COPY  C(KC_C)
#define SC_PASTE C(KC_V)
#define SC_COMM1 C(BR_SLSH)
#define SC_COMM2 C(BR_SCLN)

#define OS_SHFT OSM(MOD_RSFT)

enum combo_events {
  CB_AC_CA,
  CB_AC_AO,
  CB_AC_CAO,
  CB_AC_OES,
  CB_AC_COES,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

// const uint16_t PROGMEM r_ac_ao_combo[]   = {TILD_A, TILD_O, COMBO_END};
// const uint16_t PROGMEM r_ac_cao_combo[]  = {ACUT_A, TILD_A, TILD_O, COMBO_END};
// const uint16_t PROGMEM r_ac_oes_combo[]  = {CIRC_E, CIRC_O, COMBO_END};
// const uint16_t PROGMEM r_ac_coes_combo[] = {ACUT_E, CIRC_E, CIRC_O, COMBO_END};
const uint16_t PROGMEM r_ac_ca_combo[]   = {ACUT_A, ACUT_E, COMBO_END};
const uint16_t PROGMEM r_ac_ao_combo[]   = {ACUT_E, ACUT_I, COMBO_END};
const uint16_t PROGMEM r_ac_cao_combo[]  = {ACUT_A, ACUT_E, ACUT_I, COMBO_END};
const uint16_t PROGMEM r_ac_oes_combo[]  = {CIRC_E, DIAE_U, COMBO_END};
const uint16_t PROGMEM r_ac_coes_combo[] = {CIRC_A, CIRC_E, DIAE_U, COMBO_END};

combo_t key_combos[] = {
  [CB_AC_CA] = COMBO(r_ac_ca_combo, CB_CA),
  [CB_AC_AO] = COMBO(r_ac_ao_combo, CB_AO),
  [CB_AC_CAO] = COMBO(r_ac_cao_combo, CB_CAO),
  [CB_AC_OES] = COMBO(r_ac_oes_combo, CB_OES),
  [CB_AC_COES] = COMBO(r_ac_coes_combo, CB_COES)

};

const custom_shift_key_t custom_shift_keys[] = {
  // {KC_BSPC, KC_DEL},
  {BR_LCBR, KC_LT},
  {BR_RCBR, KC_GT },
  {BR_LPRN, BR_COLN},
  {BR_RPRN, BR_SCLN},
  {BR_EQL,  BR_EQL},
  {BR_EXLM, BR_QUES},
  // {KC_9, BR_QUES},
  // {KC_0, BR_QUES},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_COLEMAK_DH] = LAYOUT_split_3x6_3(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    BR_MINS, KC_BSPC,
    CTTAB,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                      KC_K,    KC_H,    KC_COMM, KC_DOT,  BR_SLSH, BR_SCLN,
                                        ACCTS,   LOWER,   KC_SPC,  MYNAV,   OS_SHFT, FNKEYS
),

// accents base layer ok
[_ACCENTS] = LAYOUT_split_3x6_3(
    _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,                   BR_ACUT, TILD_A,  ACUT_U,  BR_CCED, TILD_O,  _______,
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   GRAV_A,  ACUT_A,  ACUT_E,  ACUT_I,  ACUT_O,  _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   BR_TILD, CIRC_A,  CIRC_E,  DIAE_U,  CIRC_O,  BR_DIAE,
                                        XXXXXXX, XXXXXXX, _______, XXXXXXX, KC_BSPC, _______
),

[_NAV] = LAYOUT_split_3x6_3(
    _______, KC_DEL,  KC_MS_U, KC_BTN1, XXXXXXX,  KC_PSCR,                    KC_SCRL,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,  _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,  KC_INS,                     KC_PAUSE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  _______,
    _______, SC_UNDO, SC_CUT,  SC_COPY, SC_PASTE, XXXXXXX,                    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, SC_COMM1, SC_COMM2,
                                        XXXXXXX,  XXXXXXX, _______,  _______, XXXXXXX, _______
),

[_LOWER] = LAYOUT_split_3x6_3(
    _______, BR_HASH, BR_DQUO, BR_LPRN, BR_RPRN, BR_EXLM,                   BR_SLSH, KC_7,    KC_8,    KC_9,    KC_PLUS, _______,
    _______, BR_PIPE, BR_QUOT, BR_LCBR, BR_RCBR, BR_EQL,                    BR_ASTR, KC_4,    KC_5,    KC_6,    KC_MINS, _______,
    _______, BR_BSLS, D_GRAV,  BR_LBRC, BR_RBRC, BR_AMPR,                   D_TILD,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                                        XXXXXXX, _______, _______, KC_RSFT, KC_0,    BR_EQL
),

//qwerty base layer ok
[_QWERTY] = LAYOUT_split_3x6_3(
    MYESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    BR_MINS, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, BR_SCLN,
                                        ACCTS,   LOWER,   KC_SPC,  MYNAV,   OS_SHFT, FNKEYS
),

[_FUNCKEYS] = LAYOUT_split_3x6_3(
    MYESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                   XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    _______,
    KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,                   XXXXXXX, KC_5,    KC_6,    KC_7,    KC_8,    _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,                   XXXXXXX, KC_9,    KC_0,    XXXXXXX, XXXXXXX, XXXXXXX,
                                        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______
),


[_ADJUST] = LAYOUT_split_3x6_3(
    _______, QWERTY,  CLMK_DH, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_M_R, RGB_TOG, RGB_HUI, RGB_HUD, RGB_SPI, XXXXXXX,
    DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_M_B, RGB_MOD, RGB_SAI, RGB_SAD, RGB_SPD, XXXXXXX,
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_M_P, XXXXXXX, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX,
                                        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______
)

};

// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

// const char code_to_name[60] = {
//     ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
//     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
//     'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
//     '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
//     'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
//     '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

// void set_keylog(uint16_t keycode, keyrecord_t *record) {
//   char name = ' ';
//     if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
//         (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
//   if (keycode < 60) {
//     name = code_to_name[keycode];
//   }

//   // update keylog
//   snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
//            record->event.key.row, record->event.key.col,
//            keycode, name);
// }

// void oled_render_keylog(void) {
//     oled_write(keylog_str, false);
// }

// void render_bootmagic_status(bool status) {
//     /* Show Ctrl-Gui Swap options */
//     static const char PROGMEM logo[][2][3] = {
//         {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
//         {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
//     };
//     if (status) {
//         oled_write_ln_P(logo[0][0], false);
//         oled_write_ln_P(logo[0][1], false);
//     } else {
//         oled_write_ln_P(logo[1][0], false);
//         oled_write_ln_P(logo[1][1], false);
//     }
// }

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        // oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// #ifdef OLED_ENABLE
//   if (record->event.pressed) {
//     set_keylog(keycode, record);
//   }
// #endif

  static bool lshift = false;
  static bool rshift = false;

  if (!process_custom_shift_keys(keycode, record)) { return false; }

  lshift = get_mods() & MOD_BIT(KC_LSFT);
  rshift = get_mods() & MOD_BIT(KC_RSFT);

  static uint16_t swap_dot = KC_PDOT;

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case CLMK_DH:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK_DH);
      }
      return false;
      break;
    case SWP_DOT:
      if (record->event.pressed) {
        swap_dot = swap_dot == KC_COMM ? KC_DOT : KC_COMM;
      }
      return false;
      break;
    case COMMDOT:
      if (record->event.pressed) {
        register_code(swap_dot);
      } else {
        unregister_code(swap_dot);
      }
      return false;
      break;

    case ACUT_A:
      DEAD_KEY_COMBO(BR_ACUT, KC_A);
      return false;
      break;
    case ACUT_E:
      DEAD_KEY_COMBO(BR_ACUT, KC_E);
      return false;
      break;
    case ACUT_I:
      DEAD_KEY_COMBO(BR_ACUT, KC_I);
      return false;
      break;
    case ACUT_O:
      DEAD_KEY_COMBO(BR_ACUT, KC_O);
      return false;
      break;
    case ACUT_U:
      DEAD_KEY_COMBO(BR_ACUT, KC_U);
      return false;
      break;
    case TILD_A:
      DEAD_KEY_COMBO(BR_TILD, KC_A);
      return false;
      break;
    case TILD_O:
      DEAD_KEY_COMBO(BR_TILD, KC_O);
      return false;
      break;
    case GRAV_A:
      SHDEAD_KEY_COMBO(BR_ACUT, KC_A);
      return false;
      break;
    case CIRC_A:
      SHDEAD_KEY_COMBO(BR_TILD, KC_A);
      return false;
      break;
    case CIRC_E:
      SHDEAD_KEY_COMBO(BR_TILD, KC_E);
      return false;
      break;
    case CIRC_O:
      SHDEAD_KEY_COMBO(BR_TILD, KC_O);
      return false;
      break;
    case DIAE_U:
      SHDEAD_KEY_COMBO(BR_6, KC_U);
      return false;
      break;
    case D_ACUT:
      DEAD_KEY_COMBO(BR_ACUT, KC_SPC);
      return false;
      break;
    case D_GRAV:
      SHDEAD_KEY_COMBO(BR_ACUT, KC_SPC);
      return false;
      break;
    case D_TILD:
      DEAD_KEY_COMBO(BR_TILD, KC_SPC);
      return false;
      break;
    case D_CIRC:
      SHDEAD_KEY_COMBO(BR_TILD, KC_SPC);
      return false;
      break;
    case CB_CA:
      if (record->event.pressed) {
        tap_code(BR_CCED);
        if (lshift) unregister_code(KC_LSFT);
        if (rshift) unregister_code(KC_RSFT);
        tap_code(BR_TILD);
        if (lshift) register_code(KC_LSFT);
        if (rshift) register_code(KC_RSFT);
        tap_code(KC_A);
      }
      return false;
      break;
    case CB_AO:
      if (record->event.pressed) {
        if (lshift) unregister_code(KC_LSFT);
        if (rshift) unregister_code(KC_RSFT);
        tap_code(BR_TILD);
        if (lshift) register_code(KC_LSFT);
        if (rshift) register_code(KC_RSFT);
        tap_code(KC_A);
        tap_code(KC_O);
      }
      return false;
      break;
    case CB_CAO:
      if (record->event.pressed) {
        tap_code(BR_CCED);
        if (lshift) unregister_code(KC_LSFT);
        if (rshift) unregister_code(KC_RSFT);
        tap_code(BR_TILD);
        if (lshift) register_code(KC_LSFT);
        if (rshift) register_code(KC_RSFT);
        tap_code(KC_A);
        tap_code(KC_O);
      }
      return false;
      break;
    case CB_OES:
      if (record->event.pressed) {
        if (lshift) unregister_code(KC_LSFT);
        if (rshift) unregister_code(KC_RSFT);
        tap_code(BR_TILD);
        if (lshift) register_code(KC_LSFT);
        if (rshift) register_code(KC_RSFT);
        tap_code(KC_O);
        tap_code(KC_E);
        tap_code(KC_S);
      }
      return false;
      break;
    case CB_COES:
      if (record->event.pressed) {
        tap_code(BR_CCED);
        if (lshift) unregister_code(KC_LSFT);
        if (rshift) unregister_code(KC_RSFT);
        tap_code(BR_TILD);
        if (lshift) register_code(KC_LSFT);
        if (rshift) register_code(KC_RSFT);
        tap_code(KC_O);
        tap_code(KC_E);
        tap_code(KC_S);
      }
      return false;
      break;   
   }
   return true;
}