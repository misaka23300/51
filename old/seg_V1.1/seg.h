#ifndef __SEG_H__
#define __SEG_H__

#include "boot.h"
#include "led.h"
extern uchar seg_array[8];
void seg_display();
extern uchar clock_array[3];
uchar seg_clock();


#endif