#include QMK_KEYBOARD_H
#include "keymap_brazilian_abnt2.h"

enum layers {
  _COLEMAK_DH,
  _QWERTY,
  _ACCENTS,
  _RAISE,
  _SYMBOL,
  _NUMPAD,
  _ADJUST,
  _FUNCTION
};

enum keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  CLMK_DH,
  SWP_DOT,
  COMMDOT,
  RAISE_B,
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
  CB_CU,
  CB_CO
};

#include "g/keymap_combo.h"


#define TAP_DKEY(dkey) ({ \
    if (lshift) unregister_code(KC_LSFT); \
    if (rshift) unregister_code(KC_RSFT); \
    tap_code(dkey); \
    if (lshift) register_code(KC_LSFT); \
    if (rshift) register_code(KC_RSFT); \
})

#define TAP_SHDKEY(dkey) ({ \
    if (!lshift) register_code(KC_LSFT); \
    if (!rshift) register_code(KC_RSFT); \
    tap_code(dkey); \
    if (!lshift) unregister_code(KC_LSFT); \
    if (!rshift) unregister_code(KC_RSFT); \
})

#define DEAD_KEY_COMBO(dkey, kc) ({\
  if (record->event.pressed) { \
    TAP_DKEY(dkey); \
    register_code(kc); \
  } else { \
    unregister_code(kc); \
  }\
})

#define SHDEAD_KEY_COMBO(dkey, kc) ({\
  if (record->event.pressed) { \
    TAP_SHDKEY(dkey); \
    register_code(kc); \
  } else { \
    unregister_code(kc); \
  }\
})

#define LOWER MO(_SYMBOL)
#define RAISE MO(_RAISE)
#define FUNC MO(_ACCENTS)
#define NUMPAD MO(_NUMPAD)
#define FN MO(_FUNCTION)
#define CS(key) (C(S(key)))

/*
enum combo_events {
  CB_AC_CA,
  CB_AC_AO,
  CB_AC_CAO,
  CB_AC_OES,
  CB_AC_COES,
  CB_SCLN,
  CB_LPRN,
  CB_LCBR,
  CB_LBRC,
  CB_RPRN,
  CB_RCBR,
  CB_RBRC,
  CB_STAB, 
  CB_SDEL,
  CB_CBSPC,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

// const uint16_t PROGMEM r_ac_ao_combo[]   = {TILD_A, TILD_O, COMBO_END};
// const uint16_t PROGMEM r_ac_cao_combo[]  = {ACUT_A, TILD_A, TILD_O, COMBO_END};
// const uint16_t PROGMEM r_ac_oes_combo[]  = {CIRC_E, CIRC_O, COMBO_END};
// const uint16_t PROGMEM r_ac_coes_combo[] = {ACUT_E, CIRC_E, CIRC_O, COMBO_END};
const uint16_t PROGMEM r_ac_ca_combo[]   = {ACUT_A,  ACUT_E,  COMBO_END};
const uint16_t PROGMEM r_ac_ao_combo[]   = {ACUT_E,  ACUT_I,  COMBO_END};
const uint16_t PROGMEM r_ac_cao_combo[]  = {ACUT_A,  ACUT_E,  ACUT_I, COMBO_END};
const uint16_t PROGMEM r_ac_oes_combo[]  = {CIRC_E,  DIAE_U,  COMBO_END};
const uint16_t PROGMEM r_ac_coes_combo[] = {CIRC_A,  CIRC_E,  DIAE_U, COMBO_END};
const uint16_t PROGMEM r_scln_combo[]    = {KC_COMM, KC_DOT,  COMBO_END};
const uint16_t PROGMEM r_lprn_combo[]    = {BR_SCLN, BR_AMPR, COMBO_END};
const uint16_t PROGMEM r_lcbr_combo[]    = {BR_DQUO, BR_QUOT, COMBO_END};
const uint16_t PROGMEM r_lbrc_combo[]    = {BR_AT,   BR_ASTR, COMBO_END};
const uint16_t PROGMEM r_rprn_combo[]    = {BR_AMPR, BR_LPRN, COMBO_END};
const uint16_t PROGMEM r_rcbr_combo[]    = {BR_QUOT, BR_LCBR, COMBO_END};
const uint16_t PROGMEM r_rbrc_combo[]    = {BR_ASTR, BR_LBRC, COMBO_END};
const uint16_t PROGMEM r_sft_tab_combo[] = {KC_SPC,  KC_TAB,  COMBO_END};
const uint16_t PROGMEM r_sft_del_combo[] = {KC_LSFT, KC_DEL,  COMBO_END};
const uint16_t PROGMEM r_bspc_del_combo[] = {KC_BSPC, KC_DEL,  COMBO_END};

combo_t key_combos[] = {
  [CB_AC_CA]   = COMBO(r_ac_ca_combo, CB_CA),
  [CB_AC_AO]   = COMBO(r_ac_ao_combo, CB_AO),
  [CB_AC_CAO]  = COMBO(r_ac_cao_combo, CB_CAO),
  [CB_AC_OES]  = COMBO(r_ac_oes_combo, CB_OES),
  [CB_AC_COES] = COMBO(r_ac_coes_combo, CB_COES),
  [CB_SCLN]    = COMBO(r_scln_combo, BR_SCLN),
  [CB_LPRN]    = COMBO(r_lprn_combo, BR_LPRN),
  [CB_LCBR]    = COMBO(r_lcbr_combo, BR_LCBR),
  [CB_LBRC]    = COMBO(r_lbrc_combo, BR_LBRC),
  [CB_RPRN]    = COMBO(r_rprn_combo, BR_RPRN),
  [CB_RCBR]    = COMBO(r_rcbr_combo, BR_RCBR),
  [CB_RBRC]    = COMBO(r_rbrc_combo, BR_RBRC),
  [CB_STAB]    = COMBO(r_sft_tab_combo, S(KC_TAB)),
  [CB_SDEL]    = COMBO(r_sft_del_combo, S(KC_DEL)),
  [CB_CBSPC]    = COMBO(r_bspc_del_combo, C(KC_BSPC))
};

*/

