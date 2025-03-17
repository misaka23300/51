#include "iic.h"
#include "intrins.h"

sbit scl=P2^0;
sbit sda=P2^1;
#define DELAY_TIME 5

static void I2C_Delay(uchar n)
{
 do
 {
  _nop_();_nop_();_nop_();_nop_();_nop_();
	 _nop_();_nop_();_nop_();_nop_();_nop_();
	 _nop_();_nop_();_nop_();_nop_();_nop_();
 }
 while(n--);
}

void I2CStart()
{
 sda=1;
	scl=1;
	I2C_Delay(DELAY_TIME);
	sda=0;
	I2C_Delay(DELAY_TIME);
	scl=0;
}

void I2CStop()
{
 sda=0;
	scl=1;
	I2C_Delay(DELAY_TIME);
	sda=1;
	I2C_Delay(DELAY_TIME);
}

void I2CSendByte(uchar byt)
{
 uchar i;
	for(i=0;i<8;i++)
	{
	 scl=0;
		I2C_Delay(DELAY_TIME);
		if(byt&0x80)
		{
		 sda=1;
		}
	  else
	  {
	   sda=0;
	  }
	  I2C_Delay(DELAY_TIME);
	  scl=1;
	  byt<<=1;
	  I2C_Delay(DELAY_TIME);
  }
	scl=0;
}

void I2CSendAck(uchar ackbit)
{
 scl=0;
	sda=ackbit;
	I2C_Delay(DELAY_TIME);
	scl=1;
	I2C_Delay(DELAY_TIME);
	scl=0;
	sda=1;
	I2C_Delay(DELAY_TIME);
}

uchar I2CWaitAck()
{
 uchar ackbit;
	scl=1;
	I2C_Delay(DELAY_TIME);
	ackbit=sda;
	scl=0;
	I2C_Delay(DELAY_TIME);
	
	return ackbit;
}

uchar I2CReceiveByte()
{
 uchar da,i;
	for(i=0;i<8;i++)
	{
	 scl=1;
		I2C_Delay(DELAY_TIME);
		da<<=1;
		if(sda)
			da |=0x01;
		scl=0;
		I2C_Delay(DELAY_TIME);
	}
	return da;
}

uchar AT24_Read(uchar addr)
{
 uchar dat;
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(0xa1);
	I2CWaitAck();
	dat=I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
	delay(10);
	return dat;
}

void AT24_Write(uchar addr,uchar dat)
{
 I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	I2CSendByte(dat);
	I2CWaitAck();
	I2CStop();
	delay(10);
}