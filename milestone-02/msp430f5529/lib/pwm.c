// pwm.c
#include <stdint.h>
#include <msp430.h>
#include "pwm.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void setup_pwm() {

    TA0CCTL0 = CCIE; //  CCR0 interrupt enabled

    // Add ID_1 to both timers (divide clk by 2) if brightness of 0 doesn't work
    // because there is not enough time between Timer A0 and Timer A1

    TA0CTL = TASSEL_1 + MC_1 + TAIE /*+ ID_1 */; // Set the timer A to SMCLCK, Up mode

    TA0CCR0 = 256;
    // TA0CCR0 will set the overall RGB led period
    //              currently 1:1
    // if TA0CCRO must be changed, try to increase to binary power
    // multiply brightness accordingly
    //    EX: TA0CCR0 = 512;
    //        TA0CCR1 = brightness*2

    set_duty_cycle(0xaa);

}

void set_duty_cycle(uint8_t duty_cycle) {
    TA0CCR0 = duty_cycle;
}

void adjustDutyCycle(int16_t offest) {
    int16_t ccr1 = TA0CCR1;
    if(offest <= 0){
        TA0CCR0 = (uint8_t) MAX((ccr1 + offest), 0);
    }
    else{
        TA0CCR0 = (uint8_t) MIN((ccr1 + offest), 0xff);
    }
}

uint8_t getDutyCycle(){
    return TA0CCR0;
}
