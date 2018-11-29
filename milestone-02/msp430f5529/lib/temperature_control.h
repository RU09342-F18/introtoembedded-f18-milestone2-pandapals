// temperature_control.h
#include <stdint.h>

float adc2Temperature(uint16_t adc);

void updateHistory(uint16_t adc12);

void handleTemperatureControl(uint16_t adc12);

int16_t calcDutyCycleOffset(int16_t delta);

int16_t calcDistance();

uint16_t calcAvg();

void setTemperatureGoal(float temperature);

void printInfoToUART(uint16_t adc12, float temperature, uint8_t duty_cycle);

