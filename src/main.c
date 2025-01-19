#include <STC89C5XRC.h>
#include <INTRINS.H>

// 占空比分辨率控制 PWM
// 周期长度 = Frequency*Resolution = 1ms = 1000hz
#define FREQUENCY Delay10us()
// 占空比，取值范围为0~resolution-1，0=0%, resolution=100%
#define DUTYCYCLE0123 5
#define DUTYCYCLE4567 90
// 分辨率 = 1/resolution
#define RESOLUTION 100

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

// delay 100us
void Delay10us(void);

// 要实现不同占空比信号来调节led亮度
void main()
{
    uint8_t i = 0;
    while (1) {
        // 这里不用取余，用跟基本的减法运算，将变化范围限制在 0~RESOLUTION
        // 赋初值应考虑到下方占空比大小与亮度大小的对应关系，习惯上觉得，
        // 下方if里的数字越大，应该越亮，所以初值应该为全亮，然后在逐个熄灭
        // 实验证明，就算是两个相邻的if语句，之间的时间都足以让led有肉眼可见的亮度。
        // 所以0%的占空比只能在赋初值出就直接设置。
        if (i == 0) P2 = 0x00;
        // 多位一同赋值建议使用格式：var = var & ~0x09 | 0x09; 这样可以同时设置0和1，
        // 之所以要在复位那里用取反号，是因为转化为16进制好计算，如1011可以写成~0100，即~0x4
        if (i == DUTYCYCLE0123) P2 = P2 & ~0x0f | 0x0f;
        if (i == DUTYCYCLE4567) P2 = P2 & ~0xf0 | 0xf0;
        // 计数完一个周期，就恢复初值
        FREQUENCY;
        i++;
        // 初值维护语句必须在 i++ 下面，否则会导致 i 永不可能为 0，所有灯闪一下后，全灭
        if (i == RESOLUTION) i = 0;
    };
}

void Delay10us(void) //@11.0592MHz
{
    unsigned char data i;

    i = 2;
    while (--i);
}
