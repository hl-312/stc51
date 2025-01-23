#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#define SEM       P0
#define SELECT(n) (P2 = P2 & ~0x1c | n << 2)

#include "Com_Util.h"

/// @brief ��ʼ������ܣ�λѡ0���Ҷˣ���ʾ��С����0
void Int_DigitalTube_Init(void);

/// @brief �������ʾ��������
/// @param bitSite
void Int_DigitalTube_DisplayOne(uint8_t bitSite);

/// @brief һ������ 8ms ����ʾ����
void Int_DigitalTube_DisplayCycle(void);

/// @brief ��ʾһ��ʱ�䣬�̶�������
/// @param time ������ʾ����ʱ�䣬ʱ�䵥λ 1s
void Int_DigitalTube_Display(uint8_t time);

/// @brief ��ȡ�Դ�ĵ�ַ
/// @return �Դ�����ĵ�ַ
uint8_t *Int_DigitalTube_GetBufferAddress(void);

/// @brief �����������ʾ��ʽ
/// @param site [0]�ǿ���״̬�� [1]��С���㿪��״̬��
/// @param value ״̬�֣���һ���ֽڱ�ʾ8������ܵ�״̬
void Int_DigitalTube_SetSetting(uint8_t site, uint8_t value);

#endif