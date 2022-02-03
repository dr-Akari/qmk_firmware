/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef NVCONFIG_MAGIC_NUMBER
#    define NVCONFIG_MAGIC_NUMBER (uint16_t)0xFEE9  // When changing, decrement this value to avoid future re-init issues
#endif
#define NVCONFIG_MAGIC_NUMBER_OFF (uint16_t)0xFFFF

/* EEPROM parameter address */
#define NVCONFIG_MAGIC (uint16_t *)0
#define NVCONFIG_DEBUG (uint8_t *)2
#define NVCONFIG_DEFAULT_LAYER (uint8_t *)3
#define NVCONFIG_KEYMAP (uint8_t *)4
#define NVCONFIG_MOUSEKEY_ACCEL (uint8_t *)5
#define NVCONFIG_BACKLIGHT (uint8_t *)6
#define NVCONFIG_AUDIO (uint8_t *)7
#define NVCONFIG_RGBLIGHT (uint32_t *)8
#define NVCONFIG_UNICODEMODE (uint8_t *)12
#define NVCONFIG_STENOMODE (uint8_t *)13
// EEHANDS for two handed boards
#define NVCONFIG_HANDEDNESS (uint8_t *)14
#define NVCONFIG_KEYBOARD (uint32_t *)15
#define NVCONFIG_USER (uint32_t *)19
#define NVCONFIG_VELOCIKEY (uint8_t *)23

#define NVCONFIG_HAPTIC (uint32_t *)24

// Mutually exclusive
#define NVCONFIG_LED_MATRIX (uint32_t *)28
#define NVCONFIG_RGB_MATRIX (uint32_t *)28
// Speed & Flags
#define NVCONFIG_LED_MATRIX_EXTENDED (uint16_t *)32
#define NVCONFIG_RGB_MATRIX_EXTENDED (uint16_t *)32

// TODO: Combine these into a single word and single block of EEPROM
#define NVCONFIG_KEYMAP_UPPER_BYTE (uint8_t *)34
// Size of EEPROM being used, other code can refer to this for available EEPROM
#define NVCONFIG_SIZE 35
/* debug bit */
#define NVCONFIG_DEBUG_ENABLE (1 << 0)
#define NVCONFIG_DEBUG_MATRIX (1 << 1)
#define NVCONFIG_DEBUG_KEYBOARD (1 << 2)
#define NVCONFIG_DEBUG_MOUSE (1 << 3)

/* keyconf bit */
#define NVCONFIG_KEYMAP_SWAP_CONTROL_CAPSLOCK (1 << 0)
#define NVCONFIG_KEYMAP_CAPSLOCK_TO_CONTROL (1 << 1)
#define NVCONFIG_KEYMAP_SWAP_LALT_LGUI (1 << 2)
#define NVCONFIG_KEYMAP_SWAP_RALT_RGUI (1 << 3)
#define NVCONFIG_KEYMAP_NO_GUI (1 << 4)
#define NVCONFIG_KEYMAP_SWAP_GRAVE_ESC (1 << 5)
#define NVCONFIG_KEYMAP_SWAP_BACKSLASH_BACKSPACE (1 << 6)
#define NVCONFIG_KEYMAP_NKRO (1 << 7)

#define NVCONFIG_KEYMAP_LOWER_BYTE NVCONFIG_KEYMAP

bool nvconfig_is_enabled(void);
bool nvconfig_is_disabled(void);

void nvconfig_init(void);
void nvconfig_init_quantum(void);
void nvconfig_init_kb(void);
void nvconfig_init_user(void);

void nvconfig_enable(void);

void nvconfig_disable(void);

uint8_t nvconfig_read_debug(void);
void    nvconfig_update_debug(uint8_t val);

uint8_t nvconfig_read_default_layer(void);
void    nvconfig_update_default_layer(uint8_t val);

uint16_t nvconfig_read_keymap(void);
void     nvconfig_update_keymap(uint16_t val);

#ifdef AUDIO_ENABLE
uint8_t nvconfig_read_audio(void);
void    nvconfig_update_audio(uint8_t val);
#endif

uint32_t nvconfig_read_kb(void);
void     nvconfig_update_kb(uint32_t val);
uint32_t nvconfig_read_user(void);
void     nvconfig_update_user(uint32_t val);

#ifdef HAPTIC_ENABLE
uint32_t nvconfig_read_haptic(void);
void     nvconfig_update_haptic(uint32_t val);
#endif

bool nvconfig_read_handedness(void);
void nvconfig_update_handedness(bool val);

#define NVCONFIG_DEBOUNCE_HELPER(name, offset, config)                     \
    static uint8_t dirty_##name = false;                                   \
                                                                           \
    static inline void nvconfig_init_##name(void) {                        \
        nvram_read_block(offset, &config, sizeof(config));                \
        dirty_##name = false;                                              \
    }                                                                      \
    static inline void nvconfig_flush_##name(bool force) {                 \
        if (force || dirty_##name) {                                       \
            nvram_update_block(offset, &config, sizeof(config));          \
            dirty_##name = false;                                          \
        }                                                                  \
    }                                                                      \
    static inline void nvconfig_flush_##name##_task(uint16_t timeout) {    \
        static uint16_t flush_timer = 0;                                   \
        if (timer_elapsed(flush_timer) > timeout) {                        \
            nvconfig_flush_##name(false);                                  \
            flush_timer = timer_read();                                    \
        }                                                                  \
    }                                                                      \
    static inline void nvconfig_flag_##name(bool v) { dirty_##name |= v; } \
    static inline void nvconfig_write_##name(typeof(config) conf) {        \
        memcpy(&config, &conf, sizeof(config));                            \
        nvconfig_flag_##name(true);                                        \
    }
