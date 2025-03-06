

#include "led.h"
uchar led_value[] = {0,0,0,0,0,0,0,0};

void led(uchar i,bit state)
{
    static uchar led_tmp = 0x00;
    static uchar led_last;

    if(1 == state)
    {
        led_tmp = led_tmp | (0x01 << i);
    } 
    else
    {
        led_tmp = led_tmp & ~(0x01 << i);
    }

    if (led_tmp != led_last)
    {
        P0 = ~led_tmp;
        batch(4);
        batch(0);

        led_last = led_tmp;
    }

}

void led_water()
{
    static uchar i;
    static uchar towards;

    if (1 == towards)
    {
        led_value[i] = 1;
        i = i + 1;

        if(i == 8)
        {
            i = 7;
            towards = 0;
        }
    }

    else
    {
        led_value[i] = 0;
        i = i - 1;
        if (i == -1)
        {
            i = 0;
            towards = 1;
        }
    }
}

void led_on()
{
    static uchar i;
    led(i,led_value[i]);
    batch(4);
    batch(0);
    i = i + 1;
    i = i % 8;
}