#include "main.h"

bit led_display_mark, seg_display_mark;
bit led_water_mark, seg_clock_mark;

void timer() interrupt 1
{
    static uint i;
    i++;
    if(i % 1 == 0)
    {
        
        seg_display_mark = 1;
    }

    if (i % 3 == 0)
    {
        led_display_mark = 1;
    }

    
    if (i % 1000 == 0)
    {
        seg_clock_mark = 1;
    }
    i %= 3000;
}

void main()
{
    boot_init();
    while(1)
    {
        if (led_display_mark)
        {
            led_display();
            led_display_mark = 0;
        }

        if (seg_display_mark)
        {
            seg_display();
            seg_display_mark = 0;
        }

        if (led_water_mark)
        {
            led_water();
            led_water_mark = 0;
        }

        if (seg_clock_mark)
        {
            uchar j = seg_clock();
            seg_clock_mark  = 0;
            if (j)
            {
                led_water_mark = 1;
            }
        }
    }
}