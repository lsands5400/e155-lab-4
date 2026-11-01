// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// This is the header file for TIM2

#ifndef STM32L4_TIM2_H
#define STM32L4_TIM2_H

#include <stdint.h>
#include "STM32L432KC_GPIO.h"

#define TIM2_BASE (0x40000000)

typedef struct 
{
volatile uint32_t CR1;     // offset 0x00 -- Control Register 1
volatile uint32_t CR2;     // offset 0x04 -- Control Register 2
volatile uint32_t SMCR;    // offset 0x08 -- Slave Mode Control Register 
volatile uint32_t DIER;    // offset 0x0C -- DMA/Interrupt enable Register
volatile uint32_t SR;      // offset 0x10 -- Status Register
volatile uint32_t EGR;     // offset 0x14 -- Event Generation Register
volatile uint32_t CCMR1;   // offset 0x18 -- Capture/Compare Mode Register 1
volatile uint32_t CCMR2;   // offset 0x1C -- Capture/Compare Mode Register 2
volatile uint32_t CCER;    // offset 0x20 -- Capture/Compare enable Register
volatile uint32_t CNT;     // offset 0x24 -- Counter
volatile uint32_t PSC;     // offset 0x28 -- Prescaler
volatile uint32_t ARR;     // offset 0x2C -- Auto-Reload Register
uint32_t          RESERVED;// offset 0x30 -- Reserved
volatile uint32_t CCR1;    // offset 0x34 -- Capture/Compare Register 1
volatile uint32_t CCR2;    // offset 0x38 -- Capture/Compare Register 2
volatile uint32_t CCR3;    // offset 0x3C -- Capture/Compare Register 3
volatile uint32_t CCR4;    // offset 0x40 -- Capture/Compare Register 1
uint32_t          RESERVED1;// offset 0x44 -- Reserved
volatile uint32_t DCR;     // offset 0x48 -- DMA control Register
volatile uint32_t DMAR;    // offset 0x4C -- DMA Address for Full Transfer
volatile uint32_t OR1;     // offset 0x50 -- Option Register 1
uint32_t          RESERVED2;// offset 0x54 -- Reserved
uint32_t          RESERVED3;// offset 0x58 -- Reserved
uint32_t          RESERVED4;// offset 0x5C -- Reserved
volatile uint32_t OR2;     // offset 0x60 -- Option Register 2
} TIM2_TypeDef;

#define TIM2 ((TIM2_TypeDef *) TIM2_BASE)

void initTIM2(TIM2_TypeDef * tim);

#endif