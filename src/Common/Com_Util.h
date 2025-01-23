/*
工具函数、常规宏定义、所有特定的算法。*PS：可能会被任何层的代码调用*。
*/

#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

void Com_Util_Delay1ms(void);
void Com_Util_Delay500ms(void);
void Com_Util_Delay998ms(void);

#endif
