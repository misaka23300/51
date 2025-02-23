void s_and_g(uchar i,bit state)
{
    static uchar tmp;
    static ucahr last = 0xFF;

    if (state)
    {
        tmp = tmp | 0x01 << i;
    }
    else
    {
        tmp = tmp & ~(0x01 << i);
    }

    if (tmp != last)
    {
        P0 = ~tmp;
        batch(5);
        batch(0);

        last = tmp;
    }
}
