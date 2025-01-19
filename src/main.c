#include <STC89C5XRC.h>
#include <INTRINS.H>

// 流水灯方向
#define DIRECTION RIGHT
// flowspeed的分辨率为100ms
#define FLOWSPEED 2
// 流水灯持续时间以一个灯亮为单位，取值8流一遍
#define DURATION 8 * 2

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

typedef enum {
    RIGHT,
    LEFT
} Direction;

// delay for num half seconds.
void Delay100ms(void);
// led lighting to flow to Direction in P2, fluence at num, duration of drt.
void FlowLedP2(Direction dirt, uint8_t num, uint16_t drt);

void main()
{
    P2 = 0xff;
    FlowLedP2(DIRECTION, FLOWSPEED, DURATION);
    while (1);
}

void Delay100ms(void) //@11.0592MHz
{
    unsigned char data i, j;

    i = 180;
    j = 73;
    do {
        while (--j);
    } while (--i);
}

void FlowLedP2(Direction dirt, uint8_t num, uint16_t drt)
{
    uint8_t tmp = num;
    uint8_t set = 0x00;
    for (; drt > 0; drt--) {
        if (dirt == RIGHT) {
            set <<= 1;
            if (set == 0) set = 0x01;
        } else if (dirt == LEFT) {
            set >>= 1;
            if (set == 0) set = 0x80;
        }
        P2 = 0xff ^ set;
        while (tmp) {
            Delay100ms();
            tmp--;
        }
        tmp = num;
    }
    P2 = 0xff;
    return;
}