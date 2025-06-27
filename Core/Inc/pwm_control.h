#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include <stdint.h>

static uint32_t current_freq = 0;
static float current_duty = 0.0f;

uint16_t calculate_pwm_duty_cycle(uint8_t percent, uint16_t arr);
void PWM_Setup(uint32_t frequency, float duty_cycle);
uint32_t PWM_GetFrequency(void);
float PWM_GetDutyCycle(void);

#endif // PWM_CONTROL_H
