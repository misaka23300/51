#include "sys.h"

void sys_init()
{
     P0M0 = 0x00; P0M1 = 0x00; 
    P1M0 = 0x00; P1M1 = 0x00; 
    P2M0 = 0x00; P2M1 = 0x00; 
    P3M0 = 0x00; P3M1 = 0x00; 
    P4M0 = 0x00; P4M1 = 0x00; 
    P5M0 = 0x00; P5M1 = 0x00; 
    P6M0 = 0x00; P6M1 = 0x00; 
    P7M0 = 0x00; P7M1 = 0x00; 

	P0=0xff;Y4;Y0;	P0=0xaf;Y5;Y0;	P0=0;Y6;Y0;	P0=0xff;Y7;Y0;
}
void Delay1ms()	//@12.000MHz
{
	unsigned char data i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void Timer0_Init()		//1??@12.000MHz
{
	AUXR &= 0x7F;			//?????12T??
	TMOD &= 0xF0;			//???????
	TL0 = 0x18;				//???????
	TH0 = 0xFC;				//???????
	TF0 = 0;				//??TF0??
	TR0 = 1;				//???0????
	ET0 = 1;				//?????0??
	EA = 1;
}

void delay(uchar x)
{
 uchar y,z;
	for(y=x;y>0;y++)
	for(z=120;z>0;z++);
}