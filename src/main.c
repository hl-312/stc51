#include <STC89C5XRC.h>
#include <INTRINS.H>

// �� P22-P24 ��ֵ��ѡ�������λ��������������λ�ţ�ʹ��ʱ���ֺţ����ֱ�Ŵ������� 0~7
#define DIGITALTUBESBIT(n) P2 = P2 & ~0x1c | n << 2
// ������ܶ�Ӧ��IO�˿ڸ�ֵ
#define DIGITALTUBESSEGMENT P0
#define TESTBIT(var, n)     (var & (0x01 << n))
// �� led �����Գ���ִ��λ�ã���bug����Ҫ��main�Ŀ�ʼ�ȵ��� P20
#define LOG P20 = 1;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

typedef struct digitalBit {
    uint8_t point;   // 0��1��
    uint8_t content; // ��ʾ����
} digitalBit;

typedef struct digitalArray {
    uint8_t bitFlag;     // ��1��
    digitalBit array[8]; // ����ܵ�λ����
} digitalArray;

// ����С�����������С����Ķ��������λ P07����1����
uint8_t segmentCodeTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// �򻯵�������������飬-1 ��ʾ��0-9��ʾ��Ӧ���֣�10-19��ʾ��С����
int8_t settingDigitalTubes[] = {0, 0, 0, -1, 10, 0, 0, 0};
// 1ms ��ʱ��
void Delay1ms(void);
// ��������ݳ�ʼ��������settingDigitalTubes����digitalTubes
void initialDigitalTubes(digitalArray *dA);
// һ�����ڵ���ʾ������8ms
void DisplayCycle(digitalArray *darray);
// 1s ��ʾ����
void digitalDisplay(digitalArray *darray);

/*
����ܶ�̬��ʾ���ܷ�����
1. ����Ӳ����֧��ȫ��ͬʱ����
2. Ϊ��֤ȫ��������Ч������Ҫ�������ֵ�ˢ���ʳ���60hz��Խ��Խ��
3. �ܹ�8�����֣�ÿ��������ʾһ����Ҫ��ȥ��һ�����֣��ٸ��ݵ�һ�㣬��ˣ�һ��������Ȼ�ֳ��˰˶Σ�
ÿ�����ֵ�ռ�ձ���Ȼ����1/8������������Ȼ�����һЩ����������ʾ������ͬ�ģ�����Ӳ������Ҳû��ͬʱ������
�����ʾ������Խ�࣬�������ƻ�Խ���ԣ�����ÿ����������Խ��Խ����
4. ÿ�����ֵ���ʾ���� = 8*����ʱ�� = ˢ���ʵ�����
����ˢ����Ҫ��100hz������ʾ����10ms��10/8Ϊ�������ֵĵ���ʱ�䡣���ֲ�������������ȡС�㣬8ms��
��������Ҫһ��1ms�Ķ�ʱ����Ȼ���ǵ��ı���ʾ���ݵ���������ı�Ҫ��̫���ˣ��϶����У�Ҫ��Ȼ��˸��
Ҫ��Ȼ�������ĵط�Ҳ��΢�������⣬�ͽ��ı�����Ϊ1s�ɣ���һ��������װ����ʵ��1sʱ�����ʾ��
����Ҳ�ܷ��֣�������ʾʱ��̫�࣬�������õĿ���Ҳ��Ӱ��ռ�ձȡ�
���������˵��ÿ������Ӧ����������״̬�����ַ���û��С���㣬ÿ���ַ�0-9ʮ�����֡�ʹ�ýṹ������ʾ��
*/
void main()
{
    digitalArray digitalTubes;
    initialDigitalTubes(&digitalTubes);
    while (1) {
        digitalDisplay(&digitalTubes);
    }
}

void Delay1ms(void) //@11.0592MHz
{
    unsigned char data i, j;

    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j);
    } while (--i);
}

void initialDigitalTubes(digitalArray *dA)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (settingDigitalTubes[i] < 0)
            dA->bitFlag = dA->bitFlag & ~0x01 << i; // ����Ӧλ��0��Ϩ��
        else if (settingDigitalTubes[i] >= 0 && settingDigitalTubes[i] < 10) {
            dA->bitFlag          = dA->bitFlag | 0x01 << i; // ����Ӧλ��1�����
            dA->array[i].point   = 0;
            dA->array[i].content = segmentCodeTable[settingDigitalTubes[i]];
        } else if (settingDigitalTubes[i] > 9) {
            dA->bitFlag          = dA->bitFlag | 0x01 << i; // ����Ӧλ��1�����
            dA->array[i].point   = 1;
            dA->array[i].content = segmentCodeTable[settingDigitalTubes[i] - 10];
        }
    }
    return;
}

void DisplayCycle(digitalArray *dA)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (TESTBIT(dA->bitFlag, i)) {
            DIGITALTUBESBIT(i);
            DIGITALTUBESSEGMENT = dA->array[i].content & ~(dA->array[i].point << 7) | (dA->array[i].point << 7);
        }
        Delay1ms();
    }
    return;
}

void digitalDisplay(digitalArray *dA)
{
    uint8_t timer = 123; // ���ǵ��������õĿ�������1000/8=125��СһЩ��
    while (timer--) {
        DisplayCycle(dA);
    }
    return;
}
