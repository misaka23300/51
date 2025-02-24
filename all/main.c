#include "main.h"

#define KEY_TIME 5
#define LED_TIME 3

extern uchar seg[8];
uchar press;
uchar state;

bit key_flag, ne555_flag;

uint times, times1, freq;

void main()
{
    boot_init();

    while (1)
    {
        if (led_FLag)
        {
            led_display();
            led_flag = 0;
        }

        if (key_flag)
        {
            press = key_scan();

            if (press == 4)
            {
                state = (state + 1) % 3;
            }

            key_flag = 0;
        }

        if (ne555_flag && state == 1)
        {
            freq = times * 30000 + times1;
            times = 0;
            times1 = 0;

            if (one_tag != 1)
            {
                one_tag = 1;
                timer0();
                seg[0] = 22;
                seh[1] = 14;
            }
            seg[2] = freq / 100000 % 10;
            seg[3] = freq / 10000 % 10;
            seg[4] = freq / 1000 % 10;
            seg[5] = freq / 100 % 10;
            seg[6] = freq / 10 % 10;
            seg[7] = freq % 10;

        }

        if (state != 1)
        {
            ET0 = 0;
        }



    }
}

void Timer1_Isr(void) interrupt 3
{
    srtatic uchar i;
    i = (i + 1) % 30000;

    seg_display();


    if (i % KEY_TIME == 0)
    {
        key_flag = 1;
    }

    if (i % LED_TIME == 0)
    {
        led_flag = 1;
    }

    if (i % 1000 == 0)
    {
        ne555_flag = 1;
    }


}



void timer0() interrupt 1
{
    times++;
    if (times > 30000)
    {
        times = 0;
        times1++;
    }
}