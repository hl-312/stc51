#include "App_ClockByDigitalTubes.h"
#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

void display_Timer(uint16_t time, int8_t *initTime)
{
    uint8_t i, j;
    // 配置表初始化
    setting[0] = 0x7e;
    setting[1] = 0x28;
    setting[9] = 0;
    setting[2] = 0;
    // 时间初始化
    for (i = 0, j = 0; i < 8; i++) {
        if (initTime[i] >= 48 && initTime[i] <= 57) setting[8 - j++] = initTime[i] - 48; // 空一位所以从8开始
    }
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // 一个周期约8ms多，1000ms/8=125，取小一点123
        {
            displayCycle();
        }
        setting[3]++;
        if (setting[3] > 9) {
            setting[3] = 0;
            setting[4]++;
        }
        if (setting[4] > 5) {
            setting[4] = 0;
            setting[5]++;
        }
        if (setting[5] > 9) {
            setting[5] = 0;
            setting[6]++;
        }
        if (setting[6] > 5) {
            setting[6] = 0;
            setting[7]++;
        }
        if (setting[8] == 0) {
            if (setting[7] > 9) {
                setting[7] = 0;
                setting[8]++;
            }
        } else if (setting[8] == 1) {
            if (setting[7] > 1) {
                setting[7] = 0;
                setting[8] = 0;
            }
        }
    }
    P0 = 0x00; // 用完端口顺手清理是好习惯
}