// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// This is the C file for the TIM2

#include "STM32L432KC_TIM2.h"
#include "STM32L432KC_RCC.h"

// Base addresses for TIM2 ports
#define TIM2_BASE (0x400003FF)

void initTIM2(TIM2_TypeDef *tim) {

    // Enable TIM2 clock
    RCC->APB1ENR1 |= (1 << 0);

    // Disable timer
    tim->CR1 &= ~(1 << 0);

    // Enable ARR preload
    tim->CR1 |= (1 << 7);

    // Configure PWM prescaler
    tim->PSC = 7;

    // Initialize ARR and counter
    tim->ARR = 9999;
    tim->CNT = 0;

    // Generate update event
    tim->EGR |= (1 << 0);

    // Clear status register
    tim->SR = 0;
}