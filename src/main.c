#include <STC89C5XRC.h>
#include <INTRINS.H>

// 给 P22-P24 赋值，选中数码管位，二进制数编码位号，使用时带分号，数字编号从左至右 0~7
#define DIGITALTUBESBIT(n) P2 = P2 & ~0x1c | n << 2
// 给数码管对应的IO端口赋值
#define DIGITALTUBESSEGMENT P0
#define TESTBIT(var, n)     (var & (0x01 << n))
// 用 led 来测试程序执行位置，找bug，需要在main的开始先点亮 P20
#define LOG P20 = 1;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

typedef struct digitalBit {
    uint8_t point;   // 0灭1亮
    uint8_t content; // 显示数字
} digitalBit;

typedef struct digitalArray {
    uint8_t bitFlag;     // 给1打开
    digitalBit array[8]; // 数码管的位数组
} digitalArray;

// 所有小数点均不亮，小数点的段码是最高位 P07，给1点亮
uint8_t segmentCodeTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// 简化的数码管配置数组，-1 表示灭，0-9表示对应数字，10-19表示有小数点
int8_t settingDigitalTubes[] = {0, 0, 0, -1, 10, 0, 0, 0};
// 1ms 定时器
void Delay1ms(void);
// 数码管内容初始化，根据settingDigitalTubes设置digitalTubes
void initialDigitalTubes(digitalArray *dA);
// 一个周期的显示函数，8ms
void DisplayCycle(digitalArray *darray);
// 1s 显示函数
void digitalDisplay(digitalArray *darray);

/*
数码管动态显示功能分析：
1. 首先硬件不支持全部同时点亮
2. 为保证全部点亮的效果，需要所有数字的刷新率超过60hz，越高越好
3. 总共8个数字，每个数字显示一会后就要切去下一个数字，再根据第一点，因此，一个周期天然分成了八段，
每个数字的占空比自然就是1/8，所以亮度自然会变弱一些，就算有显示内容相同的，由于硬件限制也没法同时点亮。
如果显示的数字越多，这种限制会越明显，导致每个数字亮度越来越弱。
4. 每个数字的显示周期 = 8*点亮时间 = 刷新率倒数。
加入刷新率要是100hz，则显示周期10ms，10/8为单个数字的点亮时间。数字不整，将周期再取小点，8ms。
所以我需要一个1ms的定时器。然后考虑到改变显示内容的需求，这个改变要是太快了，肯定不行，要不然闪烁，
要不然不该亮的地方也有微弱的亮光，就将改变间隔设为1s吧，用一个函数封装，能实现1s时间的显示。
这里也能发现，若是显示时间太多，函数调用的开销也会影响占空比。
对数码管来说，每个数字应有亮灭两个状态，亮又分有没有小数点，每个又分0-9十个数字。使用结构体来表示。
*/
void main()
{
    digitalArray digitalTubes;
    initialDigitalTubes(&digitalTubes);
    while (1) {
        digitalDisplay(&digitalTubes);
    }
}

void Delay1ms(void) //@11.0592MHz
{
    unsigned char data i, j;

    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j);
    } while (--i);
}

void initialDigitalTubes(digitalArray *dA)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (settingDigitalTubes[i] < 0)
            dA->bitFlag = dA->bitFlag & ~0x01 << i; // 给对应位赋0，熄灯
        else if (settingDigitalTubes[i] >= 0 && settingDigitalTubes[i] < 10) {
            dA->bitFlag          = dA->bitFlag | 0x01 << i; // 给对应位赋1，点灯
            dA->array[i].point   = 0;
            dA->array[i].content = segmentCodeTable[settingDigitalTubes[i]];
        } else if (settingDigitalTubes[i] > 9) {
            dA->bitFlag          = dA->bitFlag | 0x01 << i; // 给对应位赋1，点灯
            dA->array[i].point   = 1;
            dA->array[i].content = segmentCodeTable[settingDigitalTubes[i] - 10];
        }
    }
    return;
}

void DisplayCycle(digitalArray *dA)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (TESTBIT(dA->bitFlag, i)) {
            DIGITALTUBESBIT(i);
            DIGITALTUBESSEGMENT = dA->array[i].content & ~(dA->array[i].point << 7) | (dA->array[i].point << 7);
        }
        Delay1ms();
    }
    return;
}

void digitalDisplay(digitalArray *dA)
{
    uint8_t timer = 123; // 考虑到函数调用的开销，将1000/8=125调小一些。
    while (timer--) {
        DisplayCycle(dA);
    }
    return;
}
