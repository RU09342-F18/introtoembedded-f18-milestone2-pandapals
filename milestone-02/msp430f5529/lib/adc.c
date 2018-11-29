// adc.c
#include <msp430.h>
#include "adc.h"

// configures adc v ref and interrupt
void setup_adc(){
    ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_8;         // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_3;                     // Use sampling timer
    ADC12IE = 0x01;                           // Enable interrupt
    ADC12CTL0 |= ADC12ENC;
    P6SEL |= 0x01;                            // P6.0 ADC option select
    P1DIR |= 0x01;                            // P1.0 output
}

void start_sampling_conversion(){
    ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
}
