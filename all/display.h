#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "boot.h"

void led_display();
void sandy(uchar i,bit state);
void control(uchar i,bit state,uchar j);
void seg_display();


#endif