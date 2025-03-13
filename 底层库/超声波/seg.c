#include "seg.h"

uchar seg[8] = {0, 0, 0, 0, 0, 0 ,0 ,0};
uchar code letter[] = {};


void seg_display()
{
    static uchar i;
    P0 = 0xFF;
    batch(7);
    batch(0);

    P0 = 0x01 << i;
    batch(6);
    batch(0);

    P0 = letter[seg[i]];
    batch(7);
    batch(0);

    i = (i + 1) % 8;
}

void set_Seg(uchar s0, s1, s2, s3, s4, s5, s6, s7)
{
    uchar segs[8] = {s0, s1, s2, s3, s4, s5, s6, s7};
    uchar i;
    for (i = 0;i < 8;i++)
    {
        seg[i] = segs[i];
    }
}

