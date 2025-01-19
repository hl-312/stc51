#include <STC89C5XRC.h>
#include <INTRINS.H>

// ռ�ձȷֱ��ʿ��� PWM
// ���ڳ��� = Frequency*Resolution = 1ms = 1000hz
#define FREQUENCY Delay10us()
// ռ�ձȣ�ȡֵ��ΧΪ0~resolution-1��0=0%, resolution=100%
#define DUTYCYCLE0123 5
#define DUTYCYCLE4567 90
// �ֱ��� = 1/resolution
#define RESOLUTION 100

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

// delay 100us
void Delay10us(void);

// Ҫʵ�ֲ�ͬռ�ձ��ź�������led����
void main()
{
    uint8_t i = 0;
    while (1) {
        // ���ﲻ��ȡ�࣬�ø������ļ������㣬���仯��Χ������ 0~RESOLUTION
        // ����ֵӦ���ǵ��·�ռ�ձȴ�С�����ȴ�С�Ķ�Ӧ��ϵ��ϰ���Ͼ��ã�
        // �·�if�������Խ��Ӧ��Խ�������Գ�ֵӦ��Ϊȫ����Ȼ�������Ϩ��
        // ʵ��֤�����������������ڵ�if��䣬֮���ʱ�䶼������led�����ۿɼ������ȡ�
        // ����0%��ռ�ձ�ֻ���ڸ���ֵ����ֱ�����á�
        if (i == 0) P2 = 0x00;
        // ��λһͬ��ֵ����ʹ�ø�ʽ��var = var & ~0x09 | 0x09; ��������ͬʱ����0��1��
        // ֮����Ҫ�ڸ�λ������ȡ���ţ�����Ϊת��Ϊ16���ƺü��㣬��1011����д��~0100����~0x4
        if (i == DUTYCYCLE0123) P2 = P2 & ~0x0f | 0x0f;
        if (i == DUTYCYCLE4567) P2 = P2 & ~0xf0 | 0xf0;
        // ������һ�����ڣ��ͻָ���ֵ
        FREQUENCY;
        i++;
        // ��ֵά���������� i++ ���棬����ᵼ�� i ��������Ϊ 0�����е���һ�º�ȫ��
        if (i == RESOLUTION) i = 0;
    };
}

void Delay10us(void) //@11.0592MHz
{
    unsigned char data i;

    i = 2;
    while (--i);
}
