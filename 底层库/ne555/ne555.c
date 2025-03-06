// T0 为计数器 8位自动重载 


void timer_0() interrupt 1
{
    times0++;
    if (times > 35000)
    {
        times1++;
        times0 = 0;
    }
}


void timer_1() interrupt 3
{
    static uint i;
    i = (i + 1) % 30000;

    if (i % 1000 == 0)
    {
        freq = times1 * 35000 + times0;
        times1 = 0; times0 = 0;
    }

}