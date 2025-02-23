#include "main.h"



uchar percent = 60;
bit pwm_value;
void main()
{
    boot_init();

    while (1)
    {



    }
}


void Timer2_Isr(void) interrupt 12
{
    static uchar i;
    i = (i + 1) % 100;

    if (i < percent)
    {
        pwm_value = 1;
    }
    else
    {
        pwm_value = 0;
    }
}
c