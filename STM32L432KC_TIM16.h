// Lindsey Sands
// lsands@g.hmc.edu
// 09-28-2026
// This is the header file for TIM16

#ifndef STM32L4_TIM16_H
#define STM32L4_TIM16_H

#include <stdint.h>
#include "STM32L432KC_GPIO.h"

#define TIM16_BASE (0x40014400)

typedef struct 
{
volatile uint32_t CR1;     // offset 0x00 -- Control Register 1
volatile uint32_t CR2;     // offset 0x04 -- Control Register 2
uint32_t          RESERVED;// offset 0x08 -- Reserved
volatile uint32_t DIER;    // offset 0x0C -- DMA/Interrupt enable Register
volatile uint32_t SR;      // offset 0x10 -- Status Register
volatile uint32_t EGR;     // offset 0x14 -- Event Generation Register
volatile uint32_t CCMR1;   // offset 0x18 -- Capture/Compare Mode Register 1
uint32_t          RESERVED1;// offset 0x1C -- Reserved
volatile uint32_t CCER;    // offset 0x20 -- Capture/Compare enable Register
volatile uint32_t CNT;     // offset 0x24 -- Counter
volatile uint32_t PSC;     // offset 0x28 -- Prescaler
volatile uint32_t ARR;     // offset 0x2C -- Auto-Reload Register
volatile uint32_t RCR;     // offset 0x30 -- TODO:Fill in
volatile uint32_t CCR1;    // offset 0x34 -- Capture/Compare Register 1
uint32_t          RESERVED2;// offset 0x38 -- Reserved
uint32_t          RESERVED3;// offset 0x3C -- Reserved
uint32_t          RESERVED4;// offset 0x40 -- Reserved
volatile uint32_t BTDR;    // offset 0x44 -- TODO: Fill in
volatile uint32_t DCR;     // offset 0x48 -- DMA control Register
volatile uint32_t DMAR;    // offset 0x4C -- DMA Address for Full Transfer
volatile uint32_t OR1;     // offset 0x50 -- Option Register 1
uint32_t          RESERVED5;// offset 0x54 -- Reserved
uint32_t          RESERVED6;// offset 0x58 -- Reserved
uint32_t          RESERVED7;// offset 0x5C -- Reserved
volatile uint32_t OR2;     // offset 0x60 -- Option Register 2
} TIM16_TypeDef;

#define TIM16 ((TIM16_TypeDef *) TIM16_BASE)

void initTIM16(TIM16_TypeDef * tim);

#endif