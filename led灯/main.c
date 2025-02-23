#include <main.h>

static bit led_on_flag, led_water_flag;
static bit seg_clock_flag, seg_display_flag, seg_value_flag;

void main()
{

    init();
    while (1)
    {
        if (led_on_flag == 1)
        {
            led_on();
            led_on_flag = 0;
        }

        if (led_water_flag == 1)
        {
            led_water();
            led_water_flag = 0;
        }
        if (seg_clock_flag == 1)
        {
            seg_clock();
            seg_clock_flag = 0;
        }
        
        if (seg_display_flag == 1)
        {
            seg_display();
            seg_display_flag = 0;
        }

    }
}


void timer() interrupt 1
{
    static uint i;
    i = i + 1;
    if (i % 1 == 0)
    {
        led_on_flag = 1;
        seg_display_flag = 1;
    }
    if (i % 100 == 0)
    {
        led_water_flag = 1;
    }
    if(i % 1000 == 0)
    {
        seg_clock_flag = 1;
    }


    i = i % 3000;
}


