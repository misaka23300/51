#include "key.h"

uchar scankey()
{
	static uchar key_state,key_value,cnt;
	uchar key_press=0xff,tmp=99;
	
	P3=0x0f; 
	P42=0; P44=0;
	P36=P42; P37=P44;
	
	
	key_press=P3&0x0f; //0000 1110
	
	switch(key_state)
	{
		case 0: 
			if(key_press != 0x0f) key_state=1;
		break;
		
		case 1:
			if(key_press == 0x0f) key_state=0;
			else
			{
				P3 = key_press|0xf0;                       //P6=1111 1110 P6|
				P42 = 1; P44 = 1;
				P36 = P42; P37 = P44;
				
				key_press = P3;										//1111 1110
				key_state = 2;
				
				switch(key_press)
				{ //¾ØÕó
					case 0x77: key_value=4; break;
					case 0x7b: key_value=5; break;
					case 0x7d: key_value=6; break;
					case 0x7e: key_value=7; break;
					case 0xb7: key_value=8; break;
					case 0xbb: key_value=9; break;
					case 0xbd: key_value=10; break;
					case 0xbe: key_value=11; break;
					case 0xd7: key_value=12; break;
					case 0xdb: key_value=13; break;
					case 0xdd: key_value=14; break;
					case 0xde: key_value=15; break;
					case 0xe7: key_value=16; break;
					case 0xeb: key_value=17; break;
					case 0xed: key_value=18; break;
					case 0xee: key_value=19; break;
					
//					case 0xfe: key_value=7; break; ¶ÀÁ¢°´¼ü
//					case 0xfd: key_value=6; break;
//					case 0xfb: key_value=5; break;
//					case 0xf7: key_value=4; break;
				 default: key_state=0;
				}
			}
		break;
			
		case 2:
			if(key_press != 0x0f)
			{
				cnt++;
				if(cnt>=200)
				{
					key_state=3;
					cnt=0;
				}
				cnt%=255;
			}
			else //¶Ì°´¼ü
			{
				cnt=0;
				key_state=0;
				tmp = key_value; // 4 ~ 19
				key_value = 0;
			}
		break;
			
		case 3:
			if(key_press == 0x0f)
			{
				key_state = 0;
				tmp = key_value + 20; // 24 ~ 39
				key_value = 0;
			}
		break;	
	}
	return tmp;
}
	