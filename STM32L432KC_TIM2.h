// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// This is the header file for the SysTick struct, 
// giving all the addresses for the ports
#include <stdint.h>

typedef struct 
{
volatile uint32_t TIM2_CR1;     // offset 0x00 -- Control Register 1
volatile uint32_t TIM2_CR2;     // offset 0x04 -- Control Register 2
volatile uint32_t TIM2_SMCR;    // offset 0x08 -- Slave Mode Control Register 
volatile uint32_t TIM2_DIER;    // offset 0x0C -- DMA/Interrupt enable Register
volatile uint32_t TIM2_SR;      // offset 0x10 -- Status Register
volatile uint32_t TIM2_EGR;     // offset 0x14 -- Event Generation Register
volatile uint32_t TIM2_CCMR1;   // offset 0x18 -- Capture/Compare Mode Register 1
volatile uint32_t TIM2_CCMR2;   // offset 0x1C -- Capture/Compare Mode Register 2
volatile uint32_t TIM2_CCER;    // offset 0x20 -- Capture/Compare enable Register
volatile uint32_t TIM2_CNT;     // offset 0x24 -- Counter
volatile uint32_t TIM2_PSC;     // offset 0x28 -- Prescaler
volatile uint32_t TIM2_ARR;     // offset 0x2C -- Auto-Reload Register
volatile uint32_t TIM2_CCR1;    // offset 0x34 -- Capture/Compare Register 1
volatile uint32_t TIM2_CCR2;    // offset 0x38 -- Capture/Compare Register 2
volatile uint32_t TIM2_CCR3;    // offset 0x3C -- Capture/Compare Register 3
volatile uint32_t TIM2_CCR4;    // offset 0x40 -- Capture/Compare Register 1
volatile uint32_t TIM2_DCR;     // offset 0x48 -- DMA control Register
volatile uint32_t TIM2_DMAR;    // offset 0x4C -- DMA Address for Full Transfer
volatile uint32_t TIM2_OR1;     // offset 0x50 -- Option Register 1
volatile uint32_t TIM2_OR2;     // offset 0x60 -- Option Register 2
} TIM2_TypeDef;

void initSysTick(TIM2_TypeDef * TIM2);

void delay_millis(TIM2_TypeDef * TIM2, uint32_t ms);
