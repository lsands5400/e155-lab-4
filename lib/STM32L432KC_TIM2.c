// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// This is the C file for the TIM2

#include "STM32L432KC_TIM2.h"
#include "STM32L432KC_RCC.h"

// Base addresses for TIM2 ports
#define TIM2_BASE (0x400003FF)

void initTIM2(TIM2_TypeDef * tim) {

    // Turn on bus for timer from RCC
    RCC->APB1ENR1 |= (1 << 0); // Enable TIM2
    
    // Disable slave mode
    tim->SMCR &= ~(1<<0);
    tim->SMCR &= ~(1<<1);
    tim->SMCR &= ~(1<<2);

    // Configure counter

    // Enable proper registers
    // Prescaler
    // Enable Auto-reload
    tim->CR1 |= (1<<7);
    // Enable Counter
    tim->CR1 |= (1<<0);
}
