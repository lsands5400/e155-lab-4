// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// This is the C file for the TIM2 struct, 
// giving all the addresses for the ports

#include "STM32L432KC_TIM2.h"

// Base addresses for TIM2 ports
#define TIM2_BASE (0x400003FF)
// Define addresses to send data to
#define TIM2_CR1    ((TIM2_TypeDef *) (TIM2_BASE + 0x00))
#define TIM2_SMCR   ((TIM2_TypeDef *) (TIM2_BASE + 0x08))
#define TIM2_CNT    ((TIM2_TypeDef *) (TIM2_BASE + 0x24))
#define TIM2_PSC    ((TIM2_TypeDef *) (TIM2_BASE + 0x28))
#define TIM2_ARR    ((TIM2_TypeDef *) (TIM2_BASE + 0x2C))
#define TIM2_OR1    ((TIM2_TypeDef *) (TIM2_BASE + 0x50))


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

void delay_millis(TIM2_TypeDef * tim, uint32_t ms) {
    // TODO: How do I do the delay?
}
