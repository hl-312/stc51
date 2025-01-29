#include "Int_DigitalTube.h"
#include "App_Clock.h"
#include <STC89C5xRC.H>
/*
数码管显示功能分析
已经实现：任意数码管点亮并显示指定内容，但还未重构成函数。
目标实现：任意多个数码管同时显示任意内容，可以不同。
硬件限制：同一时间，只能点亮单个数码管
分析：
    亮度问题：数码管必须依次显示，因此一组显示周期应当为单个显示时间*显示个数，
    为了保证不同显示个数亮度一致，建议固定显示个数为8，不显示的位置就只延时。

    刷新率问题：100hz对应10ms，取8的倍数，8ms，每个数字显示时间1ms，刷新率大概125hz左右，不会闪烁。

    显示内容问题：关闭，无小数点数字，有小数点数字三种内容。
        小数点处理：数字已有段码表，若是有小数点数字再单独列出感觉很浪费空间，若只在段码表里增加一个字节为 0x80，
        需要小数点的就那对应段码和 0x80 或一下即可。再考虑到这样需要再单独存储每个数字是否有小数点的信息，
        干脆就用一个字节的各个位来表示，由于小数点的段码置1亮，所以每个数字的对应位为 1 表示小数点有效，
        使用时，对该字节只保留对应位，再移位至最高位，再与数字的段码或一下，赋给端口即可。
        关闭处理：仿照小数点的处理方式，用一个字节存储对应数字位的点亮信息，同样 1 有效。
    显然，我需要位测试函数（var&0x01<<i），移位函数，位赋值函数（单个位可以直接置位或复位，多个位如101b，
    就建议先复位&000b再置位|101b）这些函数比较简单，宏函数即可。
思路：
1. 将已经实现的功能重构为函数：void Int_DigitalTube_DisplayOne(bitSite)，函数内部固定显示时间为 1ms（延时函数），显示信息查setting表
2. 显示周期函数，循环调用八次单位显示函数
3. 显示函数，可以选择总的显示时长
开始实现。
*/

void main()
{
    App_Clock ac;
    Int_DigitalTubes_Init(&ac.dt);
    ac.Display  = App_Clock_DisplayByDigitalTubes;
    ac.initTime = "23.59.58";
    ac.Display(&ac, 5);
    while (1) {
    }
}
