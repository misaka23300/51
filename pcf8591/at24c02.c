v

oid AT24C02_Write(unsigned char *dat,unsigned char addr,unsigned char num)    //1.数据 2.地址 3.多少个数据
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

void AT24C02_Read(unsigned char *dat,unsigned char addr,unsigned char num)
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
		if(num)I2CSendAck(0);
		else I2CSendAck(1);
	}

	I2CStop();
}

uchar address = 0xA0;
void at24_write(uchar byte_address, uchar byte)
{
    I2CStart();

    I2CSendByte(address);
    I2CWaitAck();

    I2CSendByte(byte_address)
    I2CWaitAck();

    I2CSendByte(byte);
    I2CWaitAck();

    I2CStop();

    delay10ms();
}


uchar at24_reda()
{
    I2CStart();

    I2CSendByte(0xA0);
    I2CWaitAck();

    I2CSendByte(address);
    I2CWaitAck();

    I2CStart();

    I2CSendByte(0xA1);
    I2CWaitAck();

    dat = I2CReceiveByte();
    I2CSendAck(1);

    I2CStop();

    delay10ms();
    return dat;

}