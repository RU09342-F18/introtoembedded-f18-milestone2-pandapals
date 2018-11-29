// adc.c
#include <msp430.h>
#include "adc.h"

// configures adc v ref and interrupt
void setup_adc(){
    /*ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_8;         // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_2;                     // Use sampling timer
    ADC12IE = 0x01;                           // Enable interrupt
    ADC12CTL0 |= ADC12ENC;
    P6SEL |= 0x01;                            // P6.0 ADC option select
    ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
    */
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+ADC12SHT0_8+ADC12MSC; // Turn on ADC12, set sampling time
                                            // set multiple sample conversion
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_2;       // Use sampling timer, set mode
  //ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ADC12ENC;                    // Enable conversions
  ADC12CTL0 |= ADC12SC;                     // Start conversion
}

void start_sampling_conversion(){
    ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
}
