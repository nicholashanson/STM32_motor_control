#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stddef.h>

#include "pwm_interface.h"

static const PWM_Interface *pwm = NULL;

void motor_control_init(const PWM_Interface *pwm_driver);
void motor_control_set_speed(uint8_t speed_percent);

#endif