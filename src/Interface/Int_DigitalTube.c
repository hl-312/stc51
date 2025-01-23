#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

// 无小数点段码表，小数点的段码是最高位P07，给 1 点亮。
static uint8_t s_segmentCodeTable[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

uint8_t setting[] = {0xff, 0x14};

uint8_t buffer[8];

void Int_DigitalTube_Init(void)
{
    uint8_t i;
    setting[0] = 0xff;
    setting[1] = 0x00;
    for (i = 0; i < 8; i++) {
        buffer[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        Int_DigitalTube_DisplayOne(i);
        Com_Util_Delay500ms();
    }
    SELECT(0);
    Com_Util_Delay998ms();
}

/// @brief 数码管显示单个数字
/// @param site
void Int_DigitalTube_DisplayOne(uint8_t site)
{
    if (setting[0] & 0x01 << site) // 检查位开关
    {
        SEM = 0x00;                                        // 清除原由内容，避免切换位选时会显示一瞬间，造成拖影。
        SELECT(site);                                      // 设置位选为该位，0001 1100b, 8+4=12=0xC
        if (setting[1] & 0x01 << site)                     // 检查小数点开关
            SEM = s_segmentCodeTable[buffer[site]] | 0x80; // 赋值显示内容，有小数点所以或一下0x80
        else
            SEM = s_segmentCodeTable[buffer[site]]; // 无小数点，直接赋值
    }
    return;
}

/// @brief 一个周期 8ms 的显示函数
/// @param
void Int_DigitalTube_DisplayCycle(void)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        SEM = 0;
        Int_DigitalTube_DisplayOne(i);
        Com_Util_Delay1ms();
    }
    SEM = 0;
    return;
}

/// @brief 显示函数，显示时间单位 1s，考虑到函数调用的开销，可以设置的略微小于1s。最大256s。
/// @param time
void Int_DigitalTube_Display(uint8_t time)
{
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // 一个周期约8ms多，1000ms/8=125，取小一点123
        {
            Int_DigitalTube_DisplayCycle();
        }
    }
    SEM = 0x00; // 用完端口顺手清理是好习惯
}

uint8_t *Int_DigitalTube_GetBufferAddress(void)
{
    return buffer;
}
