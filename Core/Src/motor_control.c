#include "motor_control.h"

void motor_control_init(const PWM_Interface *pwm_driver) {
    pwm = pwm_driver;
}

void motor_control_set_speed(uint8_t speed_percent) {
    if (!pwm) return; // or assert
    uint32_t freq = 1000; // example, or configurable
    float duty = (float)speed_percent / 100.0f;
    pwm->setup(freq, duty);
}