// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// This is the C file for the TIM2

#include "STM32L432KC_TIM2.h"
#include "STM32L432KC_RCC.h"

void initTIM2(TIM2_TypeDef * tim) {

    // Turn on bus for timer from RCC
    RCC->APB1ENR1 |= (1 << 0); // Enable TIM2
    
    // Disable slave mode
    TIM2->SMCR &= ~(0b111<<0);

    // Configure counter

    // Enable proper registers
    // Prescaler
    // Enable Auto-reload
    TIM2->CR1 |= (1<<7);
    // Enable Counter
    TIM2->CR1 |= (1<<0);
}
