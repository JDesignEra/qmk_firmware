#ifdef TAP_DANCE_ENABLE
enum tap_dances {
    TD_HOME_PGUP,
    TD_END_PGDN,
    TD_DEL_INS
};

#define TD_HOME TD(TD_HOME_PGUP)
#define TD_END TD(TD_END_PGDN)
#define TD_DEL TD(TD_DEL_INS)

tap_dance_action_t tap_dance_actions[] = {
    [TD_HOME_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_PGUP),
    [TD_END_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_PGDN),
    [TD_DEL_INS] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_INS)
};
#endif
