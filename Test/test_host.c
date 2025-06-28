// test_host.c (or test_main.c)
#include "unity.h"
#include "test_motor_control.h"
#include "mock_pwm.h"   // your mock implementation

const PWM_Interface *TestPWMDriver = &Mock_PWM_Driver;

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_motor_sets_50_percent_speed);
    return UNITY_END();
}