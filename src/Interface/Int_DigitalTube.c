#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

// ��С��������С����Ķ��������λP07���� 1 ������
static uint8_t s_segmentCodeTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8_t setting[]                   = {0xff, 0x14, 0, 2, 1, 0, 5, 2, 0, 2};

/// @brief �������ʾ��������
/// @param site
void Int_DigitalTube_DisplayOne(uint8_t site)
{
    if (setting[0] & 0x01 << site) // ���λ����
    {
        SEM = 0x00;                                             // ���ԭ�����ݣ������л�λѡʱ����ʾһ˲�䣬�����Ӱ��
        SELECT(site);                                              // ����λѡΪ��λ��0001 1100b, 8+4=12=0xC
        if (setting[1] & 0x01 << site)                             // ���С���㿪��
            SEM = s_segmentCodeTable[setting[site + 2]] | 0x80; // ��ֵ��ʾ���ݣ���С�������Ի�һ��0x80
        else
            SEM = s_segmentCodeTable[setting[site + 2]]; // ��С���㣬ֱ�Ӹ�ֵ
    }
    Com_Util_Delay1ms();
    SEM = 0x00;
    return;
}

/// @brief һ������ 8ms ����ʾ����
/// @param
void Int_DigitalTube_DisplayCycle(void)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        Int_DigitalTube_DisplayOne(i);
    }
    return;
}

/// @brief ��ʾ��������ʾʱ�䵥λ 1s�����ǵ��������õĿ������������õ���΢С��1s�����256s��
/// @param time
void Int_DigitalTube_Display(uint8_t time)
{
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // һ������Լ8ms�࣬1000ms/8=125��ȡСһ��123
        {
            Int_DigitalTube_DisplayCycle();
        }
    }
    SEM = 0x00; // ����˿�˳�������Ǻ�ϰ��
}