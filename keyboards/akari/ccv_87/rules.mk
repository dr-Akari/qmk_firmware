# This file intentionally left blank
# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#

# for WPM Bongocat animation loop
WPM_ENABLE = yes
# Enabling OLED, defaulting to SSD1306
OLED_ENABLE = yes
OLED_DRIVER = SSD1306


POINTING_DEVICE_ENABLE = yes # Enable Pimoroni Trackball
POINTING_DEVICE_DRIVER = pimoroni_trackball

ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes # i want to subsequently enable encoder as well


BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes
SPACE_CADET_ENABLE = no           # Enable N-Key Rollover
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
AVR_USE_MINIMAL_PRINTF = yes


BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no       # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
VIA_ENABLE = yes


LTO_ENABLE = yes
