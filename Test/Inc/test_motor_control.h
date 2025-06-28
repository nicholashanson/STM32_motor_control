// test_motor_control.h
#ifndef TEST_MOTOR_CONTROL_H
#define TEST_MOTOR_CONTROL_H

#include "unity.h"
#include "motor_control.h"
#include "pwm_interface.h"

extern const PWM_Interface *TestPWMDriver;

void test_motor_sets_50_percent_speed(void);

#endif // TEST_MOTOR_CONTROL_H