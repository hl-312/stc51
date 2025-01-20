#include <STC89C5XRC.h>
#include <INTRINS.H>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

/*
数码管显示功能分析
已经实现：任意数码管点亮并显示指定内容，但还未重构成函数。
目标实现：任意多个数码管同时显示任意内容，可以不同。
硬件限制：同一时间，只能点亮单个数码管
分析：
    亮度问题：数码管必须依次显示，因此一组显示周期应当为单个显示时间*显示个数，
    为了保证不同显示个数亮度一致，建议固定显示个数为8，不显示的位置就只延时。

    刷新率问题：100hz对应10ms，取8的倍数，8ms，每个数字显示时间1ms，刷新率大概125hz左右，不会闪烁。

    显示内容问题：关闭，无小数点数字，有小数点数字三种内容。
        小数点处理：数字已有段码表，若是有小数点数字再单独列出感觉很浪费空间，若只在段码表里增加一个字节为 0x80，
        需要小数点的就那对应段码和 0x80 或一下即可。再考虑到这样需要再单独存储每个数字是否有小数点的信息，
        干脆就用一个字节的各个位来表示，由于小数点的段码置1亮，所以每个数字的对应位为 1 表示小数点有效，
        使用时，对该字节只保留对应位，再移位至最高位，再与数字的段码或一下，赋给端口即可。
        关闭处理：仿照小数点的处理方式，用一个字节存储对应数字位的点亮信息，同样 1 有效。
    显然，我需要位测试函数（var&0x01<<i），移位函数，位赋值函数（单个位可以直接置位或复位，多个位如101b，
    就建议先复位&000b再置位|101b）这些函数比较简单，宏函数即可。
思路：
1. 将已经实现的功能重构为函数：void displayOneDT(bitSite)，函数内部固定显示时间为 1ms（延时函数），显示信息查setting表
2. 显示周期函数，循环调用八次单位显示函数
3. 显示函数，可以选择总的显示时长
开始实现。
*/

// 无小数点段码表，小数点的段码是最高位P07，给 1 点亮。
uint8_t segmentCodeTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// 数码管配置表，[0]: 开关信息; [1]: 小数点开关信息; [2-11]: 0-7号数码管显示内容。
uint8_t setting[] = {0xff, 0x14, 0, 2, 1, 0, 5, 2, 0, 2};

// 延时函数
void Delay1ms(void);
// 单位显示函数。检查位开关，设置位选，检查小数点，设置内容，延时，返回
void displayOneDT(uint8_t bitSite);
// 一个周期的显示函数
void displayCycle(void);
// 显示函数，显示时间单位 1s，考虑到函数调用的开销，可以设置的略微小于1s。最大256s。
void display(uint8_t time);
// 时钟函数，格式：hh.mm.ss，左右各空一位，最小时间单位1s。
// 对应配置信息为：[0]=0111 1110=0x7e, [1]=0010 1000=0x28;
void display_Timer(uint16_t time, int8_t *initTime);

void main()
{
    int8_t *init_time = "11.59.56";
    display_Timer(60 * 70, init_time);
    while (1) {
    }
}

void Delay1ms(void) //@11.0592MHz
{
    uint8_t data i, j;

    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j);
    } while (--i);
}

void displayOneDT(uint8_t bitSite)
{
    if (setting[0] & 0x01 << bitSite) // 检查位开关
    {
        P0 = 0x00;                                              // 清除原由内容，避免切换位选时会显示一瞬间，造成拖影。
        P2 = P2 & ~0x1c | bitSite << 2;                         // 设置位选为该位，0001 1100b, 8+4=12=0xC
        if (setting[1] & 0x01 << bitSite)                       // 检查小数点开关
            P0 = segmentCodeTable[setting[bitSite + 2]] | 0x80; // 赋值显示内容，有小数点所以或一下0x80
        else
            P0 = segmentCodeTable[setting[bitSite + 2]]; // 无小数点，直接赋值
    }
    Delay1ms();
    P0 = 0x00;
    return;
}

void displayCycle(void)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        displayOneDT(i);
    }
    return;
}

void display(uint8_t time)
{
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // 一个周期约8ms多，1000ms/8=125，取小一点123
        {
            displayCycle();
        }
    }
    P0 = 0x00; // 用完端口顺手清理是好习惯
}

void display_Timer(uint16_t time, int8_t *initTime)
{
    uint8_t i, j;
    // 配置表初始化
    setting[0] = 0x7e;
    setting[1] = 0x28;
    setting[9] = 0;
    setting[2] = 0;
    // 时间初始化
    for (i = 0, j = 0; i < 8; i++) {
        if (initTime[i] >= 48 && initTime[i] <= 57) setting[8 - j++] = initTime[i] - 48; // 空一位所以从8开始
    }
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // 一个周期约8ms多，1000ms/8=125，取小一点123
        {
            displayCycle();
        }
        setting[3]++;
        if (setting[3] > 9) {
            setting[3] = 0;
            setting[4]++;
        }
        if (setting[4] > 5) {
            setting[4] = 0;
            setting[5]++;
        }
        if (setting[5] > 9) {
            setting[5] = 0;
            setting[6]++;
        }
        if (setting[6] > 5) {
            setting[6] = 0;
            setting[7]++;
        }
        if (setting[8] == 0) {
            if (setting[7] > 9) {
                setting[7] = 0;
                setting[8]++;
            }
        } else if (setting[8] == 1) {
            if (setting[7] > 1) {
                setting[7] = 0;
                setting[8] = 0;
            }
        }
    }
    P0 = 0x00; // 用完端口顺手清理是好习惯
}
