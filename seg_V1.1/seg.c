#include "seg.h"

const uchar letter[] = {                       
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};

// 定义 seg_array 变量
uchar seg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uchar point[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void seg_display()
{
    static uchar i;

    P0 = ~0x00;
    batch(7);
    batch(0);

    

    P0 = 0x01 << i;
    batch(6);
    batch(0);

    P0 = ~letter[seg_array[i]];
    if (point[i])
    {
        P0 = P0 & 0x7F;
    }
    batch(7);
    batch(0);


    i = (i + 1) % 8;
}

// 定义 clock_array 变量
uchar clock_array[3] = {23, 59, 1};    // hour, minute, second

uchar seg_clock()
{
    clock_array[2]++;

    
    if (clock_array[2] == 60)
    {
        clock_array[2] = 0;
        clock_array[1]++;

        if (clock_array[1] == 60)
        {
            clock_array[1] = 0;
            clock_array[0]++;
            if (clock_array[0] == 24)
            {
                clock_array[0] = 0;
            }
        }
    }

    seg_array[7] = clock_array[2] % 10;
    seg_array[6] = clock_array[2] / 10;

    seg_array[5] = 17;
    seg_array[4] = clock_array[1] % 10;

    seg_array[3] = clock_array[1] / 10;
    seg_array[2] = 17;

    seg_array[1] = clock_array[0] % 10;
    seg_array[0] = clock_array[0] / 10;

    if (clock_array[2] % 5 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}