#ifndef __BOOT_H_
#define __BOOT_H__

#include "STC15F2K60S2.H"
#include "intrins.h"

#define uchar unsigned char
#define uint unsigned int

#define Y4 P2 = (P2 & 0x0F) | 0x80
#define Y5 P2 = (P2 & 0x0F) | 0xA0
#define Y6 P2 = (P2 & 0x0F) | 0xC0
#define Y7 P2 = (P2 & 0x0F) | 0xE0


#endif