#include <STC89C5XRC.h>
#include <INTRINS.H>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

/*
�������ʾ���ܷ���
�Ѿ�ʵ�֣���������ܵ�������ʾָ�����ݣ�����δ�ع��ɺ�����
Ŀ��ʵ�֣������������ͬʱ��ʾ�������ݣ����Բ�ͬ��
Ӳ�����ƣ�ͬһʱ�䣬ֻ�ܵ������������
������
    �������⣺����ܱ���������ʾ�����һ����ʾ����Ӧ��Ϊ������ʾʱ��*��ʾ������
    Ϊ�˱�֤��ͬ��ʾ��������һ�£�����̶���ʾ����Ϊ8������ʾ��λ�þ�ֻ��ʱ��

    ˢ�������⣺100hz��Ӧ10ms��ȡ8�ı�����8ms��ÿ��������ʾʱ��1ms��ˢ���ʴ��125hz���ң�������˸��

    ��ʾ�������⣺�رգ���С�������֣���С���������������ݡ�
        С���㴦���������ж����������С���������ٵ����г��о����˷ѿռ䣬��ֻ�ڶ����������һ���ֽ�Ϊ 0x80��
        ��ҪС����ľ��Ƕ�Ӧ����� 0x80 ��һ�¼��ɡ��ٿ��ǵ�������Ҫ�ٵ����洢ÿ�������Ƿ���С�������Ϣ��
        �ɴ����һ���ֽڵĸ���λ����ʾ������С����Ķ�����1��������ÿ�����ֵĶ�ӦλΪ 1 ��ʾС������Ч��
        ʹ��ʱ���Ը��ֽ�ֻ������Ӧλ������λ�����λ���������ֵĶ����һ�£������˿ڼ��ɡ�
        �رմ�������С����Ĵ���ʽ����һ���ֽڴ洢��Ӧ����λ�ĵ�����Ϣ��ͬ�� 1 ��Ч��
    ��Ȼ������Ҫλ���Ժ�����var&0x01<<i������λ������λ��ֵ����������λ����ֱ����λ��λ�����λ��101b��
    �ͽ����ȸ�λ&000b����λ|101b����Щ�����Ƚϼ򵥣��꺯�����ɡ�
˼·��
1. ���Ѿ�ʵ�ֵĹ����ع�Ϊ������void displayOneDT(bitSite)�������ڲ��̶���ʾʱ��Ϊ 1ms����ʱ����������ʾ��Ϣ��setting��
2. ��ʾ���ں�����ѭ�����ð˴ε�λ��ʾ����
3. ��ʾ����������ѡ���ܵ���ʾʱ��
��ʼʵ�֡�
*/

// ��С��������С����Ķ��������λP07���� 1 ������
uint8_t segmentCodeTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// ��������ñ�[0]: ������Ϣ; [1]: С���㿪����Ϣ; [2-11]: 0-7���������ʾ���ݡ�
uint8_t setting[] = {0xff, 0x14, 0, 2, 1, 0, 5, 2, 0, 2};

// ��ʱ����
void Delay1ms(void);
// ��λ��ʾ���������λ���أ�����λѡ�����С���㣬�������ݣ���ʱ������
void displayOneDT(uint8_t bitSite);
// һ�����ڵ���ʾ����
void displayCycle(void);
// ��ʾ��������ʾʱ�䵥λ 1s�����ǵ��������õĿ������������õ���΢С��1s�����256s��
void display(uint8_t time);
// ʱ�Ӻ�������ʽ��hh.mm.ss�����Ҹ���һλ����Сʱ�䵥λ1s��
// ��Ӧ������ϢΪ��[0]=0111 1110=0x7e, [1]=0010 1000=0x28;
void display_Timer(uint16_t time, int8_t *initTime);

void main()
{
    int8_t *init_time = "11.59.56";
    display_Timer(60 * 70, init_time);
    while (1) {
    }
}

void Delay1ms(void) //@11.0592MHz
{
    uint8_t data i, j;

    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j);
    } while (--i);
}

void displayOneDT(uint8_t bitSite)
{
    if (setting[0] & 0x01 << bitSite) // ���λ����
    {
        P0 = 0x00;                                              // ���ԭ�����ݣ������л�λѡʱ����ʾһ˲�䣬�����Ӱ��
        P2 = P2 & ~0x1c | bitSite << 2;                         // ����λѡΪ��λ��0001 1100b, 8+4=12=0xC
        if (setting[1] & 0x01 << bitSite)                       // ���С���㿪��
            P0 = segmentCodeTable[setting[bitSite + 2]] | 0x80; // ��ֵ��ʾ���ݣ���С�������Ի�һ��0x80
        else
            P0 = segmentCodeTable[setting[bitSite + 2]]; // ��С���㣬ֱ�Ӹ�ֵ
    }
    Delay1ms();
    P0 = 0x00;
    return;
}

void displayCycle(void)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        displayOneDT(i);
    }
    return;
}

void display(uint8_t time)
{
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // һ������Լ8ms�࣬1000ms/8=125��ȡСһ��123
        {
            displayCycle();
        }
    }
    P0 = 0x00; // ����˿�˳�������Ǻ�ϰ��
}

void display_Timer(uint16_t time, int8_t *initTime)
{
    uint8_t i, j;
    // ���ñ��ʼ��
    setting[0] = 0x7e;
    setting[1] = 0x28;
    setting[9] = 0;
    setting[2] = 0;
    // ʱ���ʼ��
    for (i = 0, j = 0; i < 8; i++) {
        if (initTime[i] >= 48 && initTime[i] <= 57) setting[8 - j++] = initTime[i] - 48; // ��һλ���Դ�8��ʼ
    }
    for (; 0 < time; time--) {
        uint8_t i;
        for (i = 0; i < 123; i++) // һ������Լ8ms�࣬1000ms/8=125��ȡСһ��123
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
    P0 = 0x00; // ����˿�˳�������Ǻ�ϰ��
}
