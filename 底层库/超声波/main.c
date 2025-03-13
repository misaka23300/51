#include "main.h"
#define SONIC_TIME 1000

bit sonic_flag;
uchar distance;


void main()
{
    boot_init();
    while (1)
    {
        if (sonic_flag)
        {
            sonic_flag = 0;
            sonic_proc();
        }
    }
}


void Timer2_Isr(void) interrupt 12
{
    static uint i;
    i = (i + 1) % 30000;

    seg_display();

    if (i % SONIC_TIME == 0)
    {
        sonic_flag = 1;
    }
}


void sonic_proc()
{
    distance = sonic_measure();
}