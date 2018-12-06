// flint.c
#include "flint.h"

Flint float2Flint(float floaty_boi) {
    Flint michiganMegaBowl;
    michiganMegaBowl.wholeNum = (uint8_t) floaty_boi;
    michiganMegaBowl.decimal = (uint8_t) ((floaty_boi - (uint8_t) (floaty_boi)) * 100);
    return michiganMegaBowl;
}

Flint ints2Flint(uint8_t wholeNum, uint8_t decimal){
    Flint andSteel;
    andSteel.wholeNum = wholeNum;
    andSteel.decimal = decimal;
    return andSteel;
}

float flint2Float(Flint f){
    return f.wholeNum + (float) (f.decimal) * 1e-2;
}
