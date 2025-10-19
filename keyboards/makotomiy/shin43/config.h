// Copyright 2023 Makoto Miyagawa (@makotomiy)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define COMBO_VARIABLE_LEN
#define TAPPING_TERM 200
// #define TAPPING_TERM_PER_KEY
// #define COMBO_TERM  350
#define COMBO_TERM_PER_COMBO
// #define TAPPING_FORCE_HOLD
#define PERMISSIVE_HOLD
//#define LED_CAPS_LOCK_PIN GP25
//#define RGB_DI_PIN GP29
//#define WS2812_LED_COUNT 2
//#define RGBLED_NUM 2
//#define NOP_FUDGE 0.4
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
