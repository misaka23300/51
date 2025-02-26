#include "iic.h"

sbit scl = P2 ^ 0;
sbit sda = P2 ^ 1;

#define DELAY_TIME	10

//
static void I2C_Delay(unsigned char n)
{
    do
    {
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();		
    }
    while(n--);      	
}

//
void I2CStart(void)
{
    sda = 1;
    scl = 1;
	I2C_Delay(DELAY_TIME);
    sda = 0;
	I2C_Delay(DELAY_TIME);
    scl = 0;    
}

//
void I2CStop(void)
{
    sda = 0;
    scl = 1;
	I2C_Delay(DELAY_TIME);
    sda = 1;
	I2C_Delay(DELAY_TIME);
}


void at2402_read(uchar address)
{
    uchar data_;

    I2CStart();

    I2CSendByte(0xA0);
    I2CWaitAck();

    I2CSendByte(address);
    I2CWaitAck();

    I2CStart();

    I2CSendByte(0xA1);
    I2CWaitAck();

    data_ = I2CReceiveByte();
    I2CSendAck(1);

    I2CStop();
    Delay10us();
}

uchar at2402_wirte(uchar address,uchar data_)
{
    I2CStart();

    I2CSendByte(0xA0);
    I2CWaitAck();

    I2CSendByte(address);
    I2CWaitAck();

    I2CSendByte(data_);
    I2CWaitAck();

    I2CStop();
    I2CDelay10us();
}


//0-255 0x00 0xff
void AT24C02_Write(uchar *dat,uchar addr,uchar num)    //1.数据 2.地址 3.多少个数据
{
	I2CStart();

	I2CSendByte(0xa0);
	I2CWaitAck();

	I2CSendByte(addr);
	I2CWaitAck();

	while(num--)
	{
		I2CSendByte(*dat++);
		I2CWaitAck();

		I2C_Delay(200);
	}
	I2CStop();
	Delay5ms();
}

void AT24C02_Read(uchar *dat,uchar addr,uchar num)
{
	I2CStart();

	I2CSendByte(0xa0);
	I2CWaitAck();

	I2CSendByte(addr);
	I2CWaitAck();
	
	I2CStart();

	I2CSendByte(0xa1);
	I2CWaitAck();

	while(num--)
	{
		*dat++=I2CReceiveByte();
		if(num)
            I2CSendAck(0);
		else 
            I2CSendAck(1);
	}
	I2CStop();
}