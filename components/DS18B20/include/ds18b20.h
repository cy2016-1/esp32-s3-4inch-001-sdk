#ifndef __DS18B20_H__
#define __DS18B20_H__

#define uchar unsigned char
#define uint8 unsigned char
#define uint16 unsigned short
extern unsigned char Ds18b20Initial(void);
extern unsigned char ReadDs18B20(void);
extern float floatReadDs18B20(void);
#endif
