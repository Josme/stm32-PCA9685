/* I2C bus Functions */
#ifndef _PCA9685_H
#define _PCA9685_H

#include <inttypes.h>
void i2c_probe(void);

void init_pca9685(unsigned char address);
void channel_light(unsigned char ch, unsigned char lev);
void pca9685_led(unsigned char addr, int led, unsigned char *values);
void pca9685_rgba_led(unsigned char addr, int rgba_led, unsigned char *color, unsigned char level);
void pca9685_brightness(int percent, unsigned char *values);
void PCA9685_SetOutput(uint8_t Address, uint8_t Output, uint16_t OnValue, uint16_t OffValue);
#endif