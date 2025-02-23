#include __SEG_H__

uchar letter[]={                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};

uchar segs[] = {0,0,0,0,0,0,0,0};

void seg_value(uchar c0,c1,c2,c3,c4,c5,c6,c7)
{
    segs[0] = c0;
    segs[1] = c1;
    segs[2] = c2;
    segs[3] = c3;
    segs[4] = c4;
    segs[5] = c5;
    segs[6] = c6;
    segs[7] = c7;
    }

void seg_display()
{
    static uchar i;
    P0 = 0x00;
    batch(6);
    batch(0);

    P0 = letter[segs[i]];
    batch(7);
    batch(0);

    P0 = 0x01 << i;
    batch(6);
    batch(0);

    i++;

    i %= 8;

}
uchar clock[] = {20,25,00};
void seg_clock()
{
    clock[2]++;
    if(clock[2] == 60)
    {
        clock[2] = 0;
        clock[1]++;
        if(clock[1] == 60)
        {
            clock[1] = 0;
            clock[0]++;

            if(clock[0] = 24)
            {
                clock[0] = 0;
            }
        }
    }

    seg_value(0, 0, clock[0] / 10, clock[0] % 10, clock[1] / 10, clock[1] % 10, clock[2] / 10, clock[2] % 10);
}

