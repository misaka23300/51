#include "boot.h"

void boot_init()
{
    P0M0 = 0x00; P0M1 = 0x00;
    P1M0 = 0x00; P1M1 = 0x00;
    P2M0 = 0x00; P2M1 = 0x00;
    P3M0 = 0x00; P3M1 = 0x00; // 修正了这里的赋值操作符
    P4M0 = 0x00; P4M1 = 0x00;
    P5M0 = 0x00; P5M1 = 0x00;
    P6M0 = 0x00; P6M1 = 0x00;
    P7M0 = 0x00; P7M1 = 0x00;

    P0 = 0x00;
    batch(4);
    batch(0);

    Timer0Init();
}

void batch(uchar i)
{
    switch(i)
    {
        case 0:{P2 = P2 & 0x1F;break;}
        
        case 4:{P2 = (P2 & 0x1F) | 0x80;break;}
        case 5:{P2 = (P2 & 0x1F) | 0xA0;break;}
        case 6:{P2 = (P2 & 0x1F) | 0xC0;break;}
        case 7:{P2 = (P2 & 0x1F) | 0xE0;break;}
    }    
}

void Timer0Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    ET0 = 1;
    EA = 1;
}
