#ifdef TAP_DANCE_ENABLE
enum tap_dances {
    TD_CAPS_MO_MAIN_FN
};

#define TD_CAPS TD(TD_CAPS_MO_MAIN_FN)

void td_mo_main_fn_caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state -> count == 1) layer_on(_MAIN_FN);
    else tap_code(KC_CAPS);
}

void td_mo_main_fn_caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state -> count == 1) layer_off(_MAIN_FN);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS_MO_MAIN_FN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mo_main_fn_caps_finished, td_mo_main_fn_caps_reset)
};
#endif
