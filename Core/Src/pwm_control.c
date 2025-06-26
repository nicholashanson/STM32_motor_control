#include "pwm_control.h"

uint16_t calculate_pwm_duty_cycle(uint8_t percent, uint16_t arr) {
    if (percent > 100) percent = 100;
    return (percent * arr) / 100;
}
