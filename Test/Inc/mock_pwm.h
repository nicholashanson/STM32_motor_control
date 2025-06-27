#ifndef MOCK_PWM_H
#define MOCK_PWM_H

#include "pwm_interface.h"

void mock_pwm_setup(uint32_t frequency, float duty_cycle);
uint32_t mock_get_frequency(void);
float mock_get_duty_cycle(void);

extern const PWM_Interface Mock_PWM_Driver;

#endif // MOCK_PWM_H