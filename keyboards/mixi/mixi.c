#include "mixi.h"

void nvconfig_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable(); // Enable RGB underglow by default
    rgblight_sethsv(0, 255, 255);
#ifdef RGBLIGHT_ANIMATIONS
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5); // Set to RGB_RAINBOW_SWIRL animation by default
#endif
#endif

    nvconfig_update_kb(0);
    nvconfig_init_user();
}
