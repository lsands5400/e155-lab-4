// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// This is the C file for the TIM2

#include "STM32L432KC_TIM2.h"

// Base addresses for TIM2 ports
#define TIM2_BASE (0x400003FF)

void initTIM2(TIM2_TypeDef * tim) {

    // Turn on clock for timer from RCC
    // LSE is the clock input on the TIM2_ETR pin
    TIM2->OR1 |= (1<<1); // TODO: Do I only need the TIMx_CLK?

    // Select correct clock source in TIM control

    // Disable slave mode
    TIM2->SMCR &= ~(1<<0);
    TIM2->SMCR &= ~(1<<1);
    TIM2->SMCR &= ~(1<<2);

    // Configure counter

    // Enable proper registers
    // Prescaler
    // Enable Auto-reload
    TIM2->CR1 |= (1<<7);
    // Enable Counter
    TIM2->CR1 |= (1<<0);
}
