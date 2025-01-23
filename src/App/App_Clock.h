#ifndef __APP_CLOCK_H__
#define __APP_CLOCK_H__

#include "Com_Util.h"

/// @brief ʹ���������ʵ��ʱ�ӣ����Ҹ���һλ����Сʱ�䵥λ1s��ͨ������ setting���飬��ϢΪ��[0]=0111 1110=0x7e, [1]=0010 1000=0x28;
/// @param time ��ʾʱ�䣺0s~18h.12m.16s
/// @param initTime ��ʽ��"hh.mm.ss"
void App_Clock_DisplayByDigitalTubes(uint16_t time, int8_t *initTime);

#endif