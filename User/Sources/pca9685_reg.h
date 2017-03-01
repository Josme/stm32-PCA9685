#ifndef __PCA9685_H
#define __PCA9685_H

/* Devices */
#define LEDDRV1    0xb8
#define LEDDRV2    0xba
#define LEDDRV3    0xd8
#define LEDDRV4    0xda
#define LEDDRV5    0xc8
#define LEDDRV6    0xca

/* Registers */
#define PCA9685_BASE          	 0x01
#define PCA9685_MODE1            0x00
#define PCA9685_MODE2            0x01
#define PCA9685_SUBADR1            0x02
#define PCA9685_SUBADR2            0x03
#define PCA9685_SUBADR3            0x04
#define PCA9685_ALLCALLADR        0x05
#define PCA9685_LED0_ON_L        0x06
#define PCA9685_LED0_ON_H        0x07
#define PCA9685_LED0_OFF_L        0x08
#define PCA9685_LED0_OFF_H        0x09
#define PCA9685_LED1_ON_L        0x0a
#define PCA9685_LED1_ON_H        0x0b
#define PCA9685_LED1_OFF_L        0x0c
#define PCA9685_LED1_OFF_H        0x0d
#define PCA9685_LED2_ON_L        0x0e
#define PCA9685_LED2_ON_H        0x0f
#define PCA9685_LED2_OFF_L        0x10
#define PCA9685_LED2_OFF_H        0x11
#define PCA9685_LED3_ON_L        0x12
#define PCA9685_LED3_ON_H        0x13
#define PCA9685_LED3_OFF_L        0x14
#define PCA9685_LED3_OFF_H        0x15
#define PCA9685_LED4_ON_L        0x16
#define PCA9685_LED4_ON_H        0x17
#define PCA9685_LED4_OFF_L        0x18
#define PCA9685_LED4_OFF_H        0x19
#define PCA9685_LED5_ON_L        0x1a
#define PCA9685_LED5_ON_H        0x1b
#define PCA9685_LED5_OFF_L        0x1c
#define PCA9685_LED5_OFF_H        0x1d
#define PCA9685_LED6_ON_L        0x1e
#define PCA9685_LED6_ON_H        0x1d
#define PCA9685_LED6_OFF_L        0x20
#define PCA9685_LED6_OFF_H        0x21
#define PCA9685_LED7_ON_L        0x22
#define PCA9685_LED7_ON_H        0x23
#define PCA9685_LED7_OFF_L        0x24
#define PCA9685_LED7_OFF_H        0x25
#define PCA9685_LED8_ON_L        0x26
#define PCA9685_LED8_ON_H        0x27
#define PCA9685_LED8_OFF_L        0x28
#define PCA9685_LED8_OFF_H        0x29
#define PCA9685_LED9_ON_L        0x2a
#define PCA9685_LED9_ON_H        0x2b
#define PCA9685_LED9_OFF_L        0x2c
#define PCA9685_LED9_OFF_H        0x2d
#define PCA9685_LED10_ON_L        0x2e
#define PCA9685_LED10_ON_H        0x2f
#define PCA9685_LED10_OFF_L        0x30
#define PCA9685_LED10_OFF_H        0x31
#define PCA9685_LED11_ON_L        0x32
#define PCA9685_LED11_ON_H        0x33
#define PCA9685_LED11_OFF_L        0x34
#define PCA9685_LED11_OFF_H        0x35
#define PCA9685_LED12_ON_L        0x36
#define PCA9685_LED12_ON_H        0x37
#define PCA9685_LED12_OFF_L        0x38
#define PCA9685_LED12_OFF_H        0x39
#define PCA9685_LED13_ON_L        0x3a
#define PCA9685_LED13_ON_H        0x3b
#define PCA9685_LED13_OFF_L        0x3c
#define PCA9685_LED13_OFF_H        0x3d
#define PCA9685_LED14_ON_L        0x3e
#define PCA9685_LED14_ON_H        0x3f
#define PCA9685_LED14_OFF_L        0x40
#define PCA9685_LED14_OFF_H        0x41
#define PCA9685_LED15_ON_L        0x42
#define PCA9685_LED15_ON_H        0x43
#define PCA9685_LED15_OFF_L        0x44
#define PCA9685_LED15_OFF_H        0x45
#define PCA9685_ALL_LED_ON_L       0xfa
#define PCA9685_ALL_LED_ON_H       0xfb
#define PCA9685_ALL_LED_OFF_L      0xfc
#define PCA9685_ALL_LED_OFF_H      0xfd
#define PCA9685_PRE_SCALE      0xfe     //Ҫ��ֵΪ30�����pwmƵ��200���ȡ�

