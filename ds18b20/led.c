#include "led.h"

void led(uchar p,bit state)
{
 static uchar led_temp=0x00;
	static uchar last_temp=0xff;
	if(1==state)
	{
	 led_temp |=0x01<<p;
	}
	else
	{
	 led_temp &=~(0x01<<p);
	}
	if(led_temp!=last_temp)
	{
	 P0=~led_temp;Y4;Y0;
		last_temp=led_temp;
	}
}

void wmq(uchar d,bit state)
{
 static uchar wmq_temp=0x00;
	static uchar last_temp=0xff;
	if(1==state)
	{
	 wmq_temp |=0x01<<d;
	}
	else
	{
	 wmq_temp &=~(0x01<<d);
	}
	if(wmq_temp!=last_temp)
	{
	 P0=~wmq_temp;Y5;Y0;
		last_temp=wmq_temp;
	}
}