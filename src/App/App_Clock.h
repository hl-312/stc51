#ifndef __APP_CLOCK_H__
#define __APP_CLOCK_H__

#include "Com_Util.h"

/// @brief 使用数码管来实现时钟，左右各空一位，最小时间单位1s。通过配置 setting数组，信息为：[0]=0111 1110=0x7e, [1]=0010 1000=0x28;
/// @param time 显示时间：0s~18h.12m.16s
/// @param initTime 格式："hh.mm.ss"
void App_Clock_DisplayByDigitalTubes(uint16_t time, int8_t *initTime);

/// @brief 维护时间数据合法性
/// @param size 有几个数据，如只有秒？只有秒和分？秒分时都有？
/// @param sec 秒的数据地址
/// @param min 分的数据地址
/// @param h 时的数据地址
void App_Clock_KeepValid(uint8_t *time);

#endif