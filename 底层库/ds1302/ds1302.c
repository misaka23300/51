#include "ds1302.h"

sbit SCK = P1^7;
sbit RST = P1^3;
sbit SDA = P2^3;

//
void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

//uchar write_address[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C};
//uchar read_address[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8B, 0x8D};

//

void init_ds1302(uchar hour, min, sec)
{
    uchar tmp;
    Write_Ds1302_Byte(0x8E, 0x00);

    tmp = sec / 10 << 4 + sec % 10;
    Write_Ds1302_Byte(0x80, tmp);

    tmp = min / 10 << 4 + min % 10;
    Write_Ds1302_Byte(0x82, tmp);

    tmp = hour / 10 << 4 + hour % 10;
    Write_Ds1302_Byte(0x84, tmp);

    Write_Ds1302_Byte(0x8E,0x80);
}

char get_time(uchar address)
{
    // 0x81, 0x83, 0x85
    char tmp;
    tmp = Read_Ds1302_Byte(address);
    tmp = tmp >> 4 * 10 + tmp & 0x0F;
    return tmp;
}