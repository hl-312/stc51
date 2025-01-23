#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

/// @brief ��С��������С����Ķ��������λP07����1������
static uint8_t s_segmentCodeTable[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

/// @brief ��������ñ�[0]: ������Ϣ; [1]: С���㿪����Ϣ;
static uint8_t s_setting[] = {0xff, 0x00};

/// @brief �Դ棺0-7���������ʾ���ݡ�
static uint8_t s_buffer[8];

void Int_DigitalTube_Init(void)
{
    uint8_t i;
    s_setting[0] = 0xff;
    s_setting[1] = 0x00;
    for (i = 0; i < 8; i++) {
        s_buffer[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        Int_DigitalTube_DisplayOne(i);
        Com_Util_Delay500ms();
    }
    SELECT(0);
    Com_Util_Delay998ms();
}

void Int_DigitalTube_DisplayOne(uint8_t site)
{
    if (s_setting[0] & 0x01 << site) // ���λ����
    {
        SEM = 0x00;                                          // ���ԭ�����ݣ������л�λѡʱ����ʾһ˲�䣬�����Ӱ��
        SELECT(site);                                        // ����λѡΪ��λ��0001 1100b, 8+4=12=0xC
        if (s_setting[1] & 0x01 << site)                     // ���С���㿪��
            SEM = s_segmentCodeTable[s_buffer[site]] | 0x80; // ��ֵ��ʾ���ݣ���С�������Ի�һ��0x80
        else
            SEM = s_segmentCodeTable[s_buffer[site]]; // ��С���㣬ֱ�Ӹ�ֵ
    }
    return;
}

void Int_DigitalTube_DisplayCycle(void)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        SEM = 0;
        Int_DigitalTube_DisplayOne(i);
        Com_Util_Delay1ms();
    }
    SEM = 0;
    return;
}

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

uint8_t *Int_DigitalTube_GetBufferAddress(void)
{
    return s_buffer;
}

void Int_DigitalTube_SetSetting(uint8_t site, uint8_t value)
{
    s_setting[site] = value;
    return;
}
