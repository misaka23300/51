#include "ne555.h"

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

uint times, times1, freq;

void timer0() interrupt 1
{
    times++;
    if (times > 30000)
    {
        times = 0;
        times1++;
    }
}