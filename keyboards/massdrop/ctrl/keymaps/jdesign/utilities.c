// Toggle PC Wake
void toggle_pc_wake(void) {
    pc_wake.flag = !pc_wake.flag;
    pc_wake.timer = pc_wake.flag ? timer_read() : 0;
    pc_wake.mins = 0;
    pc_wake.interval = 0;
}

// Reset indicators
void reset_indicators_state(void) {
    led_t led_state = host_keyboard_led_state();

    if (led_state.caps_lock) {
        tap_code(KC_CAPS);
    }

    if (led_state.scroll_lock) {
        tap_code(KC_SLCK);
    }

    if (keymap_config.no_gui) {
        keymap_config.no_gui = !keymap_config.no_gui;
    }

    if (pc_wake.flag) {
        toggle_pc_wake();
    }
}
