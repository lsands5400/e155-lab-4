// Lindsey Sands
// lsands@g.hmc.edu
// 09-28-2026
// This is the C file for TIM16

#include "STM32L432KC_TIM16.h"
#include "STM32L432KC_RCC.h"

// Base addresses for TIM16 ports
#define TIM16_BASE (0x40014400)

void initTIM16(TIM16_TypeDef * tim) {

    // Turn on bus for timer from RCC
    RCC->APB2ENR |= (1 << 17); // Enable TIM16
    // Configure counter

    // Enable proper registers
    // Prescaler
    // Enable Auto-reload
    tim->CR1 |= (1 << 7);
    // Enable Counter
    tim->CR1 |= (1 << 0);
}
