// pwm_interface.h
#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

#include <stdint.h>

typedef struct {
    void (*setup)(uint32_t frequency, float duty_cycle);
    uint32_t (*get_frequency)(void);
    float (*get_duty_cycle)(void);
} PWM_Interface;

#endif