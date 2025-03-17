#include "main.h"

bit led_flag,seg_flag,key_flag,settle_flag,nz_flag,nz_arrive,flash_flag,sec_flag,temp_flag;
uchar led_flash[]={0,0,0,0,0,0,0,0};
uchar clock[]={0,0,0};
uchar n_clock[]={99,99,99};
uchar disp_type=0;
uchar tmp[]={9,9,9};
uint temp;
uchar s4_times,s7_times;

void led_proc()
{
 if(led_flag)
 {
	 led_flag=0;
  if(nz_flag)
	{
	 if(nz_arrive)
	 {
	  led_flash[1]^=1;
		  led_flash[2]^=1;
	 }
	}
	else
	{
	 led_flash[1]=0;
	 led_flash[2]=0;
	}
 }
}

void seg_proc()
{
 if(seg_flag)
 {
  seg_flag=0;
	 switch(disp_type)
	 {
		 case 0:
		 if(nz_flag)
		 {
		  if(nz_arrive)
			{
			 if(flash_flag)
			 {
			  flash_flag=0;
				 setcontent(16,16,17,16,16,17,16,16);
			 }
			 else
			 {
			  setcontent(clock[0]/10,clock[0]%10,17,clock[1]/10,clock[1]%10,17,clock[2]/10,clock[2]%10);
			 }
			}
			else
			{
			 setcontent(clock[0]/10,clock[0]%10,17,clock[1]/10,clock[1]%10,17,clock[2]/10,clock[2]%10);
			}
		 }
		 else
		 {
		  setcontent(clock[0]/10,clock[0]%10,17,clock[1]/10,clock[1]%10,17,clock[2]/10,clock[2]%10);
		 }
		 break;
		 case 1:
		 {
		  if(s7_times==0)
			{
			 if(flash_flag)
			 {
			  flash_flag=0;
				 setcontent(15,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			 else
			 {
			  setcontent(15,17,16,16,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			}
			if(s7_times==1)
			{
			 if(flash_flag)
			 {
			  flash_flag=0;
				 setcontent(15,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			 else
			 {
			   setcontent(15,17,tmp[0]/10,tmp[0]%10,16,16,tmp[2]/10,tmp[2]%10);
			 }
			}
			if(s7_times==2)
			{
			 if(flash_flag)
			 {
			  flash_flag=0;
				 setcontent(15,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			 else
			 {
			   setcontent(15,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,16,16);
			 }
			}
			break;
		}
		  case 2:
		 {
		  if(s7_times==0)
			{
			 if(flash_flag)
			 {
			  flash_flag=0;
				 setcontent(24,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			 else
			 {
			  setcontent(24,17,16,16,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			}
			if(s7_times==1)
			{
			 if(flash_flag)
			 {
			  flash_flag=0;
				 setcontent(24,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			 else
			 {
			   setcontent(24,17,tmp[0]/10,tmp[0]%10,16,16,tmp[2]/10,tmp[2]%10);
			 }
			}
			if(s7_times==2)
			{
			 if(flash_flag)
			 {
			  flash_flag=0;
				 setcontent(24,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,tmp[2]/10,tmp[2]%10);
			 }
			 else
			 {
			   setcontent(24,17,tmp[0]/10,tmp[0]%10,tmp[1]/10,tmp[1]%10,16,16);
			 }
			}
			break;
		 }
		 case 3:
		 {
		  setcontent(n_clock[0]/10,n_clock[0]%10,17,n_clock[1]/10,n_clock[1]%10,17,n_clock[2]/10,n_clock[2]%10);
		 }
		 break;
		 case 4:
		 {
		  setcontent(26,16,17,16,temp/1000,temp%1000/100+32,temp%100/10,temp%10);
		 }
		 break;
  }
 }
}

void key_proc()
{
 uchar i,num;
	if(key_flag)
	{
	 key_flag=0;
		num=scankey();
		if(num!=99)
		{
		 switch(num)
		 {
			 case 4:
			  s4_times++;
			 if(!settle_flag)
			 {
			  switch(s4_times)
				{
					case 1:
					{
					 disp_type=3;
					}
					break;
					case 2:
					{
					 disp_type=4;
					}
					break;
					case 3:
					{
					 disp_type=0;
					}
					break;
				}
				s4_times%=3;
			 }
			 if(settle_flag)
			 {
			  switch(s4_times)
				{
					case 2:
					{
					 disp_type=1;
						tmp[0]=clock[0];
						tmp[1]=clock[1];
						tmp[2]=clock[2];
					}
					break;
					case 1:
					{
					 disp_type=2;
						tmp[0]=n_clock[0];
						tmp[1]=n_clock[1];
						tmp[2]=n_clock[2];
					}
					break;
				}
				 s4_times%=2;
			 }
			 break;
					case 5:
					if(settle_flag)
					{
					 switch(s7_times)
					 {
						 case 0:
						   tmp[0]++;
						   if(tmp[0]==24) tmp[0]=0;
						 break;
						 case 1:
						   tmp[1]++;
						   if(tmp[1]==60) tmp[1]=0;
						 break;
						 case 2:
						   tmp[2]++;
						   if(tmp[2]==60) tmp[2]=0;
						 break;
					 }
					}
					else
					{
					 disp_type=0;
					}
					break;
						case 6:
					if(settle_flag)
					{
					 switch(s7_times)
					 {
						 case 0:
						   tmp[0]--;
						   if(tmp[0]==0) tmp[0]=23;
						 break;
						 case 1:
						   tmp[1]--;
						   if(tmp[1]==0) tmp[1]=59;
						 break;
						 case 2:
						   tmp[2]--;
						   if(tmp[2]==0) tmp[2]=59;
						 break;
					 }
					}
					else
					{
					 disp_type=0;
					}
					break;
						 case 7:
             if(settle_flag)
						 {
						  s7_times++;
							 s7_times%=3;
						 }					
             else
						 {
						  disp_type=0;
							 settle_flag=0;
							 nz_flag=0;
						 }		
             break;
						 case 24:
						  settle_flag^=1;
              if(settle_flag)
							{
							 if(disp_type==0)
							 {
							  disp_type=1;
								 s7_times=0;
								 s4_times=0;
							 }
							}							
              else
							{
							 if(disp_type==1)
							 {
							  clock[0]=tmp[0];
								 clock[1]=tmp[1];
								 clock[2]=tmp[2];
								 
								 Init_Ds1302(tmp[0],tmp[1],tmp[2]);
								 
								 disp_type=0;
							 }
							 if(disp_type==2)
							 {
								 disp_type=0;
							  n_clock[0]=tmp[0];
								 n_clock[1]=tmp[1];
								 n_clock[2]=tmp[2];							 
								 for(i=0;i<3;i++)
								 {
								  AT24_Write(i,tmp[i]);
								 }
								 nz_flag=1;
							 }
							}			
              break;
						 case 27:
						 {
						  settle_flag=0;
							 disp_type=0;
							 nz_flag=0;
						 }						
             break;						 
		 }
		}
	}
}

void wmq_proc()
{
 if(nz_flag)
 {
  if(nz_arrive)
	{
	 wmq(6,flash_flag);
	}
 }
 else
 {
  wmq(6,1);
 }
}

void ds1302_proc()
{
 if(sec_flag)
 {
  sec_flag=0;
	 clock[2]=Get_Ds1302(0x81);
	 clock[1]=Get_Ds1302(0x83);
	 clock[0]=Get_Ds1302(0x85);
 }
}

void ds18b20_proc()
{
 float tmp;
	if(temp_flag)
	{
	 temp_flag=0;
		
		ET0=0;
		temp=read_temp();
		ET0=1;
		
		temp=(int)(tmp*100);
	}
}

void main()
{
	uchar i,dat;
  sys_init();
	Timer0_Init();
	for(i=0;i<3;i++)
	{
	 dat=AT24_Read(i);
		n_clock[i]=dat>99?0:dat;
	}
	nz_flag=1;
	
	Init_Ds1302(0x23,0x59,0x59);
	
	temp=read_temp();
	delay(1000);
	
	while(1)
	{
		
		ds1302_proc();
		ds18b20_proc();
		
	 led_proc();
		seg_proc();
		key_proc();
		wmq_proc();
	}
}

void Timer0_Isr() interrupt 1
{
	static uint k,cnt,nz_cnt;
	k++;
	if(k%3==0) display();
	if(k%5==0)
	{
	 led(cnt,led_flash[cnt++]);
		cnt%=8;
	}
	if(nz_arrive)
	{
	 nz_cnt++;
		if(nz_cnt==5000)
		{
		 nz_arrive=0;
			nz_flag=0;
			nz_cnt=0;
		}
	}
	if(clock[0]==n_clock[0]&&clock[1]==n_clock[1]&&clock[2]==n_clock[2])
	{
		nz_arrive=1;
	nz_flag=1;
	}
	if(k%10==0) key_flag=1;
	if(k%200==0) seg_flag=1;
	if(k%300==0) led_flag=1;
	if(k%500==0) flash_flag=1;
	
	if(k%100==0) sec_flag=1; 
	if(k%750==0) temp_flag=1; 
	
	k%=10000;
}	
