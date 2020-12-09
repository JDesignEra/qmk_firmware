// Attempt to set RGB speed as close as pssible to targeted value
uint8_t rgb_matrix_set_speed(uint8_t curr_spd, uint8_t set_spd) {
    if (curr_spd != set_spd) {
        if (curr_spd < set_spd) {
            while (curr_spd < set_spd) {
                rgb_matrix_increase_speed();
                curr_spd = rgb_matrix_get_speed();
            }
        }
        else {
            while (curr_spd > set_spd) {
                rgb_matrix_decrease_speed();
                curr_spd = rgb_matrix_get_speed();
            }

        }
    }

    return curr_spd;
}

// Attempt to set RGB value as close as pssible to targeted value
uint8_t rgb_matrix_set_val(uint8_t curr_val, uint8_t set_val) {
    if (curr_val != set_val) {
        if (curr_val < set_val) {
            while (curr_val < set_val) {
                rgb_matrix_increase_val();
                curr_val = rgb_matrix_get_val();
            }
        }
        else {
            while (curr_val > set_val) {
                rgb_matrix_decrease_val();
                curr_val = rgb_matrix_get_val();
            }

        }
    }

    return curr_val;
}

// Set underglow LED
void rgb_matrix_set_underglow(uint8_t r, uint8_t g, uint8_t b) {
    for (size_t i = 87; i <= 118; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
}

// Set LED to show RGB speed or value level (max 15 level)
void rgb_matrix_set_lvl_indicators(uint8_t lvl) {
    uint8_t max_lvl = RGB_MATRIX_MAXIMUM_BRIGHTNESS / RGB_MATRIX_VAL_STEP;

    for (int i = 0; i <= lvl; i++) {
        rgb_matrix_set_color(i, RGB_GREEN);
    }

    for (int i = lvl + 1; i <= max_lvl; i++) {
        rgb_matrix_set_color(i, RGB_ORANGE);
    }
}
