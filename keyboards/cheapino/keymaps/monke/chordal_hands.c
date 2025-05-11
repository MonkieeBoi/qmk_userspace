#include QMK_KEYBOARD_H

char chordal_hold_handedness(keypos_t key) {
    if (key.col == (MATRIX_COLS - 1) / 2 || key.col == MATRIX_COLS - 1) {
        return '*';
    }
    return key.row < MATRIX_ROWS / 2 ? 'L' : 'R';
}
