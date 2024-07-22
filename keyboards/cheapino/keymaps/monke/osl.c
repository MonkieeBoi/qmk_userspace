#include QMK_KEYBOARD_H

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if ((IS_QK_ONE_SHOT_MOD(keycode) || IS_MODIFIER_KEYCODE(keycode)) && is_oneshot_layer_active() && record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
    return;
}
