
#include "pca9685.h"
#include "pca9685_reg.h"    /* Light Driver Chip */
#include "bsp_i2c_gpio.h"
#define MAX_OUTPUT_INDEX	15
#define MAX_OUTPUT_VALUE	0xFFF
/******************************************/
/*                                        */
/*   Probe the I2C bus, and show the      */
/*   user what we have found              */
/*                                        */
/*                                        */
/*                                        */
/******************************************/

/******************************************/
/*                                        */
/* Philips PCA9685 I2C Driver, 16 channel */
/* Lighting controler chip                */
/*                                        */
/*                                        */
/******************************************/

/******************************************/
/*                                        */
/* Init code for the PCA9685              */
/*                                        */
/******************************************/

void init_pca9685(unsigned char address)
{
    unsigned char buf[30];
    
    printf("Setting up channel %d\n\r",address);
    
    buf[0] = PCA9685_MODE1;
    buf[1] = PCA9685_AI;
   // buf[2] = PCA9685_OUTDRV;
    buf[2] = PCA9685_INVRT;
    i2c_WriteBuffer(address,(char *) buf, 3);
}

/******************************************/
/*                                        */
/* Send data to a given channel of a      */
/* given PCA9685 chip                     */
/*                                        */
/******************************************/

void pca9685_led(unsigned char addr, int led, unsigned char *values) 
{
    unsigned char buf[5];
   
    if (led == PCA9685_ALL_LEDS) {
        buf[0] = PCA9685_ALL_LED_ON_L;
    } else {
        buf[0] = PCA9685_BASE(led);
    }

    buf[1] = values[0];
    buf[2] = values[1];
    buf[3] = values[2];
    buf[4] = values[3];
    i2c_WriteBuffer(addr, (char *)buf, 5);
}

/******************************************/
/*                                        */
/* Send all the data to a single rgba led */
/* at once to the PCA9685 chip            */
/*                                        */
/*                                        */
/*                                        */
/* color[0] = red (0-255)                 */
/* color[1] = green (0-255)               */
/* color[2] = blue (0-255)                */
/* color[3] = amber (0-100%)              */
/* total brightness = level (0-100%)      */
/******************************************/
void pca9685_rgba_led(unsigned char addr, int rgba_led, unsigned char *color, unsigned char level)
{
    int led;
    unsigned int on, off;
    unsigned char buf[17];
    
    if (level > 100){
        //printf("Level percentage range 0 - 100 (Trying for %d)\n\r",level);
        return;
        }
    if (color[3] > 100) {
        //printf("Amber percentage range 0 - 100 (Trying for %d)\n\r",color[3]);
        return;
        }
    on=0;
    if (rgba_led == PCA9685_ALL_LEDS) {
        buf[0] = PCA9685_ALL_LED_ON_L;
        if (color[0]==0 || level==0){
            buf[1]=0;
            buf[1+PCA9685_LED_ON_H] = 0;//buf[2]
            buf[3]=0;
            buf[1+PCA9685_LED_OFF_H] = PCA9685_LED_OFF;//buf[4]
            //printf("all on, zero brightness\r\n");
        }
        else if (color[0]==0xff && level==100){
            buf[1]=0;
            buf[1+PCA9685_LED_ON_H] = PCA9685_LED_ON;//buf[2]
            buf[3]=0;
            buf[1+PCA9685_LED_OFF_H] = 0;//buf[4]
            //printf("all on, full brightness\r\n");
        }
        else{
            off = (4096 * color[0]*level) / 0xff / 100;
            buf[1+PCA9685_LED_ON_L] = on & 0xff;//buf[1]
            buf[1+PCA9685_LED_ON_H] = (on >> 8) & 0xf;//buf[2]
            buf[1+PCA9685_LED_OFF_L] = off & 0xff;//buf[3]
            buf[1+PCA9685_LED_OFF_H] = (off >> 8) & 0xf;//buf[4]
        }
        i2c_WriteBuffer(addr, (char *)buf, 5);
        //printf("All leds on\r\n");
        return;
    } else {
        buf[0] = PCA9685_BASE(rgba_led);
    }    
    for (led=0;led<=3;led++){
        if (color[led]==0 || level==0){
        buf[led*4+1+PCA9685_LED_ON_H] = 0; 
        buf[led*4+1+PCA9685_LED_OFF_H] = PCA9685_LED_OFF;
        continue;
        }
        if (((color[led]==100 && led==3)|| color[led]==0xff)&& level==100) {
        buf[led*4+1+PCA9685_LED_ON_H] = PCA9685_LED_ON;
        buf[led*4+1+PCA9685_LED_OFF_H] = 0;
        continue;
        }
        off = (4096 * color[led]*level) / 0xff / 100;
        buf[led*4+1+PCA9685_LED_ON_L] = on & 0xff;
        buf[led*4+1+PCA9685_LED_ON_H] = (on >> 8) & 0xf;
        buf[led*4+1+PCA9685_LED_OFF_L] = off & 0xff;
        buf[led*4+1+PCA9685_LED_OFF_H] = (off >> 8) & 0xf;
    }
    i2c_WriteBuffer(addr, (char *)buf, 17);
}
/******************************************/
/*                                        */
/* Calculate the register values for a    */
/* given brightness percentage            */
/*                                        */
/******************************************/

