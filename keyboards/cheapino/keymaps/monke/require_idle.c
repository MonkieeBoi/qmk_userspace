#include QMK_KEYBOARD_H
// Edited from https://github.com/qmk/qmk_firmware/issues/24262
// Decision macro for mod-tap keys to override
#define IS_HOMEROW_MOD_TAP(kc) ( \
    IS_QK_MOD_TAP(kc) && \
    ((QK_MOD_TAP_GET_TAP_KEYCODE(kc) >= KC_A && \
    QK_MOD_TAP_GET_TAP_KEYCODE(kc) <= KC_Z) || \
    QK_MOD_TAP_GET_TAP_KEYCODE(kc) == KC_SPC))

// Decision macro for preceding trigger key
#define IS_REGULAR_KEY(k) ( \
    (!IS_QK_MOD_TAP(k)) && \
    ((uint8_t)(k) <= KC_Z) && \
    ((uint8_t)(k) >= KC_A))

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool     is_pressed[UINT8_MAX];
    static uint16_t idle_timer = 0;
    const  uint8_t  tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);

    if (record->event.pressed) {
        // Press the tap keycode if the tap-hold key follows the previous key swiftly
        if (IS_HOMEROW_MOD_TAP(keycode) && timer_elapsed(idle_timer) < QUICK_TAP_TERM) {
            is_pressed[tap_keycode] = true;
            record->keycode = tap_keycode;
            idle_timer = timer_read();
        } else if (IS_REGULAR_KEY(keycode)) {
            idle_timer = timer_read();
        }
    }

    // Release the tap keycode if pressed
    else if (is_pressed[tap_keycode]) {
        is_pressed[tap_keycode] = false;
        record->keycode = tap_keycode;
    }

    return true;
}
