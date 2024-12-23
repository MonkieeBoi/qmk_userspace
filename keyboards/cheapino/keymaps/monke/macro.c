#include QMK_KEYBOARD_H

#define SYM_LAYER 5

enum custom_keycodes {
    SYM_OSL = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYM_OSL:
            if (record->event.pressed) {
                set_oneshot_layer(SYM_LAYER, ONESHOT_START);
                set_oneshot_mods(MOD_BIT(KC_LSFT));
            }
            break;
        default:
            if (!record->event.pressed && is_oneshot_layer_active())
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
    }
    return true;
}
