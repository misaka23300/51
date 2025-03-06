#ifndef __SYS_H__
#define __SYS_H__

#include <STC15F2K60S2.H>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

// 0x1F -> 0001 1111
// 0x80 -> 1000 0000
#define LATCH_ON P2 = (P2 & 0x1F) | 0x80
#define LATCH_OFF P2 = P2 & 0x1F

void sys_init();
void Delay50ms();
void sleep(int ms);

#endif