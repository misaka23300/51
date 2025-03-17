#ifndef __SYS_H__
#define __SYS_H__
#include <STC15F2K60S2.H>
#define uchar unsigned char
#define uint unsigned int

#define Y4 P2=(P2&0x1f)|0x80
#define Y5 P2=(P2&0x1f)|0xa0
#define Y6 P2=(P2&0x1f)|0xc0
#define Y7 P2=(P2&0x1f)|0xe0
#define Y0 P2&=0x1f

void Timer0_Init();
void Delay1ms();
void sys_init();
void delay(uchar x);

#endif