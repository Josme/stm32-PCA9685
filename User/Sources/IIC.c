
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
#define  BUS_CLOCK		   32000000	   //总线频率
#define  OSC_CLOCK		   16000000	   //晶振频率
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
/*/ 要发送到PCA9685的数据寄存器初始化和pwm占空比 */
volatile unsigned int kuozhan_pwm_TAB[16]={ 0x80,0x00,0x20,0x1c,0x66,0x44,0x22};
/*实时运行而得到的pwm占空比数据要转换以后才能发送到PCA9685*/


/*************************************************************/
/*                        延时函数                           */
/*************************************************************/
void delay(void) 
{
 unsigned int i;
 for(i=0;i<5000;i++);
}

/*************************************************************/
/*            写PCA9685单个寄存器                            */
/*        函数类型byte形参PCA9685地址byte,                   */
/*        要写入寄存器的地址byte,                            */
/*        要写入寄存器的数值byte,                            */
/*************************************************************/
unsigned char WritePCA9685REG_1(unsigned char address,unsigned char REG,unsigned char value){
  I2Cstart();//启动总线开始发送数据
  I2Csend(address) ;//发送要接受数据的器件地址
    if (I2Creadack())
  return 0xff;    //读取应答码
  I2Csend(REG) ;//发送要写入寄存器的地址
    if (I2Creadack())
  return 0xff;    //读取应答码
  I2Csend(value) ; //发送要写入寄存器的参数值
    if (I2Creadack())
  return 0xff;    //读取应答码
  I2Cstop();
  return 0;

}
/*************************************************************/
/*            自动写PCA9685所有寄存器自动增量                */                    
/*            要写入寄存器的数值表,                          */
/*************************************************************/

unsigned char AutoWritePCA9685(volatile unsigned char tap[]){
     unsigned char *p=0;
     unsigned char i=0;
     unsigned char temp=0;
     I2Cstart();//启动总线开始发送数据
     for (;i<=70;i++) {
     temp=tap[i];     
     I2Csend(temp) ;//发送要接受数据的器件地址
     if (!I2Creadack())
     return 0xff;    //读取应答码
     p++;
     }
     I2Cstop();
     return 0;
     }


/*************************************************************/
/*     要写入PCA9685的pwm值数据转换uint to uchar 16转12位    */
/*        函数类型void形参PCA9685地址byte,                   */
/*        要写入寄存器的地址byte,                            */
/*        要写入寄存器的数值byte,                            */
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
/*                         主函数                            */
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
      //receivedata = I2Creceive();      //读取数据
      //I2Cstop();
      // LED=receivedata;                 //显示读取到的数据
  }
}






