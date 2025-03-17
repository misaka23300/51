#include "ds1302.h"
#include <intrins.h>

sbit SCK=P1^7;		
sbit SDA1=P2^3;		
sbit RST = P1^3;   // DS1302??												

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA1=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

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
 		if(SDA1)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA1=0;	_nop_();
	SDA1=1;	_nop_();
	return (temp);			
}

void Init_Ds1302(uchar hour,min,sec)
{
 uchar temp;
	Write_Ds1302_Byte(0x8e,0);
	temp=sec/10<<4+sec%10;
	Write_Ds1302_Byte(0x80,temp);
	temp=min/10<<4+min%10;
	Write_Ds1302_Byte(0x80,temp);
	temp=hour/10<<4+hour%10;
	Write_Ds1302_Byte(0x80,temp);
	Write_Ds1302_Byte(0x8e,0x80);
}

char Get_Ds1302(uchar addr)
{
 char temp;
	temp=Read_Ds1302_Byte(addr);
	temp=temp/16*10+temp%16;
	return temp;
}