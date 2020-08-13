#pragma once
#include QMK_KEYBOARD_H

enum jdesign_layers {
    _MAIN,
    _MAIN_FN,
    _CODE,
    _CODE_FN,
};

enum jdesign_keycodes {
    U_T_AUTO = SAFE_RANGE,  // USB Extra Port Toggle Auto Detect / Always Active
    MD_BOOT,                // Restart into bootloader after hold timeout
    TO_MAIN,                // Move to _MAIN layer
    TO_CODE,                // Move to _CODE layer
    GUI_TOG,                // Enable / Disable GUI (Win Lock)
    PC_WAKE,                // Prevent PC going into sleep mode
    RGB_SUP,                // Suspend RGB Lights
};

#define WIN_DEL LGUI(KC_DEL)

#define M_MAINF MO(_MAIN_FN)
#define M_CODEF MO(_CODE_FN)

keymap_config_t keymap_config;

typedef struct {
    bool flag;
    uint16_t timer;
    uint16_t mins;
    uint16_t interval;
} pc_wake_t;

typedef struct {
    uint16_t timer;
    uint8_t main[3];    // mode, speed, value
    uint8_t code[3];    // mode, speed, value
} rgb_layers_t;

typedef struct {
    uint8_t lvl;
    uint16_t timer;
} rgb_lvl_indicators_t;

extern pc_wake_t pc_wake;
extern rgb_layers_t rgb_layers;
extern rgb_lvl_indicators_t rgb_lvl_indicators;
