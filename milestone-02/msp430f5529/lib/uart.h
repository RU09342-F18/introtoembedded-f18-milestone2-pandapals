// uart.h
#include <stdint.h>
// configures UART for baud 9600
void setup_uart();

char* read_data_bytes();

void send_bytes(uint8_t *bytes, uint8_t length);

uint8_t flipByte(uint8_t fipped);

uint8_t ascii2Int(char c);
