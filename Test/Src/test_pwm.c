#include "test_pwm.h"

void test_hal_pwm_setup_configures_timer_correctly(void) {
    hal_pwm_setup(1000, 0.5f); 
    TEST_ASSERT_EQUAL_UINT32(71999, TIM1->ARR);
    TEST_ASSERT_UINT32_WITHIN(5, 36000, TIM1->CCR1);
    TEST_ASSERT_BITS_HIGH(TIM_CR1_CEN, TIM1->CR1);
}