// uart.c

#include <msp430.h>
#include <stdint.h>
#include "uart.h"

void setup_uart() {
    /* Configure hardware UART */
    P4SEL |= BIT4+BIT5;                       // P3.3,4 = USCI_A0 TXD/RXD
    UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA1CTL1 |= UCSSEL_2;                     // SMCLK
    UCA1BR0 = 9;                              // 1MHz 115200 (see User's Guide)
    UCA1BR1 = 0;                              // 1MHz 115200
    UCA1MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

}

void send_bytes(uint8_t *bytes, uint8_t length) {
    while(length--) {
        while (!(UCA1IFG&UCTXIFG));             // USCI_A1 TX buffer ready?
        UCA1TXBUF = *bytes; //Write the character
        bytes++; //Increment the bytes pointer to point to the next character
    }
}

static unsigned char lookup[16] = {
    0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
    0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

uint8_t flipByte(uint8_t flipped){
    return (lookup[flipped&0b1111] << 4) | lookup[flipped>>4];
}

uint8_t ascii2Int(char c){
    return c = '0';
}
