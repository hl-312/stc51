#include "Com_Util.h"
#include <INTRINS.H>

void Com_Util_Delay1ms(void)
{
    uint8_t data i, j;

    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j);
    } while (--i);
}

void Com_Util_Delay500ms(void) //@11.0592MHz
{
    unsigned char data i, j, k;

    _nop_();
    i = 4;
    j = 129;
    k = 119;
    do {
        do {
            while (--k);
        } while (--j);
    } while (--i);
}

void Com_Util_Delay998ms(void) //@11.0592MHz
{
    unsigned char data i, j, k;

    _nop_();
    i = 7;
    j = 254;
    k = 93;
    do {
        do {
            while (--k);
        } while (--j);
    } while (--i);
}
