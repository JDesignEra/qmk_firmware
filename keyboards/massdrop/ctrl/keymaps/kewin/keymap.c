#include "keymap.h"

#include "utilities.c"

#ifdef RGB_MATRIX_ENABLE
#   include "rgb_func.c"
#endif

rgb_layers_t rgb_layers;
rgb_lvl_indicators_t rgb_lvl_indicators;

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                                        \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP,            \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, M_MAINF,   KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_MAIN_FN] = LAYOUT(
        _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, RGB_VAD, RGB_VAI,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, RGB_SPI, RGB_MOD, \
        _______, _______, _______, _______, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,   _______, RGB_SPD, RGB_RMOD,\
        _______, _______, _______, _______, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,                                       \
        _______, RGB_TOG, RGB_SUP, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______,          \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______  \
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
void matrix_scan_user(void) {};

void rgb_matrix_indicators_user(void) {
    led_t led_state = host_keyboard_led_state();
    led_flags_t matrix_flags = rgb_matrix_get_flags();
    uint8_t layer = biton32(layer_state);
    bool keys_flag = matrix_flags == LED_FLAG_ALL || matrix_flags == (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
    bool underglow_flag = matrix_flags == LED_FLAG_ALL || matrix_flags == LED_FLAG_UNDERGLOW;

    if (rgb_layers.timer == 0) {
        switch (layer) {
            case _MAIN_FN:
                if (keys_flag) {
                    // Alphas and Modifiers
                    for (int i = 1; i <= 3; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 5; i <= 7; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 11; i <= 12; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 31; i <= 32; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 38; i <= 39; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 48; i <= 49; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 55; i <= 56; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 64; i <= 65; i++) rgb_matrix_set_color(i, RGB_WHITE);
                    for (int i = 68; i <= 69; i++) rgb_matrix_set_color(i, RGB_WHITE);
                }

                if (underglow_flag) {
                    rgb_matrix_set_underglow(RGB_WHITE);
                }
                break;
        }

        // Indicators LED
        if (led_state.caps_lock) {
            keys_flag ? rgb_matrix_set_color(50, RGB_WHITE) : rgb_matrix_set_color(50, 0, 0, 0);
        }

        if (led_state.scroll_lock) {
            keys_flag ? rgb_matrix_set_color(14, RGB_WHITE) : rgb_matrix_set_color(14, 0 ,0, 0);
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
