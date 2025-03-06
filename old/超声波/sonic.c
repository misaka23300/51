#incloude "sonic.h"

sbit tx = P0 ^ 1;
sbit rx = P0 ^ 1;


void sonic_send()
{
    uchar i;
    for (i = 0;i < 8;i++)
    {
        tx = 1;
        delay();
        rx = 0;
        delay();
    }
}

void sonic_measure()
{
    sonic_send();

    while (rx == 0);
    TH1 = 0; TL1 = 0;
    TF1 = 0;
    TR1 = 1;

    while (rx == 1 && TF1 = 0);

    TR1 = 0;

    if (TF1)
    {
        distance = 999;
        TF1 = 0;
    }
    else
    {
        t = (TH1 << 8) | TL1;
        distance = (uint) (t * 0x017);
    }

    return distance;
}