#include "led.h"

void led(uchar i, bit state)
{
    static uchar led_tmp = 0x00;
    static uchar led_last = 0xFF;

    if(state == 1)
    {
        led_tmp = led_tmp | (0x01 << i);
    }
    else
    {
        led_tmp = led_tmp & ~(0x01 << i);
    }

    if(led_tmp != led_last) // 修正了这里的条件
    {
        P0 = ~led_tmp;
        batch(4);
        batch(0);

        led_last = led_tmp;
    }
}

// 定义 led_array 变量
uchar led_array[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void led_display()
{
    static uchar i;
    led(i,led_array[i]);
    i = (i + 1) % 8;
}

void led_water()
{
    static uchar i;
    static bit towards;

    if(towards == 1)
    {
        led_array[i] = 1;
        i++;
        if(i == 8)
        {
            i = 7;
            towards = 0;
        }
    }
    else
    {
        led_array[i] = 0;
        if(i == 0) 
        {
            towards = 1;
        }
        else
        {
            i--;
        }
    }
}