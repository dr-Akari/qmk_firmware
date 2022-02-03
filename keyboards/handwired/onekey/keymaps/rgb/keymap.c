#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(RGB_MOD)
};

void keyboard_post_init_user(void) {
    rgblight_enable_no_nvram();
    rgblight_sethsv_no_nvram_cyan();
    rgblight_mode_no_nvram(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
