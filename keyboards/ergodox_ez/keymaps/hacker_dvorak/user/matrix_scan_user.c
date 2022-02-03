#include "../leader/leader_setup.c"

bool MATRIX_SCANNED = false;

void matrix_scan_user(void) {
    if (!(MATRIX_SCANNED)) {
        rgblight_sethsv_no_nvram_green();
        MATRIX_SCANNED = true;
    }

    #include "../leader/leader_dictionary.c"
};
