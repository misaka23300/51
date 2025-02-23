
#include "main.h"



extern uchar seg[8];


uint count, freq;





void Timer0_Isr(void) interrupt 1
{
    count++;

}

void timer_3() interrupt 3
{
    static uint i;
    i = (i + 1) % 8000;
    
    if (i % 1000 == 0)
    {
        freq = count;
        count = 0;

     
        seg[0] = 16;
        seg[1] = 16;
        seg[2] = 16;
        seg[3] = freq / 10000 % 10;
        seg[4] = freq / 1000 % 10;
        seg[5] = freq / 100 % 10;
        seg[6] = freq / 10 % 10;
        seg[7] = freq % 10;

        freq = 0;
    }

    if (i % 1 == 0)
    {
		seg_display();
	}
}



void main()
{
    boot_init();

    while (1)
    {
        
    }
}