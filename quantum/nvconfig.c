#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "nvconfig.h"
#include "action_layer.h"

#if defined(NVRAM_DRIVER)
#    include "nvram_driver.h"
#endif

#if defined(HAPTIC_ENABLE)
#    include "haptic.h"
#endif

#if defined(VIA_ENABLE)
bool via_eeprom_is_valid(void);
void via_eeprom_set_valid(bool valid);
void nvconfig_init_via(void);
#endif

/** \brief eeconfig enable
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void nvconfig_init_user(void) {
    // Reset user EEPROM value to blank, rather than to a set value
    nvconfig_update_user(0);
}

__attribute__((weak)) void nvconfig_init_kb(void) {
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    nvconfig_update_kb(0);

    nvconfig_init_user();
}

/*
 * FIXME: needs doc
 */
void nvconfig_init_quantum(void) {
#if defined(NVRAM_DRIVER)
    nvram_driver_erase();
#endif
    nvram_update_u16(NVCONFIG_MAGIC, NVCONFIG_MAGIC_NUMBER);
    nvram_update_u8(NVCONFIG_DEBUG, 0);
    nvram_update_u8(NVCONFIG_DEFAULT_LAYER, 0);
    default_layer_state = 0;
    nvram_update_u8(NVCONFIG_KEYMAP_LOWER_BYTE, 0);
    nvram_update_u8(NVCONFIG_KEYMAP_UPPER_BYTE, 0);
    nvram_update_u8(NVCONFIG_MOUSEKEY_ACCEL, 0);
    nvram_update_u8(NVCONFIG_BACKLIGHT, 0);
    nvram_update_u8(NVCONFIG_AUDIO, 0xFF);  // On by default
    nvram_update_u32(NVCONFIG_RGBLIGHT, 0);
    nvram_update_u8(NVCONFIG_STENOMODE, 0);
    nvram_update_u32(NVCONFIG_HAPTIC, 0);
    nvram_update_u8(NVCONFIG_VELOCIKEY, 0);
    nvram_update_u32(NVCONFIG_RGB_MATRIX, 0);
    nvram_update_u16(NVCONFIG_RGB_MATRIX_EXTENDED, 0);

    // TODO: Remove once ARM has a way to configure NVCONFIG_HANDEDNESS
    //        within the emulated eeprom via dfu-util or another tool
#if defined INIT_EE_HANDS_LEFT
#    pragma message "Faking EE_HANDS for left hand"
    nvram_update_u8(NVCONFIG_HANDEDNESS, 1);
#elif defined INIT_EE_HANDS_RIGHT
#    pragma message "Faking EE_HANDS for right hand"
    nvram_update_u8(NVCONFIG_HANDEDNESS, 0);
#endif

#if defined(HAPTIC_ENABLE)
    haptic_reset();
#else
    // this is used in case haptic is disabled, but we still want sane defaults
    // in the haptic configuration eeprom. All zero will trigger a haptic_reset
    // when a haptic-enabled firmware is loaded onto the keyboard.
    nvram_update_u32(NVCONFIG_HAPTIC, 0);
#endif
#if defined(VIA_ENABLE)
    // Invalidate VIA eeprom config, and then reset.
    // Just in case if power is lost mid init, this makes sure that it pets
    // properly re-initialized.
    via_eeprom_set_valid(false);
    nvconfig_init_via();
#endif

    nvconfig_init_kb();
}

/** \brief eeconfig initialization
 *
 * FIXME: needs doc
 */
void nvconfig_init(void) { nvconfig_init_quantum(); }

/** \brief eeconfig enable
 *
 * FIXME: needs doc
 */
void nvconfig_enable(void) { nvram_update_u16(NVCONFIG_MAGIC, NVCONFIG_MAGIC_NUMBER); }

/** \brief eeconfig disable
 *
 * FIXME: needs doc
 */
void nvconfig_disable(void) {
#if defined(NVRAM_DRIVER)
    nvram_driver_erase();
#endif
    nvram_update_u16(NVCONFIG_MAGIC, NVCONFIG_MAGIC_NUMBER_OFF);
}

/** \brief eeconfig is enabled
 *
 * FIXME: needs doc
 */
