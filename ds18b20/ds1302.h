#ifndef __DS1302_H
#define __DS1302_H
#include "sys.h"
void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );
char Get_Ds1302(uchar addr);
void Init_Ds1302(uchar hour,min,sec);
#endif