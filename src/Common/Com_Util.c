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