#include "sonic.h"

sbit tx = P1^0;
sbit rx = P1^1;

void sonic_send()
{
    uchar i;
    for (i = 0;i < 8;i++)
    {
        tx = 1;
        delay14us();
        tx = 0;
        delay14us();
    }
}


uint sonic_measure()
{
    uint distance;

    sonic_send();

    TH0 = 0x00; TL0 = 0x00;
    TR0 = 0;
    TF0 = 1;

    while (rx == 0);
    TR0 = 1;

    while (rx == 1 && TF0 == 0);
    TR0 = 0;

    if (TF0)
    {
        distance = 999;
        TF0 = 0;
    }
    else
    {
        distance = (uint) ( (TH0 << 8) | TL0 ) * 0.017;
    }

    return distance;
}