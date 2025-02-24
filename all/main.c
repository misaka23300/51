#include "main.h"

#define KEY_TIME 5
#define LED_TIME 3

extern uchar seg[8];
extern uchar led[8];

uchar press, percent;
uchar state;

bit key_flag, ne555_flag;

uint times, times1, freq;



// state
// 0 -> ne55
// 1 -> pwm
void main()
{
    boot_init();

    while (1)
    {
        if (led_flag && state != 2)
        {
            led_display();
            led_flag = 0;
        }


        if (led_flag && state == 2)
        {
            if (one_tag != 2)
            {
                one_tag = 2;
                pwm_timer_0();
            }


            bit j;
            uchar i;

            j = pwm_flag;

            for(i = 0; i < 8; i++);
            {
                led[i] = j;
            }

            led_display();
        }

        if (key_flag)
        {
            press = key_scan();

            if (press == 4)
            {
                state = (state + 1) % 3;
            }

            if (state == 1)
            {
                if (press == 9)
                {
                    percent++;
                    if (percent == 99)
                    {
                        percent = 0;
                    }
                }

                if (press == 8)
                {
                    percent--;
                    if (percent == 0)
                    {
                        percent = 99;
                    }
                }
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
                ne555_timer_0();
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

        if (state == 2)
        {
            
        }

        if (state != 1)
        {
            ET0 = 0;
        }

        if (state == 3)
        {
            if (one_tag != 3)
            {
                one_tag = 3;
                seg[0] = 5;
                seg[1] = 0;
                seg[2] = 16;
                seg[3] = 16;
                seg[4] = 16;
            }

        
            seg[5] = idstance / 100  % 10;
            seg[6] = distance / 10 % 10;
            seg[7] = distance / 10;
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
    static uchar i;

    switch (state)
    {
        case 0:
        {
            times++;
            if (times > 30000)
            {
                times = 0;
                times1++;
            }
        }
        break;

        case 1:
        {
            i = (i + 1) % 100
            if (i > percent)
            {
                pwm_flag = 1;
            }
            else
            {
                pwm_flag = 0;
            }
        }
        break;
    }
}