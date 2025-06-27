#include "pwm_control.h"

uint16_t calculate_pwm_duty_cycle(uint8_t percent, uint16_t arr) {
    if (percent > 100) percent = 100;
    return (percent * arr) / 100;
}

void hal_pwm_setup(uint32_t frequency, float duty_cycle) {
    current_freq = frequency;
    current_duty = duty_cycle;
}

uint32_t hal_get_frequency(void) {
    return current_freq;
}

float hal_get_duty_cycle(void) {
    return current_duty;
}
