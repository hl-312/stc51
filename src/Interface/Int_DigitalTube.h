#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#define SEM       P0
#define SELECT(n) (P2 = P2 & ~0x1c | n << 2)

#include "Com_Util.h"

/// @brief 初始化数码管，位选0最右端，显示无小数点0
void Int_DigitalTube_Init(void);

/// @brief 数码管显示单个数字
/// @param bitSite
void Int_DigitalTube_DisplayOne(uint8_t bitSite);

/// @brief 一个周期 8ms 的显示函数
void Int_DigitalTube_DisplayCycle(void);

/// @brief 显示一段时间，固定的数字
/// @param time 设置显示的总时间，时间单位 1s
void Int_DigitalTube_Display(uint8_t time);

/// @brief 获取显存的地址
/// @return 显存数组的地址
uint8_t *Int_DigitalTube_GetBufferAddress(void);

/// @brief 设置数码管显示格式
/// @param site [0]是开关状态字 [1]是小数点开关状态字
/// @param value 状态字，用一个字节表示8个数码管的状态
void Int_DigitalTube_SetSetting(uint8_t site, uint8_t value);

#endif