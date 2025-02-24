#include "pwm.c"


void pwm_timer0()   //10微秒@12.000MHz
{
    // 10ms
    AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xF6;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断

}

void Timer0_Isr(void) interrupt 1
{
    static uchar i;
    i = (i + 1) % 101;
    if (i > percent)
    {
        pwm_flag = 1;
        i = 0;
    }
    else
    {
        pwm_flag = 0;
    }
}

bit j;
if (pwm_flag)
{
    j = 1;    
}
else
{
    j = 0;
}


uchar i;
for(i = 0; i < 8; i++);
{
    led[i] = j;
}