#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
    rgblight_enable_no_nvram();
    rgblight_mode_no_nvram(RGBLIGHT_MODE_RGB_TEST);
}
