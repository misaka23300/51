#include "boot.h"

void boot_init()
{
    
    timer();
    EA = 1;
}



void batch(uchar i)
{
    switch(i)
    {
        case 0: { P2 = P2 & 0x1F; break; }
 
        case 4: { P2 = (P2 & 0x1F) | 0x80; break; }
        case 5: { P2 = (P2 & 0x1F) | 0xA0; break; }
        case 6: { P2 = (P2 & 0x1F) | 0xC0; break; }
        case 7: { P2 = (P2 & 0x1F) | 0xE0; break; }
    }
    
}


void timer()
{
    // 1011 1111
    AUXR &= 0xBF;
    // 0000 0110
    TMOD = 0x06;

    timer_0();
    timer_1();

    EA = 1;
}

void timer_0()
{
    TL0 = 0xFF;
    TH0 = 0xFF;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
}


void timer_1()
{
    TL1 = 0x18;
    TH1 = 0xFC;
    TF1 = 0;
    TR1 = 1;
    ET1 = 1;
}