/* MODE1 bits */
#define PCA9685_RESTART    0x80  // ����λ��1������0��Ч��
/*���PCA9685�������û�������оƬ˯��������MODE1
��4λ��û��ֹͣ�κε�PWMͨ��������λ��MODE1��7λ��
��PWMˢ�����ڽ���ʱ������Ϊ�߼�1��ÿ��PWM�Ĵ�����������
������Ч��ʱ���رա�
Ҫ��������������ǰ�Ļ��I2C�������ڵ�PWMͨ������
�������£�
1���Ķ�MODE1�Ĵ�����
2�����ĵ�7λ������������Ϊ�߼�1������ǵĻ��������ĵ�4λ�����ߣ����ȴ�һ��ʱ��
�����ȶ���500΢�룩��
3������׫дMODE1�Ĵ����߼�1���ڵĵ�7λ�����е�PWMͨ��������������
RESTARTλ�������*/
#define PCA9685_EXTCLK    0x40   //����ѡ��0�ڲ�1�ⲿ
#define PCA9685_AI    0x20       //�Ĵ����Զ�����λ0��ʹ�ã�1ʹ��
#define PCA9685_SLEEP    0x10    //˯��ģʽ��0��ͨ1˯�߾���ֹͣ
#define PCA9685_SUB1    0x08     //0PCA9685����ӦI2C�����ӵ�ַ1��1PCA9685��ӦI2C�����ӵ�ַ1��
#define PCA9685_SUB2    0x04     //0PCA9685����ӦI2C�����ӵ�ַ2��1PCA9685��ӦI2C�����ӵ�ַ2?
#define PCA9685_SUB3    0x02     //0PCA9685����ӦI2C�����ӵ�ַ3��1PCA9685��ӦI2C�����ӵ�ַ3?
#define PCA9685_ALLCALL    0x01  //0PCA9685����ӦLED���к���I2C���ߵ�ַ,1PCA9685��ӦLED�����к���I2C���ߵ�ַ��



/* MODE2 bits */
#define PCA9685_INVRT    0x10    //0�������ת1�����ת��
#define PCA9685_OCH    0x08      //0����ı���STOP���1 ����ı���ACK.Ӧ�����������1���ı��ٶȿ졣
#define PCA9685_OUTDRV    0x04   //0�������Ϊ��©��1�������Ϊ�������ͼ�����ṹ��
#define PCA9685_OUTNE1    0x02
#define PCA9685_OUTNE0    0x01   /*�����OUTDRV�����й�������00����ô��������߼���(��OE=1ʱ)��
                                  ����01��OUTDRV=1��������߼���,OUTDRV = 0��������Ǹ���(��OE=1ʱ)��
                                  ����10��11������Ǹ���(��OE=1ʱ)��
                                  /*00, *��OE = 1�����������δ���ã���LEDN=0��
                                    01����OE = 1�����������δ���ã���
                                        LEDN=1��OUTDRV= 1
                                        LEDN=�����迹OUTDRV=0��ͬΪOUTNE[1:0] = 10��
                                    1X,��OE= 1�����������δ���ã���LEDN=���迹��*/
/* LEDX_ON_H bits */
#define PCA9685_LED_ON 0x10

/* LEDX_OFF_H bits */
#define PCA9685_LED_OFF 0x10

#define PCA9685_LED_BUFSIZ       0x04
#define PCA9685_BASE(led) ((led * 4) + 6)
#define PCA9685_BASE_RGBA(led) (led * 16 + 6)
#define PCA9685_LED_ON_L       0x00
#define PCA9685_LED_ON_H       0x01
#define PCA9685_LED_OFF_L      0x02
#define PCA9685_LED_OFF_H      0x03
#define PCA9685_ALL_LEDS    -1

#define LEDn_ON_L(n)		(0x06 + (n)*4)
#define LEDn_ON_H(n)		(0x07 + (n)*4)
#define LEDn_OFF_L(n)		(0x08 + (n)*4)
#define LEDn_OFF_H(n)		(0x09 + (n)*4)

#endif