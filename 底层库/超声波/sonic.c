#include "sonic.h"

sbit tx = P1 ^ 0;
sbit rx = P1 ^ 1;

void send_measure()
{
    uchar i;
    for (i = 0;i < 10;i++)
    {
        tx = 0;
        Delay14us();
        tx = 1;
        Delay14us();
    }
}

uchar sonic_measure()
{
    uchar distance;

    // 关闭定时器
    TR0 = 0;
    // 定时器值设置为0
    TL0 = 0; TH0 = 0;

    // 发送超声波
    send_measure();

    // 等待接收端电平为低
    // 可以不写
    while(rx == 0);

    // 开启定时器
    TR0 = 1;

    // 当接受端电平为高 并且定时器未溢出
    while (rx == 1 && TF0 == 0);

    // 关闭定时器
    TR0 = 0;

    // 返回值 没有溢出
    if (TF0 == 1)
    {
        TF0 = 0;
        distance = 99;
    }
       
    else
        distance = (uchar) ( ( (TH0 << 8) | TL0) * 0.017);

    // 重新设置为0
    TL0 = 0; TH0 = 0;
    return distance;
}
