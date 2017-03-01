/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   AT24C02���ԣ����ģ��I2C��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include "pca9685_reg.h" 
#include "pca9685.h" 
 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
		/* USART1 config 115200 8-N-1 */
	unsigned char date[4];
	unsigned char rx[4],buf,i;
 unsigned int delay;
		USART1_Config();

		//printf("eeprom ���ģ��i2c�������� \r\n");		
   // i2c_probe();
	
  init_pca9685(0xf0);
	
	
	pca9685_brightness(100,date);
	
	pca9685_led(0xf0,14,date);
	pca9685_brightness(100,date);
	pca9685_led(0xf0,13,date);
//	i2cWrite(0xf0,0x43,0xff);
//	i2c_ReadBuffer(0xf0,0x43,1,&buf);
	printf("%d",buf);

		for(;;)		{
			
				pca9685_brightness(i++,date);
	i%=100;
			
	pca9685_led(0xf0,15,date);
			delay=0xffff;
			while(delay--);
		}
}
/*********************************************END OF FILE**********************/
