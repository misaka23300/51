#ifndef __BOOT_H__
#define __BOOT_H__

#include <STC15F2K60S2.h>

#define uchar unsigned char
#define uint unsigned int 

void init();
void batch(uchar i);
void Timer0Init(void);

#endif