#pragma once
#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _MAIN_FN
};

enum keycodes {
    GUI_TO,
    LGUI_F13
};

struct bef_gui_off_state {
    bool autoshift;
    bool autocorrect;
} bef_gui_off_state;

#define MAIN_FN MO(_MAIN_FN)
