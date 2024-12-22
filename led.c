#include "led.h"
uchar led_flash[8] = {0,0,0,0,0,0,0,0};

void led(uchar p,bit state)
{   
    // p为第几个灯，state为灯的状态。
    static uchar led_tmp = 0x00;
    static uchar led_last;

    // 生成寄存器2进制数据
    if(state == 1)
    {
        led_tmp = led_tmp | (0x01 << p);    // 0x01 -> 0000 0001
    }
    else
    {
        led_tmp = led_tmp & ~(0x01 << p);   // ~0x01 -> 1111 1110 -> 0xFE
    }

    if(led_tmp != led_last)
    {
        P0 = ~led_tmp;
        LATCH_ON;
        LATCH_OFF;
        led_last = led_tmp;
    }
}
                 

void water_led_left()
{
    // 流水灯,从左往右亮。
    
    uchar i;
    for(i = 0;i <= 7;i++)
    {
        led_flash[i] = 1;
        led(i,led_flash[i]);
        //Delay50ms();
        sleep(100);
        led_flash[i] = 0;
        led(i,led_flash[i]);
    }
    
}

void water_led_right()
{
    // 流水灯，从右往左亮。
    char j;
    for(j = 7; j >= 0; j--)  // 循环条件修改为 j >= 0
    {
        led_flash[j] = 1;
        led(j, led_flash[j]);
        Delay50ms();
        led_flash[j] = 0;
        led(j, led_flash[j]);
    }
}


void sharing_led(int k)
{
    while(k > 0)
    {
        k--;
        P0 = ~0xFF;
        LATCH_ON;
        LATCH_OFF;
        Delay50ms();

        P0 = ~0x00;
        LATCH_ON;
        LATCH_OFF;
        Delay50ms();
        
    }
    
}