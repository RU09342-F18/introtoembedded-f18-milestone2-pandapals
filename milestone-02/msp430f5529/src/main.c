#include <msp430.h>
#include <stdio.h>
#include <stdint.h>
#include "../lib/adc.h" // setup_adc, start_sampling_conversion
#include "../lib/flint.h" // setup_adc, start_sampling_conversion
#include "../lib/pwm.h" // setup_adc, start_sampling_conversion
#include "../lib/uart.h" // setup_adc, start_sampling_conversion
#include "../lib/temperature_control.h" // setup_adc, start_sampling_conversion

/**
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    setup_pwm();

    setup_adc();

    setup_uart();
    __bis_SR_register(GIE);

    //setTemperatureGoal(33.2);
    //set_duty_cycle(255);

    while(1) {
        handleTemperatureControl((uint16_t) ADC12MEM0);
    }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12_ISR (void)
#else
#error Compiler not supported!
#endif
{
    // 6: ADC12IFG0
    if(__even_in_range(ADC12IV,34) == 6){
        //handleTemperatureControl((uint16_t) ADC12MEM0);
    }
}

uint8_t rxCounter = 0;
Flint rxFlint = { .wholeNum = 0, .decimal = 0 };

void __attribute__((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
{
    // 012.123
    send_bytes("HI\n", 3);
    uint8_t byteIn = UCA1RXBUF;
    switch(rxCounter){
        case 0:
            rxFlint.wholeNum += ascii2Int(flipByte(byteIn)) * 100;
            break;
        case 1:
            rxFlint.wholeNum += ascii2Int(flipByte(byteIn)) * 10;
            break;
        case 2:
            rxFlint.wholeNum += ascii2Int(flipByte(byteIn));
            break;
        case 4:
            rxFlint.decimal += ascii2Int(flipByte(byteIn)) * 100;
            break;
        case 5:
            rxFlint.decimal += ascii2Int(flipByte(byteIn)) * 10;
            break;
        case 6:
            rxFlint.decimal += ascii2Int(flipByte(byteIn));
            setTemperatureGoal(flint2Float(rxFlint));
            rxFlint.wholeNum = 0;
            rxFlint.decimal = 0;
            rxCounter = 0;
            break;
    }
    rxCounter++;

}

