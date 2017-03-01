
#include "stm32f10x.h"
#include "pca9685_reg.h"                         
#include "bsp_i2c_gpio.h"

#define SCL PTJ_PTJ7 
#define SDA PTJ_PTJ6 
#define SCL_dir DDRJ_DDRJ7
#define SDA_dir DDRJ_DDRJ6
#define OE PORTK_PK0
#define OE_dir DDRK_DDRK0
#define LED PORTB
#define LED_dir DDRB
#define  BUS_CLOCK		   32000000	   //����Ƶ��
#define  OSC_CLOCK		   16000000	   //����Ƶ��
#define I2Cstart   i2c_Start
#define I2Csend    i2c_SendByte
#define I2Creadack i2c_WaitAck
#define I2Cstop    i2c_Stop
#define somenop(); asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
unsigned char receivedata = 0;
volatile unsigned char AutoWritePCA9685_TAB[71]={ 0x80,0x00,0x20,0x1c,0x66,0x44,0x22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/*/ Ҫ���͵�PCA9685�����ݼĴ�����ʼ����pwmռ�ձ� */
volatile unsigned int kuozhan_pwm_TAB[16]={ 0x80,0x00,0x20,0x1c,0x66,0x44,0x22};
/*ʵʱ���ж��õ���pwmռ�ձ�����Ҫת���Ժ���ܷ��͵�PCA9685*/


/*************************************************************/
/*                        ��ʱ����                           */
/*************************************************************/
void delay(void) 
{
 unsigned int i;
 for(i=0;i<5000;i++);
}

/*************************************************************/
/*            дPCA9685�����Ĵ���                            */
/*        ��������byte�β�PCA9685��ַbyte,                   */
/*        Ҫд��Ĵ����ĵ�ַbyte,                            */
/*        Ҫд��Ĵ�������ֵbyte,                            */
/*************************************************************/
unsigned char WritePCA9685REG_1(unsigned char address,unsigned char REG,unsigned char value){
  I2Cstart();//�������߿�ʼ��������
  I2Csend(address) ;//����Ҫ�������ݵ�������ַ
    if (I2Creadack())
  return 0xff;    //��ȡӦ����
  I2Csend(REG) ;//����Ҫд��Ĵ����ĵ�ַ
    if (I2Creadack())
  return 0xff;    //��ȡӦ����
  I2Csend(value) ; //����Ҫд��Ĵ����Ĳ���ֵ
    if (I2Creadack())
  return 0xff;    //��ȡӦ����
  I2Cstop();
  return 0;

}
/*************************************************************/
/*            �Զ�дPCA9685���мĴ����Զ�����                */                    
/*            Ҫд��Ĵ�������ֵ��,                          */
/*************************************************************/

unsigned char AutoWritePCA9685(volatile unsigned char tap[]){
     unsigned char *p=0;
     unsigned char i=0;
     unsigned char temp=0;
     I2Cstart();//�������߿�ʼ��������
     for (;i<=70;i++) {
     temp=tap[i];     
     I2Csend(temp) ;//����Ҫ�������ݵ�������ַ
     if (!I2Creadack())
     return 0xff;    //��ȡӦ����
     p++;
     }
     I2Cstop();
     return 0;
     }


/*************************************************************/
/*     Ҫд��PCA9685��pwmֵ����ת��uint to uchar 16ת12λ    */
/*        ��������void�β�PCA9685��ַbyte,                   */
/*        Ҫд��Ĵ����ĵ�ַbyte,                            */
/*        Ҫд��Ĵ�������ֵbyte,                            */
/*************************************************************/
void PCA9685PWM_convert(void){
     unsigned char i=10,ii,a;
     unsigned char pwm[2];
     unsigned int aa,bb;
     float d;
     for (ii=0;ii<=15;ii++){
      
     aa=kuozhan_pwm_TAB[ii];
     d=(float)(aa)/2.4;
     bb=(unsigned int)(d);
     pwm[0]=bb&0X00ff;
     bb=bb>>8;
     pwm[1]=bb&0x00ff;
     for (a=0;a<=1;a++){
     AutoWritePCA9685_TAB[i]=pwm[a];
     i++;}
     i+=2; 
     }
     } 

/*************************************************************/
/*                         ������                            */
/*************************************************************/
void test(void) {



  for(;;)
  {   
      delay();
      PCA9685PWM_convert( );
      if(WritePCA9685REG_1(LEDDRV1,PCA9685_MODE1,0x20))
				printf("WritePCA9685REG_1 error1");
		 i2cWrite(LEDDRV1,PCA9685_LED15_ON_L,0xff);
	  i2cWrite(LEDDRV1,PCA9685_LED15_ON_H,0x0f);
		i2cWrite(LEDDRV1,PCA9685_LED15_OFF_L,0xff);
		i2cWrite(LEDDRV1,PCA9685_LED15_OFF_H,0x0f);
				
     if( WritePCA9685REG_1(LEDDRV1,PCA9685_PRE_SCALE,30))
			printf("WritePCA9685REG_1 error1");
     // AutoWritePCA9685(AutoWritePCA9685_TAB);
    
      for(;;){
      ;}//I2Cstart();
      //I2Csend(0b01110001);
      //LED=I2Creadack();
      //receivedata = I2Creceive();      //��ȡ����
      //I2Cstop();
      // LED=receivedata;                 //��ʾ��ȡ��������
  }
}






