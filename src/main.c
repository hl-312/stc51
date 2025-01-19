#include <STC89C5XRC.h>
#include <INTRINS.H>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

void Delay500ms(void); //@11.0592MHz

void main()
{
    uint8_t set = 0x01;
    P2          = 0xff;
    while (1) {
        P2 = ~set;
        /*
        P2 = set ^ P2;  这种写法也可以，0^0=0,1^0=1,0^1=1,1^1=0,
        P2默认关，值全1，则与掩码异或后，特定位相同被置0点亮，其余位不同同仍为1关闭，
        而已被点亮的位与下一位掩码均为0，相同置1，关闭，效果与取反相同。
        当然现在看来不如取反直接，容易理解。
        */
        set <<= 1;
        if (set == 0) set = 0x01;
        Delay500ms();
    };
}

void Delay500ms(void) //@11.0592MHz
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
