// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_RCC.h"

void configurePLL() {
    // Set clock to 80 MHz
    // Output freq = (src_clk) * (N/M) / R
    // (4 MHz) * (N/M) / R = 80 MHz
    // M: 2, N: 80, R: 2
    // Use MSI as PLLSRC

    // Turn off PLL
    RCC->CR &= ~(1<<24);
    
    // Wait till PLL is unlocked (e.g., off)
    // how do I wait? wait until bit 25 == 0
    while ((RCC->CR >> 25) & 1 != 0);

    // Load configuration
    // Set PLL SRC to MSI
    // PLLCFGR[1:0]->PLLSRC == 01
    RCC->PLLCFGR |= (1 << 0);
    RCC->PLLCFGR &= ~(1 << 1);

    // Set PLLN
    // PLLCFGR[14:8]-> 7 < PLLN < 87
    RCC->PLLCFGR &= ~(0b11111111 << 8); // Clear all bits of PLLN
    RCC->PLLCFGR |= (0b1010000 << 8);


    // Set PLLM
    // PLLCFGR[6:4]-> 1 <= PLLM <= 8
    RCC->PLLCFGR &= ~(0b111 << 4);  // Clear all bits
    RCC->PLLCFGR |= (0b010 << 4);

    // Set PLLR
    // PLLCFGR[26:25]-> PLLR = 2(00), 4(01), 6(10), 8(11)
    RCC->PLLCFGR |= (0b00 << 25);
    
    // Enable PLLR output
    RCC->PLLCFGR |= (1 << 24);

    // Enable PLL
    RCC->CR |= (1 << 24);
    
    // Wait until PLL is locked
    while ((RCC->CR >> 25) & 1 != 1);
}

void configureClock(){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));
}