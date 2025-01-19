#include <STC89C5XRC.h>
#include <INTRINS.H>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

// delay for num half seconds.
void Delay100us(void);

// 要实现不同占空比信号来调节led亮度
void main()
{
    uint8_t i = 0;
    while (1) {
        // 跟8取余就是设一个周期长8*100ms，同样一个周期被划为8段，设置一个灯亮的段数，就是在设置占空比。
        // 当取余为0时，就是第一段内，但是在第一段的开头还是结尾，看延时函数在赋值前还是赋值后，在后，就是在第一段开头
        if (i % 8 == 0) {
            // 赋初值应考虑到下方占空比大小与亮度大小的对应关系，习惯上觉得，
            // 下方if里的数字越大，应该越亮，所以初值应该为全亮，然后在逐个熄灭
            P2 = 0x00;
        }
        // 这里所有刻度都列出来了，实际使用只需给出所需刻度值即可
        // 也许应该定义一个宏函数，来置位和复位。算了，可能情况太多，不好定义。
        // 置位操作：|1，复位操作：&0，由于初值为全0，所以后续只需置位即可。
        // 多位一同赋值建议使用格式：var = var & ~0x09 | 0x09; 这样可以同时设置0和1，
        // 之所以要在复位那里用取反号，是因为转化为16进制好计算，如1011可以写成~0100，即~0x4
        if (i % 8 == 1) P2 = P2 & ~0x0f | 0x0f;
        //        if (i % 8 == 2) P2 = P2 & ~0x0f | 0x04;
        //        if (i % 8 == 3) P2 = P2 & ~0x0f | 0x08;
        //        if (i % 8 == 4) P2 = P2 & ~0x0f | 0x10;
        //        if (i % 8 == 5) P2 = P2 & ~0x0f | 0x20;
        //        if (i % 8 == 6) P2 = P2 & ~0x0f | 0x40;
        if (i % 8 == 7) P2 = P2 & ~0xf0 | 0xf0;
        // 保证每轮取余的结果相同，否则将240改为243，就有可能出现最后一个周期只有三段，占空比就乱了
        if (i == 240) i = 0;
        Delay100us();
        i++;
    };
}

void Delay100us(void) //@11.0592MHz
{
    unsigned char data i;

    _nop_();
    i = 43;
    while (--i);
}
