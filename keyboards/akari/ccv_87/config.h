// Copyright 2023 Gowtham Varma (@drakari)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config.h"

#define DEBOUNCE 5

// #define POINTING_DEVICE_ROTATION_0
#define TRACKBALL_RIGHT

#ifdef TRACKBALL_RIGHT
  #define POINTING_DEVICE_INVERT_X
  #define POINTING_DEVICE_INVERT_Y
#endif



// left encoder absent. Only right encoder at B7 and C7 on puchi C
#define ENCODERS_PAD_A { }
#define ENCODERS_PAD_B { }
#define ENCODER_RESOLUTIONS { }
#define ENCODERS_PAD_A_RIGHT { B7 } // B7 pin on right side
#define ENCODERS_PAD_B_RIGHT { C7 } // C7 pin on right side
#define ENCODERS_RESOLUTIONS_RIGHT { 4 }
#define ENCODER_MAP_KEY_DELAY 10



// OLED I2C 128x64px _Right keyboard
#ifdef OLED_ENABLE
  #define OLED_BRIGHTNESS 128
  #define OLED_DISPLAY_HEIGHT 64
  #define OLED_DISPLAY_WIDTH 128
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 30000
#endif


// Split Config
//#define USE_SERIAL // Use serial for communication between boards. bit banged 3 wire. Rx-->Rx, GND, VCC
//#define SOFT_SERIAL_PIN D2 // D2 pin on puchi-C. i.e., RX

#define SPLIT_LAYER_STATE_ENABLE // This enables syncing of the layer state between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the currently active layer.
#define SPLIT_WPM_ENABLE // This enables transmitting the current WPM to the slave side of the split keyboard. The purpose of this feature is to support cosmetic use of WPM (e.g., displaying current value on an OLED screen)
#define SPLIT_OLED_ENABLE // Enables transmitting the current OLED on/off status to the slave side of the split keyboard. The purpose of this feature is to support state (on/off state only) syncing.
#define SPLIT_POINTING_ENABLE // Enables transmitting the pointing device status to the master side of the split keyboard.
#define EE_HANDS // EEPROM HANDEDNESS

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
