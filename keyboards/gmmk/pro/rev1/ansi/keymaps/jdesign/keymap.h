#pragma once
#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _MAIN_FN
};

enum keycodes { G_RESET };

#define MAIN_FN MO(_MAIN_FN)
