#include "unity.h"
#include "pwm_control.h"

void setUp(void) {}
void tearDown(void) {}

void test_calculate_pwm_duty_cycle_zero(void) {
    TEST_ASSERT_EQUAL_UINT16(0, calculate_pwm_duty_cycle(0, 999));
}

void test_calculate_pwm_duty_cycle_half(void) {
    TEST_ASSERT_EQUAL_UINT16(500, calculate_pwm_duty_cycle(50, 1000));
}

void test_calculate_pwm_duty_cycle_full(void) {
    TEST_ASSERT_EQUAL_UINT16(1000, calculate_pwm_duty_cycle(100, 1000));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_calculate_pwm_duty_cycle_zero);
    RUN_TEST(test_calculate_pwm_duty_cycle_half);
    RUN_TEST(test_calculate_pwm_duty_cycle_full);
    return UNITY_END();
}
