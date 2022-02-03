#include "mattly.h"

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

static uint16_t current_state = 0;

void set_lights_default(void) {
    #ifdef RGBLIGHT_ENABLE
        if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            rgblight_sethsv_no_nvram(HSV_CAPS);
        } else {
            if (current_state == _BASE_MAC) {
                rgblight_sethsv_no_nvram(HSV_MAC);
            } else if (current_state == _OVER_WIN) {
                rgblight_sethsv_no_nvram(HSV_WIN);
            }
        }
    #endif
}

void layer_state_set_rgb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
        case _SYMBOL:
            rgblight_sethsv_no_nvram(HSV_SYMBOL);
            break;
        case _NAVNUM:
        case _NAVNUM_WIN:
            rgblight_sethsv_no_nvram(HSV_NAVNUM);
            break;
        case _FUNCT:
        case _FUNCT_WIN:
            rgblight_sethsv_no_nvram(HSV_FUNCT);
            break;
        default:
            set_lights_default();
    }
#endif
}

layer_state_t layer_state_set_user (layer_state_t state) {
  state = update_tri_layer_state(state, _SYMBOL, _NAVNUM, _FUNCT);
  state = update_tri_layer_state(state, _OVER_WIN, _NAVNUM, _NAVNUM_WIN);
  state = update_tri_layer_state(state, _OVER_WIN, _FUNCT, _FUNCT_WIN);
  current_state = get_highest_layer(state);
  layer_state_set_rgb(state);
  return layer_state_set_keymap (state);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            #ifdef RGBLIGHT_ENABLE
            set_lights_default();
            #endif
            return true;
        case RESET:
            #ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_no_nvram(HSV_RESET);
            #endif
            return true;
        default:
            return true;
    }
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_no_nvram();
    set_lights_default();
#endif
}
