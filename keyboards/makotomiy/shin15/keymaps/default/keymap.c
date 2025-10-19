#include QMK_KEYBOARD_H





const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │   0   │ . │   │
     * └───────┴───┴───┘
     */
    [0] = LAYOUT_macropad_3x4_3(
        KC_P7,   KC_P8,   KC_P9,   KC_TAB,
        KC_P4,   KC_P5,   KC_P6,   KC_PENT,
        KC_P1,   KC_P2,   KC_P3,   
        KC_BSPC, KC_P0,   KC_PDOT, KC_W
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
};
#endif