void pca9685_brightness(int percent, unsigned char *values) 
{
    unsigned int on, off;

    if (percent == 0) {
    values[PCA9685_LED_ON_H] = 0; 
    values[PCA9685_LED_OFF_H] = PCA9685_LED_OFF;
    return;
    }
    if (percent == 100) {
    values[PCA9685_LED_ON_H] = PCA9685_LED_ON;
    values[PCA9685_LED_OFF_H] = 0;
    return;
    }
    on = 0;
    off = (4096 * percent) / 100;
    values[PCA9685_LED_ON_L] = on & 0xff;//0
    values[PCA9685_LED_ON_H] = (on >> 8) & 0xf;//1
    values[PCA9685_LED_OFF_L] = off & 0xff;//2
    values[PCA9685_LED_OFF_H] = (off >> 8) & 0xf;//3
}

/******************************************/
/*                                        */
/* Set a given channel to a given level   */
/*                                        */
/******************************************/
void channel_light(unsigned char ch, unsigned char lev)
{
    char            chip,led;     /* Chip Number, channel number */
    unsigned char   v[4];         /* register data for givern level */
    
    led = ch%16;
    v[0]=0;
    v[1]=0;
    v[2]=0;
    v[3]=0;
    
    if(lev > 100){
        printf("Level percentage range 0 - 100 (Trying for %d)\n\r",lev);
        return;
    }
    
    switch(ch/16){
        case    0    :
            chip=LEDDRV1;
            break;
        case    1    :
            chip=LEDDRV2;
            break;
        case    2    :
            chip=LEDDRV3;
            break;
        case    3    :
            chip=LEDDRV4;
            break;
        case    4    :
            chip=LEDDRV5;
            break;
        case    5    :
            chip=LEDDRV6;
            break;
        default      :
            printf("Error unknown chip %d\n\r",ch/16);
            return;
    }
    
    printf("Setting channel %d to brightness level %d chip = %d(%d),%d\n\r",
        ch,lev,chip,ch/16,led);
    pca9685_brightness(lev,v);    /* Calculate the brightness level */
    printf("Brightness level is %02x,%02x,%02x,%02x\n\r",v[0],v[1],v[2],v[3]);
    pca9685_led(chip,led,v);      /* Send to chip */
}

void PCA9685_SetOutput(uint8_t Address, uint8_t Output, uint16_t OnValue, uint16_t OffValue)
{
	 
	// Optional: PCA9685_I2C_SlaveAtAddress(Address), might make things slower
	if (Output <= MAX_OUTPUT_INDEX && OnValue <= MAX_OUTPUT_VALUE && OffValue <= MAX_OUTPUT_VALUE)
	{
	   uint8_t temp[4];
		 temp[0]=OnValue & 0xFF;
		 temp[1]=(OnValue >> 8) & 0xF;
		 temp[2]=OffValue & 0xFF;
		 temp[3]=(OffValue >> 8) & 0xF;
		 i2c_ReadBuffer(Address,LEDn_ON_L(Output),4,temp);
	}
}