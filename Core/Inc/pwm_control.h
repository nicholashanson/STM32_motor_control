#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include "pwm_interface.h"

static uint32_t current_freq = 0;
static float current_duty = 0;

uint16_t calculate_pwm_duty_cycle(uint8_t percent, uint16_t arr);

void hal_pwm_setup(uint32_t frequency, float duty_cycle);
uint32_t hal_get_frequency(void);
float hal_get_duty_cycle(void);

extern const PWM_Interface STM32_PWM_Driver;

#endif // PWM_CONTROL_H