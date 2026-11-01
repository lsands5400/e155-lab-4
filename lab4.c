// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// E155 Lab 4

#include "fur_elise.h"
#include "STM32L432KC_TIM2.h"
#include "STM32L432KC_TIM16.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_FLASH.h"

#include <stdint.h>
#include <math.h>

#define ARR32 4000.0 // ARR value for 32 ms duration
#define ARR200 50000.0 // ARR value for 200 Hz frequency
#define OUTPUT_PIN 5 // PA5 for TIM2_CH1

void PWM(void) {

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

void setPitch(int pitch) {
    // Set new ARR value
    if (pitch == 0) {
      TIM2->ARR &= 0;
    } else {
      uint32_t reload = 200.0/((double) pitch) * ARR200;
      TIM2->ARR |= (reload << 0);
    }
}

void delay_millis(uint32_t ms) {
    // Set new ARR value
    uint32_t reload;
    reload = ms/31.25 * ARR32;
    TIM16->ARR |= (reload << 0);
}


int main(void) {

    // Enable clock for GPIOA
    RCC->AHB2ENR |= (1 << 0);

    // Set OUTPUT_PIN as alternate function for TIM PWM
    pinMode(OUTPUT_PIN, GPIO_ALT);
    // Set alternate function to TIM2_CH1
    GPIO->AFRL &= ~(0b0000 << 20);
    GPIO->AFRL |= (0b0001 << 20);

    // initialize timers
    TIM2_TypeDef *tim2 = TIM2;
    TIM16_TypeDef *tim16 = TIM16;
    initTIM2(tim2);
    initTIM16(tim16);

    tim2->PSC &= 0;
    TIM2->PSC = (625 << 0);
    tim16->PSC &= 0;
    TIM16->PSC = (8 << 0);  
    TIM2->DIER |= (1 << 6);

    // Set initial pitch to 0
    setPitch(0);

    delay_millis(10);

    // Start PWM for TIM2
    PWM();
    
    // UIF Remapping
    TIM16->CR1 |= (1 << 11);
    // clear SR 
    TIM16->SR &= 0;

    //// Start song
    for (uint32_t i = 0; i < 109; i++) {

        int pitch = notes[i][0];
        int duration = notes[i][1];

        // clear UIF 
        TIM16->SR &= ~(1 << 0);

        // Set the pitch
        setPitch(pitch);

        // Start the clock for the duration
        delay_millis(duration);
    }
}