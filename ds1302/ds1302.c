
uchar ds_write[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C};
uchar ds_read[7] = {0x81; 0x83; 0x85, 0x87, 0x89, 0x8B, 0x8D};

uchar ds_init_time[7] = {0x48, 0x34, 0x16, 0x22, 0x2, 0x3, 0x25};
. ,/m
sbit SCK = P1^7;            //位定义
sbit SDA = P2^3;
sbit RST = P1^3;

//秒、分、时、日、月、星期、年


uchar bcd_hex(uchar bcd)
{
    hex = (bcd >> 4) * 10 + (bcd & 0x0F); 
    return hex;
}

uchar hex_to_bcd(uchar hex)
{
    bcd = ( (hex / 10) << 4) + (hex % 10);
    return bcd;
}


void ds1302_init(uchar hour,uchar minute,uchar second)
{
    Write_Ds1302_Byte(0x8e,0x00);

    Write_Ds1302_Byte(ds_write[0], hex_to_bcd(second));

    Write_Ds1302_Byte(ds_write[1], hex_to_bcd(minute));

    Write_Ds1302_Byte(ds_write[2], hex_to_bcd(hour));

    Write_Ds1302_Byte(0x8e,0x80);
}

void DS1302_Read_Time()
{
	for(i=0;i<=6;i++)
	{
		DS1302_Time_Reset[i] = Read_Ds1302_Byte(DS1302_Read_adr[i]);
	}
	//0x35  ==  35           
	//3*16+5*1  / 16  =  3
	//3*16+5*1  % 16  =  5
	//3*10 + 5   
	for(i=0;i<=6;i++)
	{
		Time10[i] = DS1302_Time_Reset[i]/16*10 + DS1302_Time_Reset[i]%16;
	}
}


