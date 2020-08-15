#include "keymap.h"

#ifdef CONSOLE_ENABLE
#   include <print.h>
#endif

#include "utilities.c"

#ifdef TAP_DANCE_ENABLE
#   include "tap_dances.c"
#endif
#ifdef RGB_MATRIX_ENABLE
#   include "rgb_func.c"
#endif

pc_wake_t pc_wake;
rgb_layers_t rgb_layers;
rgb_lvl_indicators_t rgb_lvl_indicators;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_MPRV, TD_MPSM, KC_MNXT, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        TD_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                                        \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                               KC_UP,           \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, M_MAINF, KC_MYCM, KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_MAIN_FN] = LAYOUT(
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, PC_WAKE,            KC_PSCR, KC_SLCK, KC_PAUS, \
        TO_CODE, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, KC_VOLU, \
        _______, RGB_SPD,  RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,   WIN_DEL, KC_CALC, KC_VOLD, \
        _______, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,                                       \
        _______, RGB_TOG,  RGB_SUP, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______,          \
        _______, GUI_TOG,  _______,                   _______,                            _______, _______, KC_APP,  _______,            _______, _______, _______  \
    ),
    [_CODE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_MPRV, TD_MPSM, KC_MNXT, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_ENT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                                        \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,                              KC_UP,            \
        KC_LCPO, KC_LGUI, KC_LAPO,                   KC_SPC,                             KC_RAPC, M_CODEF, KC_MYCM, KC_RCPC,            KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_CODE_FN] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, PC_WAKE,            KC_PSCR, KC_SLCK, KC_PAUS, \
        TO_MAIN, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,   _______, _______, KC_VOLU, \
        _______, _______, _______, _______, _______, _______, _______, RGB_SPD,  RGB_VAI, RGB_SPI, _______, _______, _______, _______,   WIN_DEL, KC_CALC, KC_VOLD, \
        _______, _______, _______, _______, _______, _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______, _______,                                       \
        _______, RGB_TOG, RGB_SUP, _______, _______, MD_BOOT, _______, _______,  _______, _______, _______, _______,                               _______,         \
        _______, GUI_TOG, _______,                   _______,                            _______, _______, KC_APP,  _______,            _______,  _______, _______  \
    ),
};

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    pc_wake.flag = false;
    pc_wake.timer = 0;
    pc_wake.mins = 0;
    pc_wake.interval = 0;

    rgb_layers.timer = 0;

    rgb_layers.main[0] = RGB_MATRIX_RAINBOW_MOVING_CHEVRON;
    rgb_layers.main[1] = RGB_MATRIX_STARTUP_SPD;
    rgb_layers.main[2] = rgb_matrix_get_val();

    rgb_layers.code[0] = RGB_MATRIX_CYCLE_OUT_IN;
    rgb_layers.code[1] = 68;
    rgb_layers.code[2] = rgb_matrix_get_val();

    rgb_lvl_indicators.lvl = 0;
    rgb_lvl_indicators.timer = 0;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    if (pc_wake.flag) {
        if (timer_elapsed(pc_wake.timer) >= 60000) {
            pc_wake.mins++;
            pc_wake.timer = timer_read();
        }

        if (pc_wake.mins >= 55) {
            tap_code(KC_MS_L);

            pc_wake.interval = timer_read();
            pc_wake.mins = 0;
            pc_wake.timer = timer_read();
        }

        if (pc_wake.interval != 0 && timer_elapsed(pc_wake.interval) >= MK_C_INTERVAL_UNMOD) {
            tap_code(KC_MS_R);
            pc_wake.interval = 0;
        }
    }
};