bool nvconfig_is_enabled(void) {
    bool is_eeprom_enabled = (nvram_read_u16(NVCONFIG_MAGIC) == NVCONFIG_MAGIC_NUMBER);
#ifdef VIA_ENABLE
    if (is_eeprom_enabled) {
        is_eeprom_enabled = via_eeprom_is_valid();
    }
#endif
    return is_eeprom_enabled;
}

/** \brief eeconfig is disabled
 *
 * FIXME: needs doc
 */
bool nvconfig_is_disabled(void) {
    bool is_eeprom_disabled = (nvram_read_u16(NVCONFIG_MAGIC) == NVCONFIG_MAGIC_NUMBER_OFF);
#ifdef VIA_ENABLE
    if (!is_eeprom_disabled) {
        is_eeprom_disabled = !via_eeprom_is_valid();
    }
#endif
    return is_eeprom_disabled;
}

/** \brief eeconfig read debug
 *
 * FIXME: needs doc
 */
uint8_t nvconfig_read_debug(void) { return nvram_read_u8(NVCONFIG_DEBUG); }
/** \brief eeconfig update debug
 *
 * FIXME: needs doc
 */
void nvconfig_update_debug(uint8_t val) { nvram_update_u8(NVCONFIG_DEBUG, val); }

/** \brief eeconfig read default layer
 *
 * FIXME: needs doc
 */
uint8_t nvconfig_read_default_layer(void) { return nvram_read_u8(NVCONFIG_DEFAULT_LAYER); }
/** \brief eeconfig update default layer
 *
 * FIXME: needs doc
 */
void nvconfig_update_default_layer(uint8_t val) { nvram_update_u8(NVCONFIG_DEFAULT_LAYER, val); }

/** \brief eeconfig read keymap
 *
 * FIXME: needs doc
 */
uint16_t nvconfig_read_keymap(void) { return (nvram_read_u8(NVCONFIG_KEYMAP_LOWER_BYTE) | (nvram_read_u8(NVCONFIG_KEYMAP_UPPER_BYTE) << 8)); }
/** \brief eeconfig update keymap
 *
 * FIXME: needs doc
 */
void nvconfig_update_keymap(uint16_t val) {
    nvram_update_u8(NVCONFIG_KEYMAP_LOWER_BYTE, val & 0xFF);
    nvram_update_u8(NVCONFIG_KEYMAP_UPPER_BYTE, (val >> 8) & 0xFF);
}

/** \brief eeconfig read audio
 *
 * FIXME: needs doc
 */
uint8_t nvconfig_read_audio(void) { return nvram_read_u8(NVCONFIG_AUDIO); }
/** \brief eeconfig update audio
 *
 * FIXME: needs doc
 */
void nvconfig_update_audio(uint8_t val) { nvram_update_u8(NVCONFIG_AUDIO, val); }

/** \brief eeconfig read kb
 *
 * FIXME: needs doc
 */
uint32_t nvconfig_read_kb(void) { return nvram_read_u32(NVCONFIG_KEYBOARD); }
/** \brief eeconfig update kb
 *
 * FIXME: needs doc
 */
void nvconfig_update_kb(uint32_t val) { nvram_update_u32(NVCONFIG_KEYBOARD, val); }

/** \brief eeconfig read user
 *
 * FIXME: needs doc
 */
uint32_t nvconfig_read_user(void) { return nvram_read_u32(NVCONFIG_USER); }
/** \brief eeconfig update user
 *
 * FIXME: needs doc
 */
void nvconfig_update_user(uint32_t val) { nvram_update_u32(NVCONFIG_USER, val); }

/** \brief eeconfig read haptic
 *
 * FIXME: needs doc
 */
uint32_t nvconfig_read_haptic(void) { return nvram_read_u32(NVCONFIG_HAPTIC); }
/** \brief eeconfig update haptic
 *
 * FIXME: needs doc
 */
void nvconfig_update_haptic(uint32_t val) { nvram_update_u32(NVCONFIG_HAPTIC, val); }

/** \brief eeconfig read split handedness
 *
 * FIXME: needs doc
 */
bool nvconfig_read_handedness(void) { return !!nvram_read_u8(NVCONFIG_HANDEDNESS); }
/** \brief eeconfig update split handedness
 *
 * FIXME: needs doc
 */
void nvconfig_update_handedness(bool val) { nvram_update_u8(NVCONFIG_HANDEDNESS, !!val); }
