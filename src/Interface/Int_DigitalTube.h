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
    /// @brief 无小数点段码表，小数点的段码是最高位P07，给1点亮。
    uint8_t *segmentCodeTable;
    /// @brief 数码管配置表，[0]: 开关信息; [1]: 小数点开关信息;
    uint8_t setting[2];
    /// @brief 显存：0-7号数码管显示内容。
    uint8_t buffer[8];
    void (*Init)(struct Int_DigitalTubes_Struct *this);
    void (*DisplayOne)(struct Int_DigitalTubes_Struct *this, uint8_t site);
    void (*DisplayCycle)(struct Int_DigitalTubes_Struct *this);
    void (*Display)(struct Int_DigitalTubes_Struct *this, uint8_t time);
} Int_DigitalTubes_Struct;

/// @brief 构造函数
/// @param 必须在函数外部先声明这么一个变量，并且第一次初始化只能直接调用这个函数

/// @brief 初始化数码管，位选0最右端，显示无小数点0
void Int_DigitalTubes_Init(struct Int_DigitalTubes_Struct *this);

/// @brief 数码管显示单个数字
/// @param bitSite
void Int_DigitalTubes_DisplayOne(struct Int_DigitalTubes_Struct *this, uint8_t site);

/// @brief 一个周期 8ms 的显示函数
void Int_DigitalTubes_DisplayCycle(struct Int_DigitalTubes_Struct *this);

/// @brief 显示一段时间，固定的数字
/// @param time 设置显示的总时间，时间单位 1s
void Int_DigitalTubes_Display(struct Int_DigitalTubes_Struct *this, uint8_t time);

#endif