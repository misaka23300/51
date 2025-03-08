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
    batch(0);

    P0 = 0xFF;
    batch(7);
    batch(0);

    batch(6);
    batch(0);
    
    P0 = 0xAF;
    batch(5);
    batch(0);
}

void batch(uchar i)
{
    switch (i)
    {
        case 4: P2 = (P2 & 0x0F) | 0x80; break;
        case 5: P2 = (P2 & 0x0F) | 0xA0; break;
        case 6: P2 = (P2 & 0x0F) | 0xC0; break;
        case 7: P2 = (P2 & 0x0F) | 0xE0; break;
    }
}