void rgb_matrix_indicators_user(void) {
    led_t led_state = host_keyboard_led_state();
    led_flags_t matrix_flags = rgb_matrix_get_flags();
    uint8_t layer = biton32(layer_state);
    bool keys_flag = matrix_flags == LED_FLAG_ALL || matrix_flags == (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
    bool underglow_flag = matrix_flags == LED_FLAG_ALL || matrix_flags == LED_FLAG_UNDERGLOW;

    if (rgb_layers.timer == 0) {
        switch (layer) {
            case _CODE:
                if (underglow_flag) {
                    rgb_matrix_set_underglow(RGB_WHITE);
                }
                break;

            case _MAIN_FN:
                if (keys_flag) {
                    // Alphas and Modifiers
                    for (size_t i = 12; i <= 16; i++) {
                        rgb_matrix_set_color(i, RGB_TEAL);
                    }

                    rgb_matrix_set_color(32, RGB_TEAL);

                    for (size_t i = 34; i <= 38; i++) {
                        rgb_matrix_set_color(i, RGB_TEAL);
                    }

                    for (size_t i = 47; i <= 49; i++) {
                        rgb_matrix_set_color(i, RGB_TEAL);
                    }

                    for (size_t i = 51; i <= 55; i++) {
                        rgb_matrix_set_color(i, RGB_TEAL);
                    }

                    rgb_matrix_set_color(64, RGB_TEAL);
                    rgb_matrix_set_color(65, RGB_TEAL);
                    rgb_matrix_set_color(68, RGB_TEAL);
                    rgb_matrix_set_color(69, RGB_TEAL);
                    rgb_matrix_set_color(77, RGB_TEAL);
                    rgb_matrix_set_color(82, RGB_TEAL);
                }

                if (underglow_flag) {
                    rgb_matrix_set_underglow(RGB_TEAL);
                }
                break;

            case _CODE_FN:
                if (keys_flag) {
                    // Alphas and Modifiers
                    for (int i = 12; i <= 16; i++) {
                        rgb_matrix_set_color(i, RGB_WHITE);
                    }

                    rgb_matrix_set_color(32, RGB_WHITE);

                    for (int i = 40; i <= 42; i++) {
                        rgb_matrix_set_color(i, RGB_WHITE);
                    }

                    for (int i = 47; i <= 49; i++) {
                        rgb_matrix_set_color(i, RGB_WHITE);
                    }

                    for (int i = 57; i <= 59; i++) {
                        rgb_matrix_set_color(i, RGB_WHITE);
                    }

                    rgb_matrix_set_color(64, RGB_WHITE);
                    rgb_matrix_set_color(65, RGB_WHITE);
                    rgb_matrix_set_color(68, RGB_WHITE);
                    rgb_matrix_set_color(77, RGB_WHITE);
                }

                if (underglow_flag) {
                    rgb_matrix_set_underglow(RGB_WHITE);
                }
                break;
        }

        // Indicators LED
        if (layer != _MAIN && layer != _CODE) {
            if (led_state.caps_lock) {
                keys_flag ? rgb_matrix_set_color(50, RGB_RED) : rgb_matrix_set_color(50, 0, 0, 0);
            }
        }

        if (led_state.scroll_lock) {
            keys_flag ? rgb_matrix_set_color(14, RGB_RED) : rgb_matrix_set_color(14, 0 ,0, 0);
        }

        if (keymap_config.no_gui) {
            keys_flag ? rgb_matrix_set_color(77, RGB_RED) : rgb_matrix_set_color(77, 0, 0, 0);
        }

        if (pc_wake.flag) {
            keys_flag ? rgb_matrix_set_color(12, RGB_RED) : rgb_matrix_set_color(12, 0, 0, 0);
        }

        // RGB speed or value indicator (Max up to 15 lvl)
        if (rgb_lvl_indicators.timer != 0) {
            if (timer_elapsed(rgb_lvl_indicators.timer) <= 1500) {
                rgb_matrix_set_lvl_indicators(rgb_lvl_indicators.lvl);
            }
            else {
                rgb_lvl_indicators.timer = 0;
            }
        }
    }
    else if (timer_elapsed(rgb_layers.timer) >= 3000){  // If _MAIN or _CODE rgb mode just changed
        rgb_layers.timer = 0;
    }
}

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
// #define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read();
            }
            else {
                if (timer_elapsed(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case TO_MAIN:
            if (record->event.pressed) {
                reset_indicators_state();
                layer_move(_MAIN);
            }
            return false;
        case TO_CODE:
            if (record->event.pressed) {
                reset_indicators_state();
                layer_move(_CODE);
            }
            return false;
        case GUI_TOG:
            if (record->event.pressed) {
                keymap_config.no_gui = !keymap_config.no_gui;
            }
            return false;
        case PC_WAKE:
            if (record->event.pressed) {
                toggle_pc_wake();
            }
            return false;
        case RGB_SUP:
            if (record->event.pressed) {
                suspend_power_down_user();
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                        rgb_matrix_set_color_all(0, 0, 0);
                        break;

                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER:
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                        break;

                    case LED_FLAG_UNDERGLOW:
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                        break;

                    default:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                        break;
                }
            }
            return false;
        case RGB_MOD:
        case RGB_RMOD:
            if (record->event.pressed) {
                switch (biton32(layer_state)) {
                    case _MAIN_FN:
                        rgb_matrix_mode(rgb_layers.main[0]);
                        keycode == RGB_MOD ? rgb_matrix_step() : rgb_matrix_step_reverse();
                        rgb_layers.main[0] = rgb_matrix_get_mode();
                        break;

                    case _CODE_FN:
                        rgb_matrix_mode(rgb_layers.code[0]);
                        keycode == RGB_MOD ? rgb_matrix_step() : rgb_matrix_step_reverse();
                        rgb_layers.code[0] = rgb_matrix_get_mode();
                        break;

                    default:
                        keycode == RGB_MOD ? rgb_matrix_step() : rgb_matrix_step_reverse();
                        break;
                }

                rgb_layers.timer = timer_read();
            }
            return false;
        case RGB_SPI:
        case RGB_SPD:
            if (record->event.pressed) {
                uint8_t layer = biton32(layer_state);
                uint8_t rgb_spd = rgb_matrix_get_speed();

                switch (layer) {
                    case _MAIN_FN:
                        rgb_spd = rgb_matrix_set_speed(rgb_spd, rgb_layers.main[1]);
                        keycode == RGB_SPI ? rgb_matrix_increase_speed() : rgb_matrix_decrease_speed();
                        rgb_layers.main[1] = rgb_matrix_get_speed();
                        break;

                    case _CODE_FN:
                        rgb_spd = rgb_matrix_set_speed(rgb_spd, rgb_layers.code[1]);
                        keycode == RGB_SPI ? rgb_matrix_increase_speed() : rgb_matrix_decrease_speed();
                        rgb_layers.code[1] = rgb_matrix_get_speed();
                        break;

                    default:
                        keycode == RGB_SPI ? rgb_matrix_increase_speed() : rgb_matrix_decrease_speed();
                        break;
                }

                rgb_lvl_indicators.lvl = rgb_matrix_get_speed() / RGB_MATRIX_SPD_STEP;
                rgb_lvl_indicators.timer = layer == _MAIN_FN || layer == _CODE_FN ? timer_read() : 0;
            }
            return false;
        case RGB_VAI:
        case RGB_VAD:
            if (record->event.pressed) {
                uint8_t layer = biton32(layer_state);
                uint8_t rgb_val = rgb_matrix_get_val();

                switch (layer) {
                    case _MAIN_FN:
                        rgb_val = rgb_matrix_set_val(rgb_val, rgb_layers.main[2]);
                        keycode == RGB_VAI ? rgb_matrix_increase_val() : rgb_matrix_decrease_val();
                        rgb_layers.main[2] = rgb_matrix_get_val();
                        break;

                    case _CODE_FN:
                        rgb_val = rgb_matrix_set_val(rgb_val, rgb_layers.code[2]);
                        keycode == RGB_VAI ? rgb_matrix_increase_val() : rgb_matrix_decrease_val();
                        rgb_layers.code[2] = rgb_matrix_get_val();
                        break;

                    default:
                        keycode == RGB_VAI ? rgb_matrix_increase_val() : rgb_matrix_decrease_val();
                        break;
                }

                rgb_lvl_indicators.lvl = rgb_matrix_get_val() / RGB_MATRIX_VAL_STEP;
                rgb_lvl_indicators.timer = layer == _MAIN_FN || layer == _CODE_FN ? timer_read() : 0;
            }
            return false;
        default:
            if (record->event.pressed) {
                suspend_wakeup_init_user();
            }
            return true; //Process all other keycodes normally
    }
}

// Layer State
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t rgb_mode = RGB_MATRIX_SPLASH;
    uint8_t rgb_spd = rgb_matrix_get_speed();
    uint8_t rgb_set_spd = RGB_MATRIX_STARTUP_SPD;
    uint8_t rgb_val = rgb_matrix_get_val();
    uint8_t rgb_set_val = RGB_MATRIX_STARTUP_VAL;

    switch (get_highest_layer(state)) {
        case _MAIN:
            rgb_lvl_indicators.timer = 0;
            rgb_layers.timer = 0;
            rgb_mode = rgb_layers.main[0];
            rgb_set_spd = rgb_layers.main[1];
            rgb_set_val = rgb_layers.main[2];
            break;

        case _CODE:
            rgb_lvl_indicators.timer = 0;
            rgb_layers.timer = 0;
            rgb_mode = rgb_layers.code[0];
            rgb_set_spd = rgb_layers.code[1];
            rgb_set_val = rgb_layers.code[2];
            break;
    }

    rgb_spd = rgb_matrix_set_speed(rgb_spd, rgb_set_spd);
    rgb_val = rgb_matrix_set_val(rgb_val, rgb_set_val);

    rgb_matrix_mode(rgb_mode);

    return state;
}
