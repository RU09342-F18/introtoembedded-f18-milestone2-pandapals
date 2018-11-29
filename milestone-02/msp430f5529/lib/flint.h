// flint.h - float + int

#include <stdint.h>

typedef struct flint {
    uint8_t wholeNum;
    uint8_t decimal;
} Flint;

Flint float2Flint(float floaty_boi);

Flint ints2Flint(uint8_t wholeNum, uint8_t decimal);

float flint2Float(Flint f);
