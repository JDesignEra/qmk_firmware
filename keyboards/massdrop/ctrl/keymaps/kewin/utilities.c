// Reset indicators
void reset_indicators_state(void) {
    led_t led_state = host_keyboard_led_state();

    if (led_state.caps_lock) {
        tap_code(KC_CAPS);
    }

    if (led_state.scroll_lock) {
        tap_code(KC_SLCK);
    }
}
