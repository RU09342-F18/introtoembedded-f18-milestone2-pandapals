// temperature_response.c

#include <stdint.h>
#include <stdlib.h>
#include "../lib/adc.h"
#include "../lib/pwm.h"
#include "../lib/temperature_control.h"

const float DISIPATION_EFFECTIVENESS = 0.1;
const float HEATUP_RATE = 1.2;
const float NOISEYNESS = 0.001; // V range for noise
const float RESOLUTION = Vref * 1e6 / ( 2 ^ 12); // uV resolution

const uint8_t TEMPERATURE_START = 20;
const uint8_t TEMPERATURE_GOAL = 50;

unsigned char TA0CCR1 = 0;

int main() {
    float currentTemp = TEMPERATURE_START;
    setTemperatureGoal(float TEMPERATURE_GOAL);

    for(unsigned int i = 0; i < 100; i++ ) {
        handleTemperatureControl();
    }
}

float noise() {
    return rand() % (int) (NOISEYNESS * 1e6);
}

unsigned int volts2Adc(float volts) {
    return (unsigned int) (volts * RESOLUTION);
}
