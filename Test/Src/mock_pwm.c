#include "mock_pwm.h"

static uint32_t mock_freq = 0;
static float mock_duty = 0;

void mock_pwm_setup(uint32_t frequency, float duty_cycle) {
    mock_freq = frequency;
    mock_duty = duty_cycle;
}

uint32_t mock_get_frequency(void) {
    return mock_freq;
}

float mock_get_duty_cycle(void) {
    return mock_duty;
}

const PWM_Interface Mock_PWM_Driver = {
    .setup = mock_pwm_setup,
    .get_frequency = mock_get_frequency,
    .get_duty_cycle = mock_get_duty_cycle,
};
