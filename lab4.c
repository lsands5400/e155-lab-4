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

volatile uint32_t reloadD;
volatile uint32_t reloadP;

void PWM(void) {
    // Set duty cycle
    TIM2->CCR1 |= reloadP / 2;

    // Set OCxM bit to PWM mode 1
    TIM2->CCMR1 |= (0b0110 << 4);

    // Set OCxPE
    TIM2->CCMR1 |= (1 << 3);

    // Set UG bit
    TIM2->EGR |= (1 << 0);

    // Set OC polarity as active low with CCxP bit
    TIM2->CCER |= (1 << 1);

    // Enable OCx output with CCxE bit
    TIM2->CCER |= (1 << 0);
}

void setPitch(int pitch) {
    // Set new ARR value
    if (pitch == 0) {
      TIM2->ARR &= 0;
    } else {
      reloadP = 200.0/((double) pitch) * ARR200;
      TIM2->ARR = reloadP;
    }
    TIM2->CCR1 |= reloadP / 2;
}

void delay_millis(uint32_t ms) {
    // Set new ARR value
    while(((TIM16->SR >> 0) & 1) == 0);
    reloadD = ms/31.25 * ARR32;
    TIM16->ARR = reloadD;
}


int main(void) {

    // Enable clock for GPIOA
    RCC->AHB2ENR |= (1 << 0);

    // Set OUTPUT_PIN as alternate function for TIM PWM
    pinMode(OUTPUT_PIN, GPIO_ALT);
    // Set alternate function to TIM2_CH1
    GPIO->AFRL &= ~(0b1111 << 20);
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
        // while(((TIM16->SR >>0) & 1) != 1);
        
        // Set UG bit
        TIM2->EGR |= (1 << 0);
    }
}