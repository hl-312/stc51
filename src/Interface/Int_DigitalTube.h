#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#define SEM       P0
#define SELECT(n) (P2 = P2 & ~0x1c | n << 2)

#include "Com_Util.h"

typedef enum Int_DigitalTubes_Type {
    CATHODE,
    ANODE
} Int_DigitalTubes_Type;

typedef struct Int_DigitalTubes_Struct {
    Int_DigitalTubes_Type type;
    /// @brief ��С��������С����Ķ��������λP07����1������
    uint8_t *segmentCodeTable;
    /// @brief ��������ñ�[0]: ������Ϣ; [1]: С���㿪����Ϣ;
    uint8_t setting[2];
    /// @brief �Դ棺0-7���������ʾ���ݡ�
    uint8_t buffer[8];
    void (*Init)(struct Int_DigitalTubes_Struct *this);
    void (*DisplayOne)(struct Int_DigitalTubes_Struct *this, uint8_t site);
    void (*DisplayCycle)(struct Int_DigitalTubes_Struct *this);
    void (*Display)(struct Int_DigitalTubes_Struct *this, uint8_t time);
} Int_DigitalTubes_Struct;

/// @brief ���캯��
/// @param �����ں����ⲿ��������ôһ�����������ҵ�һ�γ�ʼ��ֻ��ֱ�ӵ����������

/// @brief ��ʼ������ܣ�λѡ0���Ҷˣ���ʾ��С����0
void Int_DigitalTubes_Init(struct Int_DigitalTubes_Struct *this);

/// @brief �������ʾ��������
/// @param bitSite
void Int_DigitalTubes_DisplayOne(struct Int_DigitalTubes_Struct *this, uint8_t site);

/// @brief һ������ 8ms ����ʾ����
void Int_DigitalTubes_DisplayCycle(struct Int_DigitalTubes_Struct *this);

/// @brief ��ʾһ��ʱ�䣬�̶�������
/// @param time ������ʾ����ʱ�䣬ʱ�䵥λ 1s
void Int_DigitalTubes_Display(struct Int_DigitalTubes_Struct *this, uint8_t time);

#endif