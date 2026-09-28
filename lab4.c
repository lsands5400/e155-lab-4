// Lindsey Sands
// lsands@g.hmc.edu
// 09-24-2026
// E155 Lab 4

#include "fur_elise.h"
#include "STM32L432KC_TIM2.h"
#include "STM32L432KC_TIM16.h"
#include "STM32L432KC_RCC.h"
#include <stdint.h>

void PWM(TIM2_TypeDef *tim, int duration) {

    // 1. Select the active input: TIMx_CCR1 must be linked to the TI1 input, so write the CC1S
    // bits to 01 in the TIMx_CCMR1 register. As soon as CC1S becomes different from 00,
    // the channel is configured in input and the TIMx_CCR1 register becomes read-only.

    // Set CC1 to 01
    // 01: CC1 channel is configured as input, IC1 is mapped on TI1. 
    // CCMR1[1:0]->CC1S = 01
    
    TIM2->CCMR1 |= (0b01 << 0);

    // 2. Program the input filter duration you need with respect to the signal you connect to the
    // timer (when the input is one of the TIx (ICxF bits in the TIMx_CCMRx register). Let’s
    // imagine that, when toggling, the input signal is not stable during at must 5 internal clock
    // cycles. We must program a filter duration longer than these 5 clock cycles. We can
    // validate a transition on TI1 when 8 consecutive samples with the new level have been
    // detected (sampled at fDTS frequency). Then write IC1F bits to 0011 in the
    // TIMx_CCMR1 register.

    // TODO: Figure out wtf this is saying
    TIM2->CCMR1 |= (0b0011 << 4);


    
    // 3. Select the edge of the active transition on the TI1 channel by writing the CC1P and
    // CC1NP and CC1NP bits to 000 in the TIMx_CCER register (rising edge in this case)
    TIM2->CCER |= (0b000 << 0);

    // 4. Program the input prescaler. In our example, we wish the capture to be performed at
    // each valid transition, so the prescaler is disabled (write IC1PS bits to 00 in the
    // TIMx_CCMR1 register).
    TIM2->CCMR1 &= ~(0b11 << 2);

    // 5. Enable capture from the counter into the capture register by setting the CC1E bit in the
    // TIMx_CCER register.
    TIM2->CCER |= (1 << 0);

    // 6. If needed, enable the related interrupt request by setting the CC1IE bit in the
    // TIMx_DIER register, and/or the DMA request by setting the CC1DE bit in the
    // TIMx_DIER register.

    // PWM input mode
    // This mode is a particular case of input capture mode. The procedure is the same except:
    // • Two ICx signals are mapped on the same TIx input.
    // • These 2 ICx signals are active on edges with opposite polarity.
    // • One of the two TIxFP signals is selected as trigger input and the slave mode controller
    // is configured in reset mode.
    // For example, the user can measure the period (in TIMx_CCR1 register) and the duty cycle
    // (in TIMx_CCR2 register) of the PWM applied on TI1 using the following procedure
    // (depending on CK_INT frequency and prescaler value):

}

void delay_millis(TIM16_TypeDef * tim, uint32_t ms) {
    size_t count = 0b11111010000; // 2000 // TODO: Should I just hardcode this? And should I make it a #define variable?
    size_t newCount;
    newCount = ms/31.25 * count;
    tim->CNT |= (newCount << 0);
}


int main(void) {

    TIM2_TypeDef *tim2;
    TIM16_TypeDef *tim16;

    // initialize timers
    initTIM2(tim2);
    initTIM16(tim16);
	
    for (size_t i; i<= sizeof(notes); i++) {
        int pitch = notes[i][1];
        int duration = notes[i][0];

        PWM(tim2, pitch);
        delay_millis(tim16, duration);
    }
	
}