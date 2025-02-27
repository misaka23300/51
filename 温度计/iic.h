#ifndef __IIC_H__
#define __IIC_H__

#include "boot.h"

ovid pcf8591_write(uchar address, uchar data_);
uchar pcf8591_read(uchar address);

#endif