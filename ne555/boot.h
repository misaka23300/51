#ifndef __BOOT_H__
#define __BOOT_H__

#include <STC15F2K60S2.H>

#define uchar unsigned char
#define uint unsigned int

void boot_init();

void timer();
void batch(uchar i);
void timer_0();
void timer_1();

#endif