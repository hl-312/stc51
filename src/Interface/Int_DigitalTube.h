#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#include "Com_Util.h"

// 数码管配置表，[0]: 开关信息; [1]: 小数点开关信息; [2-11]: 0-7号数码管显示内容。
extern uint8_t setting[];

/// @brief 数码管显示单个数字
/// @param bitSite
// 单位显示函数。检查位开关，设置位选，检查小数点，设置内容，延时，返回
void displayOneDT(uint8_t bitSite);

/// @brief 一个周期 8ms 的显示函数
/// @param
// 一个周期的显示函数
void displayCycle(void);

/// @brief 显示函数，显示时间单位 1s，考虑到函数调用的开销，可以设置的略微小于1s。最大256s。
/// @param time
void display(uint8_t time);

#endif