#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#define SEM       P0
#define SELECT(n) (P2 = P2 & ~0x1c | n << 2)

#include "Com_Util.h"

// ��������ñ�[0]: ������Ϣ; [1]: С���㿪����Ϣ; [2-11]: 0-7���������ʾ���ݡ�
extern uint8_t setting[];

/// @brief �������ʾ��������
/// @param bitSite
// ��λ��ʾ���������λ���أ�����λѡ�����С���㣬�������ݣ���ʱ������
void Int_DigitalTube_DisplayOne(uint8_t bitSite);

/// @brief һ������ 8ms ����ʾ����
/// @param
// һ�����ڵ���ʾ����
void Int_DigitalTube_DisplayCycle(void);

/// @brief ��ʾ��������ʾʱ�䵥λ 1s�����ǵ��������õĿ������������õ���΢С��1s�����256s��
/// @param time
void Int_DigitalTube_Display(uint8_t time);

#endif