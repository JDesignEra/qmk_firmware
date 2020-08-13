enum jdesign_tap_dances {
    TD_MPLY_MSTP_MUTE,
    TD_CAPS_MO_MAIN_FN,
    TD_SFT_LPRN,
    TD_CTL_LBRC,
    TD_ALT_LCBR,
};

#define TD_MPSM     TD(TD_MPLY_MSTP_MUTE)
#define TD_CAPS     TD(TD_CAPS_MO_MAIN_FN)
#define TD_LSFT     TD(TD_SFT_LPRN)
#define TD_LCTL     TD(TD_CTL_LBRC)
#define TD_LALT     TD(TD_ALT_LCBR)
#define TD_TAB      TD(TD_TAB_LT)

void td_mply_mstp_mute(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_MPLY);
            break;
        case 2:
            tap_code(KC_MSTP);
            break;
        default:
            tap_code(KC_MUTE);
            break;
    }
}

void td_mo_main_fn_caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(_MAIN_FN);
    }
    else {
        tap_code(KC_CAPS);
    }
}

void td_mo_main_fn_caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_off(_MAIN_FN);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MPLY_MSTP_MUTE]     = ACTION_TAP_DANCE_FN(td_mply_mstp_mute),
    [TD_CAPS_MO_MAIN_FN]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mo_main_fn_caps_finished, td_mo_main_fn_caps_reset),
    [TD_SFT_LPRN]           = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LPRN),
    [TD_CTL_LBRC]           = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LBRC),
    [TD_ALT_LCBR]           = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LCBR),
};
