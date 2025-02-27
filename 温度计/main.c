#include "main.h"

#define LED_TIME 10
#define KEY_TIME 5
#define READ_TIME 750
extern uchar seg[8];
extern uchar led[8];
extern uchar now_time[7];

char set_time[7] = {0, 0, 0, 0, 0, 0, 0};

uchar one_tag = 99;
uchar press, state;
bit led_flag, key_flag, read_time_flag, set_time_flag;

char set_time_config;

void main()
{
		uchar i;
	
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

            if (press == 4)
            {
                state = 1;
            }

            if (press == 7)
            {
                state = (state + 1) % 3;
            }

            if (state == 1)
            {
                switch (press)
                {
                    case 9:
                    {
                        set_time_config = (set_time_config + 1) % 3;
                    }
                    break;

                    case 17:
                    {
                        set_time_config--;
                        if (set_time_config == -1)
                        {
                            set_time_config = 2;
                        }
                    }
                    break;

                    case 14:
                    {
                        if (set_time_config == 2)
                        {
                            set_time[set_time_config] = (set_time[set_time_config] + 1) % 24;
                        }
                        else
                        {
                            set_time[set_time_config] = (set_time[set_time_config] + 1) % 60;
                        }
                        
                    }
                    break;

                    case 12:
                    {
                        set_time[set_time_config] = (set_time[set_time_config] - 1);

                        if (set_time[set_time_config] == -1)
                        {
                            if (set_time_config == 2)
                                set_time[set_time_config] = 23;
                            else
                            {
                                set_time[set_time_config] = 59;
                            }
                        }
                    }
                    break; 

                    case 13:
                    {
                        write_time(set_time);
                        read_time();
                        state = 0;
                    }
                    break;

                    case 33:
                    {
                        state = 0;
                    }
                }
            }

           
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

            case 1:
            {
                if (one_tag != 1)
                {
                    one_tag = 1;
                    seg[2] = 17;
                    seg[5] = 17;

                    
                    for (i = 0;i <7;i++)
                    {
                        set_time[i] = now_time[i];
                    }
                }

                if (set_time_flag)
                {
                    switch (set_time_config)
                    {
                      /*  
                        for (j = 0;j < 7;j++)
                        {
                            seg[j] = 
                        }
					*/
                        case 0:
                        {
                            // 秒
                            seg[6] = 16;
                            seg[7] = 16;
                        }
                        break;

                        case 1:
                        {
                            // 分
                            seg[4] = 16;
                            seg[3] = 16;
                        }
                        break;

                        case 2:
                        {
                            // 时
                            seg[1] = 16;
                            seg[0] = 16;
                        }
                    }
                }
                else
                {
                    // 时
                    seg[0] = set_time[2] / 10;
                    seg[1] = set_time[2] % 10;
                    // 分
                    seg[3] = set_time[1] / 10;
                    seg[4] = set_time[1] % 10;
                    // 秒
                    seg[6] = set_time[0] / 10;
                    seg[7] = set_time[0] % 10;
                }
            }
            break;
        }
    }
}

void Timer2_Isr(void) interrupt 12
{
    static uchar i;
    i = (i + 1) % 30000;
    
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

    if (i % 5000 == 0)
    {
        if (set_time_flag)
        {
            set_time_flag = 0;
        }
        else
        {
            set_time_flag = 1;
        }
    }

}



