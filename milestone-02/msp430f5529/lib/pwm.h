// pwm.h
#include <stdint.h>

void setup_pwm();

void set_duty_cycle(uint8_t duty_cycle);

void adjustDutyCycle(int16_t offest);

uint8_t getDutyCycle();

