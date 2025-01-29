#ifndef __APP_CLOCK_H__
#define __APP_CLOCK_H__

#include "Com_Util.h"
#include "Int_DigitalTube.h"

typedef struct App_Clock {
    Int_DigitalTubes_Struct dt;
    int8_t *initTime;
    void (*Display)(struct App_Clock *this, uint8_t time);
} App_Clock;

/// @brief ʹ���������ʵ��ʱ�ӣ����Ҹ���һλ����Сʱ�䵥λ1s��ͨ������ setting���飬��ϢΪ��[0]=0111 1110=0x7e, [1]=0010 1000=0x28;
/// @param time ��ʾʱ�䣺0s~18h.12m.16s
/// @param initTime ��ʽ��"hh.mm.ss"
void App_Clock_DisplayByDigitalTubes(struct App_Clock *this, uint8_t time);

/// @brief ά��ʱ�����ݺϷ���
/// @param time �Դ��е�ʱ�����ݵ�ַ
void App_Clock_KeepValid(uint8_t *time);

#endif