// test_motor_control.c
#include "test_motor_control.h"

extern const PWM_Interface *TestPWMDriver;  // Use external pointer

void setUp(void) {
    motor_control_init(TestPWMDriver);  // Inject interface before each test
}

void tearDown(void) {}

void test_motor_sets_50_percent_speed(void) {
    motor_control_set_speed(50);

    TEST_ASSERT_EQUAL_UINT32(1000, TestPWMDriver->get_frequency());
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.5f, TestPWMDriver->get_duty_cycle());
}


