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

    // Set OCxM bit to PWM mode 1
    TIM2->CCMR1 &= ~(0b1111 << 4);
    TIM2->CCMR1 |= (0b0110 << 4);

    // Set OCxPE
    TIM2->CCMR1 |= (1 << 3);

    // Set OC polarity as active high with CCxP bit
    TIM2->CCER &= ~(1 << 1);

    // Enable OCx output with CCxE bit
    TIM2->CCER |= (1 << 0);

    // Enable auto-reload preload
    TIM2->CR1 |= (1 << 7);

    // Set UG bit
    TIM2->EGR |= (1 << 0);
    
    // Start timer
    TIM2->CR1 |= (1 << 0);

}

void setPitch(int pitch) {

    if (pitch == 0) {
        // Silence
        TIM2->CCR1 = 0;
        return;
    }

    // Timer counter frequency = 10 MHz
    // ARR = (timer frequency / pitch) - 1
    reloadP = (10000000UL / pitch) - 1;

    // Set frequency
    TIM2->ARR = reloadP;

    // 50% duty cycle
    TIM2->CCR1 = (reloadP + 1) / 2;

    // Immediately load updated registers
    TIM2->EGR |= (1 << 0);
}

void delay_millis(uint32_t ms) {
    if (ms == 0) return;

    // Stop timer
    TIM16->CR1 &= ~(1 << 0);
    // Reset counter
    TIM16->CNT = 0;
    // Set new ARR value
    TIM16->ARR = (10 * ms) - 1;
    // Generate update event
    TIM16->EGR |= (1 << 0);
      // Clear update flag
    TIM16->SR &= ~(1 << 0);
    // Start timer
    TIM16->CR1 |= (1 << 0);
    // Wait for update event
    while (!(TIM16->SR & (1 << 0)));
    // Stop timer
    TIM16->CR1 &= ~(1 << 0);
    // Clear update flag
    TIM16->SR &= ~(1 << 0);
}


int main(void) {

    // Configure system clock to 80 MHz
    configureFlash();
    configureClock();

    // Enable GPIOA clock
    RCC->AHB2ENR |= (1 << 0);

    // Configure PA5 as alternate function
    pinMode(OUTPUT_PIN, GPIO_ALT);

    // PA5 alternate function 1 = TIM2_CH1
    GPIO->AFRL &= ~(0b1111 << 20);
    GPIO->AFRL |= (0b0001 << 20);

    // Initialize timers
    initTIM2(TIM2);
    initTIM16(TIM16);

    // TIM2: 80 MHz / 8 = 10 MHz
    TIM2->PSC = 7;
    TIM2->ARR = 9999;
    TIM2->CNT = 0;

    // Load prescaler and ARR
    TIM2->EGR |= (1 << 0);
    TIM2->SR &= ~(1 << 0);

    // Start PWM configuration
    setPitch(0);
    PWM();

    // Small initial delay
    delay_millis(10);

    // Play song
    uint32_t numNotes = sizeof(notes) / sizeof(notes[0]);

    for (uint32_t i = 0; i < numNotes; i++) {

        int pitch = notes[i][0];
        int duration = notes[i][1];

        // Set frequency
        setPitch(pitch);

        // Wait for duration
        delay_millis(duration);
    }

    // End song
    setPitch(0);

    while (1) {
    }
}