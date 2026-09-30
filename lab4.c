// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// E155 Lab 4

#include "fur_elise.h"
#include "STM32L432KC_TIM2.h"
#include "STM32L432KC_TIM16.h"
#include "STM32L432KC_RCC.h"
#include <stdint.h>
#include <math.h>

#define PSC32 1250; // Prescale value for 32 ms duration
#define PSC200 50; // Prescale value for 200 Hz frequency

void setPitch(TIM2_TypeDef *tim, int pitch) {
    // Set new prescaler value
    double prescaler = ((double) pitch)/200.0 * PSC200;
    prescaler = round(prescaler);
    TIM2->PSC = (prescaler);
}

void PWM(TIM2_TypeDef *tim) {

    // 1. Select the active input for TIMx_CCR1: write the CC1S bits to 01 in the TIMx_CCMR1
    // register (TI1 selected)
    // Set CC1 to 01
    // 01: CC1 channel is configured as input, IC1 is mapped on TI1. 
    // CCMR1[1:0]->CC1S = 01
    TIM2->CCMR1 |= (0b01 << 0);

    // 2. Select the active polarity for TI1FP1 (used both for capture in TIMx_CCR1 and counter
    // clear): write the CC1P to ‘0’ and the CC1NP bit to ‘0’ (active on rising edge).
    TIM2->CCER &= ~(1 << 1);
    TIM2->CCER &= ~(1 << 3);

    // 3. Select the active input for TIMx_CCR2: write the CC2S bits to 10 in the TIMx_CCMR1
    // register (TI1 selected).
    TIM2->CCMR1 |= (0b10 << 8);

    // 4. Select the active polarity for TI1FP2 (used for capture in TIMx_CCR2): write the CC2P
    // bit to ‘1’ and the CC2NP bit to ’0’ (active on falling edge).
    TIM2->CCER |= (1 << 5);
    TIM2->CCER &= ~(1 << 7);

    // 5. Select the valid trigger input: write the TS bits to 101 in the TIMx_SMCR register
    // (TI1FP1 selected).
    TIM2->SMCR |= (0b101 << 4);

    // 6. Configure the slave mode controller in reset mode: write the SMS bits to 100 in the
    // TIMx_SMCR register.
    TIM2->SMCR |= (0b100 << 0);

    // 7. Enable the captures: write the CC1E and CC2E bits to ‘1 in the TIMx_CCER register.
    TIM2->CCER |= (1 << 0);
    TIM2->CCER |= (1 << 4);
}

void delay_millis(TIM16_TypeDef * tim, uint32_t ms) {
  
    // Set new prescaler value
    uint32_t prescaler;
    prescaler = ms/31.25 * PSC32;
    TIM16->PSC |= (prescaler << 0);

}


int main(void) {

    configurePLL();

    TIM2_TypeDef *tim2;
    TIM16_TypeDef *tim16;

    // initialize timers
    initTIM2(tim2);
    initTIM16(tim16);

    // Set initial pitch to 0
    setPitch(tim2, 0);

    // Start PWM
    PWM(tim2);
  
    // Start song
    for (uint32_t i = 0; i < sizeof(notes); i++) {

        int pitch = notes[i][0];
        int duration = notes[i][1];

        // Set the pitch
        setPitch(tim2, pitch);

        // Start the clock for the duration
        delay_millis(tim16, duration);
        
        //// Wait for the auto-reload registers to read the right values
        //while((((tim16->ARR >> 0) & 1) == 0) & (((tim2->ARR >> 0) & 1) == 0)); // TODO: how do I write this?

        // Wait for UEV to turn on
        while(((tim16->CNT >> 31) & 1) == 0);

    }

}