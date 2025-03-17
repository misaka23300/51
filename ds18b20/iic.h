#ifndef __IIC_H__
#define __IIC_H__
#include "sys.h"

void AT24_Write(uchar addr,uchar dat);
uchar AT24_Read(uchar addr);
uchar I2CReceiveByte();
uchar I2CWaitAck();
void I2CSendAck(uchar ackbit);
void I2CSendByte(uchar byt);
void I2CStop();
void I2CStart();
static void I2C_Delay(uchar n);

#endif