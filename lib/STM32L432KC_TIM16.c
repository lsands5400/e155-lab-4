// Lindsey Sands
// lsands@g.hmc.edu
// 09-28-2026
// This is the C file for TIM16

#include "STM32L432KC_TIM16.h"

// Base addresses for TIM16 ports
#define TIM16_BASE (0x40014400)

void initTIM16(TIM16_TypeDef * tim) {

    // Turn on clock for timer from RCC
    // LSE is the clock input on the TIM16_ETR pin
    TIM16->OR1 |= (1 << 1); // TODO: Do I only need the TIMx_CLK?

    // Select correct clock source in TIM control

    // Disable slave mode
    TIM16->SMCR &= ~(1<<0);
    TIM16->SMCR &= ~(1<<1);
    TIM16->SMCR &= ~(1<<2);

    // Configure counter

    // Enable proper registers
    // Prescaler
    // Enable Auto-reload
    TIM16->CR1 |= (1 << 7);
    // Enable Counter
    TIM16->CR1 |= (1 << 0);
}
