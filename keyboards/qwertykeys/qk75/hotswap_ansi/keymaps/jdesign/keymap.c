/*
Copyright 2022 Qwertykeys

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap.h"
#include "tap_dance.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_MAIN] = LAYOUT_qk75_ansi(
		KC_ESC,  KC_F1,  KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_MPLY, KC_TRNS, KC_TRNS,
		KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC, TD_HOME,
		KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, TD_END,
		KC_CAPS, KC_A,   KC_S,    KC_D,    KC_F,     KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,  KC_INS,
		KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,           KC_UP,
		KC_LCTL,         KC_LGUI, KC_LALT,                    KC_SPC,                    KC_RALT, MAIN_FN,         KC_LEFT, KC_DOWN, KC_RGHT
	),
	[_MAIN_FN] = LAYOUT_qk75_ansi(
		AC_TOGG, AS_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_ON,   NK_OFF,  GU_TOGG, KC_PSCR, KC_MUTE, KC_TRNS, KC_TRNS,
		QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MYCM,
		KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_KP_1, KC_KP_2, KC_KP_3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WSCH,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,                            KC_RCTL, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	)
};

void keyboard_post_init_user(void) {
    autoshift_disable();
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_MAIN_FN)) {
            if (clockwise) tap_code(KC_VOLU);
            else tap_code(KC_VOLD);
        }
        else {
            if (clockwise) tap_code(KC_MNXT);
            else tap_code(KC_MPRV);
        }
    }
    return false;
}
#endif
