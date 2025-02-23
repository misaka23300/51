#ifndef __LED_H__
#define __LED_H__

#include "boot.h"
void led(uchar i, bit state);
extern uchar led_array[8];
void led_display();
void led_water();

#endif
