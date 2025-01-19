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
        P2 = set ^ P2;  ����д��Ҳ���ԣ�0^0=0,1^0=1,0^1=1,1^1=0,
        P2Ĭ�Ϲأ�ֵȫ1���������������ض�λ��ͬ����0����������λ��ͬͬ��Ϊ1�رգ�
        ���ѱ�������λ����һλ�����Ϊ0����ͬ��1���رգ�Ч����ȡ����ͬ��
        ��Ȼ���ڿ�������ȡ��ֱ�ӣ�������⡣
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
