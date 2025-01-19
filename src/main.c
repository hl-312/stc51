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

// ����С�����������С����Ķ��������λ P07����1����
uint8_t codeTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void main()
{
    // ѡ�����ұߵ����֣����ֱ�Ŵ������� 0~7
    DIGITALTUBESBIT(0x03);
    // ʹ����ʾΪ 0
    DIGITALTUBESSEGMENT = codeTable[8];
    while (1) {}
}