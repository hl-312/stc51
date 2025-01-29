#ifndef __APP_CLOCK_H__
#define __APP_CLOCK_H__

#include "Com_Util.h"
#include "Int_DigitalTube.h"

typedef struct App_Clock {
    Int_DigitalTubes_Struct dt;
    int8_t *initTime;
    void (*Display)(struct App_Clock *this, uint8_t time);
} App_Clock;

/// @brief 使用数码管来实现时钟，左右各空一位，最小时间单位1s。通过配置 setting数组，信息为：[0]=0111 1110=0x7e, [1]=0010 1000=0x28;
/// @param time 显示时间：0s~18h.12m.16s
/// @param initTime 格式："hh.mm.ss"
void App_Clock_DisplayByDigitalTubes(struct App_Clock *this, uint8_t time);

/// @brief 维护时间数据合法性
/// @param time 显存中的时间数据地址
void App_Clock_KeepValid(uint8_t *time);

#endif