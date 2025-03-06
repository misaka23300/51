# include "sys.h"

void sys_init()
{
    P0 = 0xFF;
    LATCH_ON;
    LATCH_OFF;
}

void Delay50ms()	//@12.000MHz
{
	uchar data i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 72;
	k = 161;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void sleep(int ms)
{
    int i, j;
    for (i = 0; i < ms; i++)  // 每次外循环控制1毫秒
    {
        for (j = 0; j < 120; j++)  // 每次内循环大约耗时1微秒
        {
            // 空循环，什么都不做
        }
    }
}
