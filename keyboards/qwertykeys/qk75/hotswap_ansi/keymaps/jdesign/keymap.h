#pragma once
#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _MAIN_FN
};

#define MAIN_FN MO(_MAIN_FN)
