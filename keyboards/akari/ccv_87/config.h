// Copyright 2023 Gowtham Varma (@drakari)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config.h"

#define DEBOUNCE 5

// set which MCU has the pointing device attached
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_ROTATION_180
#define POINTING_DEVICE_SCALE 1

#define LAYER_STATE_8BIT // limiting the number of layers since we have under 4 layers.


// left encoder absent. Only right encoder at B7 and C7 on puchi C
#define ENCODERS_PAD_A { }
#define ENCODERS_PAD_B { }
#define ENCODER_RESOLUTIONS { }
#define ENCODERS_PAD_A_RIGHT { B7 } // B7 pin on right side
#define ENCODERS_PAD_B_RIGHT { C7 } // C7 pin on right side
#define ENCODERS_RESOLUTIONS_RIGHT { 4 }
#define ENCODER_MAP_KEY_DELAY 10

// #define WPM_ALLOW_COUNT_REGRESSION

// OLED I2C 128x64px _Right keyboard
#ifdef OLED_ENABLE
  #define OLED_BRIGHTNESS 128
  #define OLED_DISPLAY_HEIGHT 64
  #define OLED_DISPLAY_WIDTH 128
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 0
#endif


#define SPLIT_LAYER_STATE_ENABLE // This enables syncing of the layer state between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the currently active layer.
#define SPLIT_WPM_ENABLE // This enables transmitting the current WPM to the slave side of the split keyboard. The purpose of this feature is to support cosmetic use of WPM (e.g., displaying current value on an OLED screen)
#define SPLIT_OLED_ENABLE // Enables transmitting the current OLED on/off status to the slave side of the split keyboard. The purpose of this feature is to support state (on/off state only) syncing.
#define SPLIT_POINTING_ENABLE // Enables transmitting the pointing device status to the master side of the split keyboard.
#define EE_HANDS // EEPROM HANDEDNESS

// bootmagic config
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 8



// #define LAYER_STATE_8BIT
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
