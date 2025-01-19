#include <STC89C5XRC.h>

#define DIGITALTUBESBIT(n)  P2 = P2 & ~0x1c | (n << 2)
#define DIGITALTUBESSEGMENT P0

#define DIGITALTUBESBIT(n)  P2 = P2 & ~0x1c | (n << 2)
#define DIGITALTUBESSEGMENT P0

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

// 所有小数点均不亮，小数点的段码是最高位 P07，给1点亮
uint8_t codeTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void main()
{
    // 选中最右边的数字，数字编号从右至左 0~7
    DIGITALTUBESBIT(0x03);
    // 使其显示为 0
    DIGITALTUBESSEGMENT = codeTable[8];
    while (1) {}
}