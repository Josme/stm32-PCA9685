/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   AT24C02测试（软件模拟I2C）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
		/* USART1 config 115200 8-N-1 */
	unsigned char date[4];
	unsigned char rx[4],buf,i;
 unsigned int delay;
		USART1_Config();

		//printf("eeprom 软件模拟i2c测试例程 \r\n");		
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
