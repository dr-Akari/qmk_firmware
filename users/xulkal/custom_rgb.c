#include "custom_rgb.h"

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_increase_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
                rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                rgb_matrix_set_flags(LED_FLAG_NONE);
                rgb_matrix_disable_no_nvram();
            }
            break;
        case LED_FLAG_UNDERGLOW: {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        default: {
                rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                rgb_matrix_enable_no_nvram();
            }
            break;
    }
}

void rgb_matrix_decrease_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
                rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
                rgb_matrix_set_flags(LED_FLAG_NONE);
                rgb_matrix_disable_no_nvram();
            }
            break;
        default: {
                rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                rgb_matrix_enable_no_nvram();
            }
            break;
    }
}
#endif

void rgb_reset(void) {
#if defined(RGB_MATRIX_ENABLE)
    nvconfig_update_rgb_matrix_default();
#elif defined(RGBLIGHT_ENABLE)
    nvconfig_update_rgblight_default();
    rgblight_enable();
#endif
}
