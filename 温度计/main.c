#include "main.h"

#define LED_TIME 10
#define KEY_TIME 5
#define READ_TIME 750
extern uchar seg[8];
extern uchar led[8];
extern uchar now_time[7];

uchar one_tag = 99;
uchar press, state;
bit led_flag, key_flag, read_time_flag;
void main()
{
    boot_init();
    init_time();
    

    while (1)
    {
        if (led_flag)
        {
            led_display();
            led_flag = 0;
        }

        if (key_flag)
        {
            press = key_scan();
            key_flag = 0;
        }

        if (read_time_flag)
        {
            read_time();
            read_time_flag = 0;
        }

        switch (state)
        {
            // 时间
            
            case 0:
            {
                if (one_tag != 0)
                {
                    one_tag = 0;
                    seg[2] = 17;
                    seg[5] = 17;
                }
                seg[0] = now_time[2] / 10;
                seg[1] = now_time[2] % 10;

                seg[3] = now_time[1] / 10;
                seg[4] = now_time[1] % 10;

                seg[6] = now_time[0] / 10;
                seg[7] = now_time[0] % 10;
            }
            break;
        }
    }
}

void Timer2_Isr(void) interrupt 12
{
    static uchar i;
    i = (i + 1) % 8;
    
    seg_display();

    if (i % LED_TIME == 0)
    {
        led_flag = 1;
    }

    if (i % KEY_TIME == 0)
    {
        key_flag = 1;
    }

    if (i % READ_TIME == 0)
    {
        read_time_flag = 1;
    }
}

