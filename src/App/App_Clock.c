#include "App_Clock.h"
#include <STC89C5xRC.H>

void App_Clock_DisplayByDigitalTubes(struct App_Clock *this, uint16_t time)
{
    uint8_t i, j;
    // 配置表初始化
    this->dt.setting[0] = 0x7e; // 0x7e=0111 1110b
    this->dt.setting[1] = 0x28; // 0x28=0010 1000b
    // 时间初始化
    for (i = 0, j = 0; i < 8; i++) {
        if (this->initTime[i] >= 48 && this->initTime[i] <= 57)
            this->dt.buffer[6 - j++] = this->initTime[i] - 48; // 空一位所以从6开始
    }
    for (; 0 < time; time = time - 1) {
        this->dt.Display(&this->dt, 1);
        this->dt.buffer[1]++;
        App_Clock_KeepValid(&this->dt.buffer[1]);
        SEM = 0x00; // 用完端口顺手清理是好习惯
    }
    return;
}

void App_Clock_KeepValid(uint8_t *time)
{
    uint8_t second = 0, minute = 0, hour = 0;
    second = time[1] * 10 + time[0];
    minute = time[3] * 10 + time[2];
    hour   = time[5] * 10 + time[4];
    if (second > 59) {
        second = 0;
        minute++;
    }
    if (minute > 59) {
        minute = 0;
        hour++;
    }
    if (hour > 23) {
        hour = 0;
    }
    time[0] = second % 10;
    time[1] = second / 10;
    time[2] = minute % 10;
    time[3] = minute / 10;
    time[4] = hour % 10;
    time[5] = hour / 10;
    return;
}