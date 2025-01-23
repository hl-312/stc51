#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

/// @brief 无小数点段码表，小数点的段码是最高位P07，给1点亮。
static uint8_t s_segmentCodeTable[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

/// @brief 数码管配置表，[0]: 开关信息; [1]: 小数点开关信息;
static uint8_t s_setting[] = {0xff, 0x00};

/// @brief 显存：0-7号数码管显示内容。
static uint8_t s_buffer[8];

void Int_DigitalTube_Init(void)
{
    uint8_t i;
    s_setting[0] = 0xff;
    s_setting[1] = 0x00;
    for (i = 0; i < 8; i++) {
        s_buffer[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        Int_DigitalTube_DisplayOne(i);
        Com_Util_Delay500ms();
    }
    SELECT(0);
    Com_Util_Delay998ms();
}

void Int_DigitalTube_DisplayOne(uint8_t site)
{
    if (s_setting[0] & 0x01 << site) // 检查位开关
    {
        SEM = 0x00;                                          // 清除原由内容，避免切换位选时会显示一瞬间，造成拖影。
        SELECT(site);                                        // 设置位选为该位，0001 1100b, 8+4=12=0xC
        if (s_setting[1] & 0x01 << site)                     // 检查小数点开关
            SEM = s_segmentCodeTable[s_buffer[site]] | 0x80; // 赋值显示内容，有小数点所以或一下0x80
        else
            SEM = s_segmentCodeTable[s_buffer[site]]; // 无小数点，直接赋值
    }
    return;
}

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
    return s_buffer;
}

void Int_DigitalTube_SetSetting(uint8_t site, uint8_t value)
{
    s_setting[site] = value;
    return;
}
