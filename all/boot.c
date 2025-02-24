#include "boot.h"

void boot_init()
{
    P0M0 = 0x00; P0M1 = 0x00; 
    P1M0 = 0x00; P1M1 = 0x00; 
    P2M0 = 0x00; P2M1 = 0x00; 
    P3M0 = 0x00; P3M1 = 0x00; 
    P4M0 = 0x00; P4M1 = 0x00; 
    P5M0 = 0x00; P5M1 = 0x00; 
    P6M0 = 0x00; P6M1 = 0x00; 
    P7M0 = 0x00; P7M1 = 0x00; 


    P0 = 0xFF;
    batch(4);

    batch(6);
    batch(7);

    batch(0);

    // 1010 1111
    P0 = 0xAF;
    batch(5);
    batch(0);

    timer();


}

void timer()
{
    // T0 -> NE555
    // T0 -> sonic
    // T0 -> 

    // T1 -> 1ms
    void Timer1_Init();
    EA = 1;
}



void Timer1_Init()		//1毫秒@12.000MHz
{
	AUXR &= 0xBF;			//定时器时钟12T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0x18;				//设置定时初始值
	TH1 = 0xFC;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 1;				//使能定时器1中断
}


void batch(uchar i)
{
    switch (i)
    {
        case 0: {P2 = P2 & 0x1F; break; }
        case 4: {P2 = (P2 & 0x1F) | 0x80; break; }
        case 5: {P2 = (P2 & 0x1F) | 0xA0; break; }
        case 6: {P2 = (P2 & 0x1F) | 0xC0; break; }
        case 7: {P2 = (P2 & 0x1F) | 0xE0; break; }
    }



void timer_0()
{
    // 计数器
    // 12T
    // 8位自动装载

    // 1xxx xxxx
    AUXR |= 0x8F;

    // xxxx 0110
    TMOD = (TMOD & 0xF0) | 0x06 ;
    TL0 = 0xFF;
    TH0 = 0xFF;

    TR0 = 0;
    TF0 = 0;

    ET0 = 1;
}