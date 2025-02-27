#ifndef __IIC_H__
#define __IIC_H__

#include "boot.h"

void pcf8591_write(uchar address, uchar data_);

uchar pcf8591_ADC(uchar channel);
void pcf8591_DA(uchar v);

#endif