#include "key.h"

uchar scankey()
{
 static uchar key_state=0,cnt=0,key_value=0;
	uchar key_press=0,a=20;
	P36=P42=0;P37=P44=0;
	P3=0x0f;
	key_press=P3&0x0f;
	
	switch(key_state)
	{
		case 0:
		{
		 if(key_press!=0x0f)
		 {
		  key_state=1;
		 }
		 break;
		}
		case 1:
		{
		 if(key_press==0x0f)
		 {
		  key_state=0;
		 }
		else
		{
		 P3=key_press|0xf0;
			P36=P42=1;P37=P44=1;
			key_press=P3;
			key_state=2;
			
			switch(key_press)
			{
				case 0xfe:key_value=7;break;
				case 0xfd:key_value=6;break;
				case 0xfb:key_value=5;break;
				case 0xf7:key_value=4;break;
				default:key_state=0;
			}
		}
		break;
	}
				case 2:
				{
				 if(key_press!=0x0f)
				 {
				  if(cnt++>=100)
					{
					 key_state=3;
						cnt=0;
					}
					cnt%=200;
				 }
				 else
				 {
				  a=key_value;
					 cnt=0;
					 key_state=0;
					 key_value=0;
				 }
				 break;
				}
				case 3:
				{
				 if(key_press==0x0f)
				 {
				   a=key_value+20;
					 key_state=0;
					 key_value=0;
				 }
				 break;
				}
	}		
	return a;
}