#ifndef _BSP_I2C_GPIO_H
#define _BSP_I2C_GPIO_H

#include <inttypes.h>

#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */

void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);
void i2c_probe(void) ;
uint8_t i2c_ReadBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
uint8_t i2c_WriteBuffer(uint8_t addr, char * data,uint8_t len );
#endif
