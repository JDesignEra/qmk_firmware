#ifdef TAP_DANCE_ENABLE
enum tap_dances {
    TD_HOME_PGUP,
    TD_END_PGDN
};

#define TD_HOME TD(TD_HOME_PGUP)
#define TD_END TD(TD_END_PGDN)

tap_dance_action_t tap_dance_actions[] = {
    [TD_HOME_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_PGUP),
    [TD_END_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_PGDN)
};
#endif