//Tap Dance Declarations
enum tap_dance_keys {
  TAPD_SCTL = 0,
  TAPD_SALT
};

// TAP DANCE begin
void dance_ctrl_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LCTL);
  } else {
    register_code (KC_LCTL);
    // register_code (KC_LSFT);
    set_oneshot_mods(MOD_BIT(KC_LSFT));
  }
}

void dance_ctrl_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LCTL);
  } else {
    unregister_code (KC_LCTL);
    // unregister_code (KC_LSFT);
    clear_oneshot_mods();
  }
}

void dance_alt_finished (tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_LSFT);
    break;
  case 2:
    register_code (KC_LALT);
    break;
  default:
    register_code (KC_LALT);
    // register_code (KC_LSFT);
    set_oneshot_mods(MOD_BIT(KC_LSFT));
    break;
  }
}

void dance_alt_reset (tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    unregister_code (KC_LSFT);
    break;
  case 2:
    unregister_code (KC_LALT);
    break;
  default:
    unregister_code (KC_LALT);
    // unregister_code (KC_LSFT);
    clear_oneshot_mods();
    break;
  }
}

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TAPD_SCTL]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ctrl_finished, dance_ctrl_reset),
  [TAPD_SALT]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_alt_finished, dance_alt_reset)
};

#define TD_SCTL TD(TAPD_SCTL)
#define TD_SALT TD(TAPD_SALT)

