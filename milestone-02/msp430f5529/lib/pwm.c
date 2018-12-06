// pwm.c
#include <stdint.h>
#include <msp430.h>
#include "pwm.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

const uint8_t FAN = BIT0; // P3.0

void setup_pwm() {

    P1DIR |= BIT2+BIT3;                       // P1.2 and P1.3 output
    P1SEL |= BIT2+BIT3;                       // P1.2 and P1.3 options select
    TA0CCR0 = 512-1;                          // PWM Period
    TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TA0CCR1 = 384;                            // CCR1 PWM duty cycle
    TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
    TA0CCR2 = 128;                            // CCR2 PWM duty cycle
    TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR

}

void set_duty_cycle(uint8_t duty_cycle) {
    TA0CCR1 = duty_cycle;
}

void adjustDutyCycle(int16_t offest) {
    int16_t ccr1 = TA1CCR1;
    if(offest <= 0){
        TA0CCR1 = (uint8_t) MAX((ccr1 + offest), 0);
    }
    else{
        TA0CCR1 = (uint8_t) MIN((ccr1 + offest), 0xff);
    }
}

uint8_t getDutyCycle(){
    return TA0CCR1;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) Timer1_A0 (void)
#else
#error Compiler not supported!
#endif
{
    P3OUT ^= FAN;
}
