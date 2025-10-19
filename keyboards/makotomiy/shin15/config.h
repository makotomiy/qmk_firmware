// Copyright 2023 Makoto Miyagawa (@makotomiy)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */


#define ENCODERS_PAD_A { GP29 }
#define ENCODERS_PAD_B { GP28 }

#define RGB_DI_PIN GP16
#define RGBLED_NUM 1
#define NOP_FUDGE 0.4
#define RGBLIGHT_SLEEP
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD

#define RGBLIGHT_LIMIT_VAL 20
#define RGBLIGHT_DEFAULT_VAL 5

#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
