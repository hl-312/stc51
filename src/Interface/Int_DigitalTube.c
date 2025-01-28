#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

/// @brief 无小数点段码表，小数点的段码是最高位P07，给1点亮。
static uint8_t s_segmentCodeTable[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void Int_DigitalTubes_Init(struct Int_DigitalTubes_Struct *this)
{
    uint8_t i;
    this->type       = CATHODE;
    this->setting[0] = 0xff;
    this->setting[1] = 0x00;
    for (i = 0; i < 10; i++) {
        if (i < 8) {
            this->buffer[i] = i;
        }
        this->segmentCodeTable[i] = this->type ? ~s_segmentCodeTable[i] : s_segmentCodeTable[i];
    }
    this->Init         = Int_DigitalTubes_Init;
    this->DisplayOne   = Int_DigitalTubes_DisplayOne;
    this->DisplayCycle = Int_DigitalTubes_DisplayCycle;
    this->Display      = Int_DigitalTubes_Display;
    // 测试用例
    for (i = 0; i < 8; i++) {
        this->DisplayOne(this, i);
        Com_Util_Delay500ms();
    }
    SELECT(0);
    Com_Util_Delay998ms();
    return;
}

void Int_DigitalTubes_DisplayOne(Int_DigitalTubes_Struct *this, uint8_t site)
{
    if (this->setting[0] & 0x01 << site) // 检查位开关
    {
        SEM = 0x00;                                                  // 清除原由内容，避免切换位选时会显示一瞬间，造成拖影。
        SELECT(site);                                                // 设置位选为该位，0001 1100b, 8+4=12=0xC
        if (this->setting[1] & 0x01 << site)                         // 检查小数点开关
            SEM = this->segmentCodeTable[this->buffer[site]] | 0x80; // 赋值显示内容，有小数点所以或一下0x80
        else
            SEM = this->segmentCodeTable[this->buffer[site]]; // 无小数点，直接赋值
    }
    return;
}

void Int_DigitalTubes_DisplayCycle(struct Int_DigitalTubes_Struct *this)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        SEM = 0;
        Int_DigitalTubes_DisplayOne(this, i);
        Com_Util_Delay1ms();
    }
    SEM = 0;
    return;
}

void Int_DigitalTubes_Display(struct Int_DigitalTubes_Struct *this, uint8_t time)
{
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // 一个周期约8ms多，1000ms/8=125，取小一点123
        {
            Int_DigitalTubes_DisplayCycle(this);
        }
    }
    SEM = 0x00; // 用完端口顺手清理是好习惯
}
