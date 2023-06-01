#ifdef RGB_MATRIX_ENABLE
#include "lib/lib8tion/lib8tion.h"

void rgb_matrix_helper(uint8_t index, uint8_t mode, uint8_t hue, uint8_t sat, uint8_t val, uint8_t speed, uint8_t led_min, uint8_t led_max) {
    HSV hsv = {hue, sat, val};

    if (hsv.v > rgb_matrix_get_val()) hsv.v = rgb_matrix_get_val();

    switch (mode) {
        case 1:  {  // Breathing
            uint16_t time = scale16by8(g_rgb_timer, speed / 8);
            hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb = hsv_to_rgb(hsv);

            RGB_MATRIX_INDICATOR_SET_COLOR(index, rgb.r, rgb.g, rgb.b);

            break;
        }

        default: {
            RGB rgb = hsv_to_rgb(hsv);
            RGB_MATRIX_INDICATOR_SET_COLOR(index, rgb.r, rgb.g, rgb.b);

            break;
        }
    }
}
#endif
