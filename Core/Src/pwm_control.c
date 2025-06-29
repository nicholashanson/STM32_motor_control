#include "pwm_control.h"

const PWM_Interface STM32_PWM_Driver = {
    .setup = hal_pwm_setup,
    .get_frequency = hal_get_frequency,
    .get_duty_cycle = hal_get_duty_cycle,
};

uint16_t calculate_pwm_duty_cycle(uint8_t percent, uint16_t arr) {
    if (percent > 100) percent = 100;
    return (percent * arr) / 100;
}

void hal_pwm_setup(uint32_t frequency, float duty_cycle) {

    current_freq = frequency;
    current_duty = duty_cycle;

    __HAL_RCC_TIM2_CLK_ENABLE();
    // Also enable GPIOA clock for pin PA0 (TIM2_CH1)
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure PA0 as alternate function, AF1 for TIM2_CH1
    GPIOA->MODER &= ~(3 << (0 * 2));    // Clear mode bits
    GPIOA->MODER |= (2 << (0 * 2));     // Set alternate function mode
    GPIOA->AFR[0] &= ~(0xF << (0 * 4));
    GPIOA->AFR[0] |= (1 << (0 * 4));    // AF1 for TIM2_CH1

    // Compute timer parameters
    uint32_t timer_clk = 84000000; // Example: APB1 timer clock = 84 MHz
    uint32_t arr = (timer_clk / frequency) - 1;
    uint32_t ccr = (uint32_t)((arr + 1) * duty_cycle);

    // Reset TIM2 configuration
    TIM2->PSC = 0;                   // No prescaler
    TIM2->ARR = arr;
    TIM2->CCR1 = ccr;

    // Configure PWM mode 1 on channel 1
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM2->CCMR1 |= (6 << 4); // OC1M = 110 for PWM mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Enable preload for CCR1

    // Enable capture/compare on channel 1
    TIM2->CCER |= TIM_CCER_CC1E;

    // Enable auto-reload preload
    TIM2->CR1 |= TIM_CR1_ARPE;

    // Enable counter
    TIM2->CR1 |= TIM_CR1_CEN;
}

uint32_t hal_get_frequency(void) {
    return current_freq;
}

float hal_get_duty_cycle(void) {
    return current_duty;
}
