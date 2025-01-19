#include <STC89C5XRC.h>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

void main()
{
    uint16_t i = 0;
    uint8_t j  = 0x01;
    P2         = 0xff;
    while (1) {
        i++;
        if (i == 33000) {
            P2 = 0xff ^ j;
            j <<= 1;
            if (j == 0) j = 0x01;
            i = 0;
        }
    };
}