#define NUMENT  LT(_NUMPAD, KC_ENT)
#define NUMTAB  LT(_NUMPAD, KC_TAB)
#define NUMBSPC LT(_NUMPAD, KC_BSPC)
#define FNSPC LT(_ACCENTS, KC_SPC)
#define SYMESC LT(_SYMBOL, KC_ESC)
#define FNESC LT(_FUNCTION, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK_DH] = LAYOUT_ortho_5x14_mod(
        BR_MINS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    BR_SCLN,
        FNESC,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_TAB,  KC_DEL,
        KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    FN,      KC_RGUI, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
                 KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_ESC,  KC_DEL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  BR_SLSH,  
                          XXXXXXX, TD_SALT, TD_SCTL, FNSPC,   NUMTAB,  NUMPAD,  KC_LSFT, LOWER,   RAISE,   XXXXXXX
    ),
    [_ACCENTS] = LAYOUT_ortho_5x14_mod(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,
        _______, XXXXXXX, KC_3,    KC_2,    KC_1,    BR_DIAE,                      BR_ACUT, TILD_A,  ACUT_U,  BR_CCED, TILD_O, KC_F12,
        _______, KC_0,    KC_6,    KC_5,    KC_4,    BR_RBRC, C(BR_SLSH), KC_CAPS, GRAV_A,  ACUT_A,  ACUT_E,  ACUT_I,  ACUT_O, _______,
                 XXXXXXX ,KC_9,    KC_8,    KC_7,    BR_LBRC, _______,    _______, BR_TILD, CIRC_A,  CIRC_E,  DIAE_U,  CIRC_O, 
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
    ),
    [_SYMBOL] = LAYOUT_ortho_5x14_mod(
        _______, BR_EXLM, BR_AT  , BR_HASH, BR_DLR,  BR_PERC,                   D_CIRC,  BR_AMPR, BR_ASTR, BR_LPRN, BR_RPRN, _______,
        _______, BR_PIPE, BR_SCLN, BR_AMPR, BR_LCBR, BR_RCBR,                   D_GRAV,  BR_PERC, KC_LT,   KC_GT,   D_ACUT,  _______,
        _______, BR_EXLM, BR_DQUO, BR_QUOT, BR_LPRN, BR_RPRN, _______, _______, BR_COLN, BR_EQL,  KC_MINS, KC_PLUS, BR_QUES, _______,
                 BR_BSLS, BR_AT,   BR_ASTR, BR_LBRC, BR_RBRC, _______, _______, BR_DLR,  BR_HASH, D_TILD,  D_CIRC,  _______,  
                          _______, _______, _______, KC_UNDS, _______, _______, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT_ortho_5x14_mod(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  _______,
        _______, XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, C(BR_SLSH), _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, _______,
                 C(KC_Z), C(KC_X), C(KC_C), XXXXXXX, C(KC_V), _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
                          _______, _______, _______, KC_SPC,  _______,    _______, _______, _______, _______, _______
    ),
    [_NUMPAD] = LAYOUT_ortho_5x14_mod(  
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX, C(KC_F), XXXXXXX, XXXXXXX,                      BR_SLSH, KC_7,    KC_8,    KC_9,    BR_ASTR, _______,
        _______, XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, C(BR_SLSH), _______, KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,    _______,
                 C(KC_Z), C(KC_X), C(KC_C), XXXXXXX, C(KC_V), _______,    _______, KC_DOT,  KC_1,    KC_2,    KC_3,    KC_PLUS,  
                          _______, _______, _______, KC_SPC,  _______,    _______, KC_TAB,  KC_0,    KC_DOT,  KC_COMM
    ),
    [_FUNCTION] = LAYOUT_ortho_5x14_mod(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
        _______, XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, C(BR_SLSH), _______, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
                 C(KC_Z), C(KC_X), C(KC_C), XXXXXXX, C(KC_V), _______,    _______, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12, 
                          _______, _______, _______, KC_CAPS, _______,    _______, _______, _______, _______, _______
    )
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//   state = update_tri_layer_state(state, _RAISE, _ACCENTS, _ADJUST);
//   state = update_tri_layer_state(state, _SYMBOL, _ACCENTS, _NUMPAD);
//   return state;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false;
  static bool rshift = false;

//   if (!process_custom_shift_keys(keycode, record)) { return false; }

  lshift = get_mods() & MOD_BIT(KC_LSFT);
  rshift = get_mods() & MOD_BIT(KC_RSFT);

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
    case RAISE_B:
      if (record->event.pressed) {
        if (rshift) {
          tap_code(KC_BSPC);
        } else {
          layer_on(_RAISE);
        }
      } else {
        layer_off(_RAISE);
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
        TAP_DKEY(BR_TILD);
        tap_code(KC_A);
      }
      return false;
      break;
    case CB_AO:
      if (record->event.pressed) {
        TAP_DKEY(BR_TILD);
        tap_code(KC_A);
        tap_code(KC_O);
      }
      return false;
      break;
    case CB_CAO:
      if (record->event.pressed) {
        tap_code(BR_CCED);
        TAP_DKEY(BR_TILD);
        tap_code(KC_A);
        tap_code(KC_O);
      }
      return false;
      break;
    case CB_OES:
      if (record->event.pressed) {
        TAP_DKEY(BR_TILD);
        tap_code(KC_O);
        tap_code(KC_E);
        tap_code(KC_S);
      }
      return false;
      break;
    case CB_COES:
      if (record->event.pressed) {
        tap_code(BR_CCED);
        TAP_DKEY(BR_TILD);
        tap_code(KC_O);
        tap_code(KC_E);
        tap_code(KC_S);
      }
      return false;
      break;
    case CB_CU:
      if (record->event.pressed) {
        tap_code(BR_CCED);
        tap_code(KC_U);
      }
      return false;
      break;      
    case CB_CO:
      if (record->event.pressed) {
        tap_code(BR_CCED);
        tap_code(KC_O);
      }
      return false;
      break;                              
  }
  return true;
}


uint16_t get_combo_term(uint16_t index, combo_t *combo) {
  // decide by combo->keycode
  switch (index) {
    case CB_AC_CA2:
    case CB_AC_AO2:
    case CB_AC_CAO2:
    case CB_AC_OES2:
    case CB_AC_COES2:
    case CB_AC_CO2:
    case CB_AC_CU2:
      return 250;
  }

  return COMBO_TERM;
}

// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case FNSPC:
//       return TAPPING_TERM + 20;
//     default:
//       return TAPPING_TERM;
//   }
// }