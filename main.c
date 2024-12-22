# include "main.h"

void main()
{
    sys_init();

    sharing_led(2);

    water_led_left();

    sharing_led(2);

    Delay50ms();

    water_led_right();
}