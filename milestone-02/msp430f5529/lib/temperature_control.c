#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "flint.h"
#include "temperature_control.h"
#include "pwm.h"
#include "uart.h"

const float Vref = 3.3;
uint16_t adcHistory[8];
uint16_t adc_goal;

float adc2Temperature(uint16_t adc) {
    if(adc >= 1807) {
        return ((float)adc - 3991.4888889) / -55.1466667;
    }
    else if(adc >= 896) {
        return ((float)adc - 3099.3) / -34.22;
    }
    else {
        return ((float)adc - 1778.357143) / -14.75714;
    }
}

void updateHistory(uint16_t adc12){
    for(uint8_t i = 7; i > 0; i--){
        adcHistory[i] = adcHistory[i-1];
    }
    // 0 1 2 3 4 5 6 7
    // * 0 1 2 3 4 5 6
    adcHistory[0] = adc12;
}

void handleTemperatureControl(uint16_t adc12){
    updateHistory(adc12);
    adjustDutyCycle(calcDutyCycleOffset(calcDistance()));
    const float temperature = adc2Temperature(adcHistory[0]);
    printInfoToUART(adc12, temperature, getDutyCycle());
}

int16_t calcDutyCycleOffset(int16_t distance){
     return -distance;
}

int16_t calcDistance() {
    return adc_goal - calcAvg();
}

uint16_t calcAvg() {
    uint16_t sum = 0;
    for(uint8_t i = 0; i < 8; i++){
        sum += adcHistory[i];
    }
    return sum >> 3;
}

void setTemperatureGoal(float temperature){
    if(temperature <= 40){
        adc_goal = -55.1466667 * temperature + 3991.4888889;
    }
    else if (temperature <= 65){
        adc_goal = -34.22 * temperature + 3099.3;
    }
    else if (temperature <= 100){
        adc_goal = -14.75714 * temperature + 1778.357143;
    }
    else {
        adc_goal = 0x3ff; // out of range supported range
    }

    for(uint8_t i = 0; i < 8; i++) {
        adcHistory[i] = adc_goal;
    }
}
void printInfoToUART(uint16_t adc12, float temperature, uint8_t duty_cycle) {
    const uint8_t buf_len = 64;
    char buffer [buf_len];
    Flint t_goal, t_0, t_avg;
    t_goal = float2Flint(adc2Temperature(adc_goal));
    t_0 = float2Flint(adc2Temperature(adcHistory[0]));
    t_avg = float2Flint(adc2Temperature(calcAvg()));

    sprintf(buffer, "ADC: 0x%03x T0: %03d.%03d T_AVG: %03d.%03d GOAL: %03d.%03d DUTY: 0x%02x \n", adc12, t_0.wholeNum, t_0.decimal, t_avg.wholeNum, t_avg.decimal,
            t_goal.wholeNum, t_goal.decimal, getDutyCycle());
    send_bytes(buffer, buf_len);
    //for(uint8_t i = 0; i < 8; i ++) {
    //    sprintf(buffer, "%d|%03x\n", i, adcHistory[i]);
    //}
}

