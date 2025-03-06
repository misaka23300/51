#include "main.h"

extern uchar seg[8];
uchar adc;
void main()
{
    boot_init();
    while (1)
    {
        //DAwrite(255);
    }

}


void timer() interrupt 1
{
    static uint i;
    i = (i + 1) % 3000;

    if (i % 1 == 0)
    {
        seg_display();
    }


    if (i % 500 == 0)
    {
        adc = ADread(0x03);

        seg[0] = adc / 100 % 10;
        seg[1] = adc /10 % 10;
        seg[2] = adc % 10;
    }
}