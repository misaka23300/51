#include "main.c"

#define KEY_TIME 15
#define TEMP_TIME 1000

extern uchar led_value[8];
bit key_flag;

// 0 -> high, 1 -> low
bit show_state, temperature_flag;

uchar state;
uchar temp_value[3] = {0, 0, 0};

char adjust;
char adjust_value[3] = {0, 0, 0};

char argument = 26;
char argument_value[3] = {0, 0, 0};

/* 
press -> adjust -> adjust_value -> seg
*/
void main()
{
    boot_init();
    read_temperature();

    while (1)
    {
        if (key_flag)
        {
            key_flag = 0;
            state = key_proc();
        }

        if (temperature_flag)
        {
            temperature_flag = 0;
            temperature_proc();
        }

        state_machine();
    }
}

void timer_1() interrupt 3
{
    static uint i;
    i = (i + 1) % 30000;

    seg_dpslay();
    led_display();

    if (i % KEY_TIME == 0)
    {
        key_flag = 1;
    }

    if (i % TEMP_TIME == 0)
    {
        temperature_flag = 1;
    }
}

void key_proc()
{   
    uchar press;
    press = key_scan();

    switch (press)
    {
        case 4:
        {
            state = (state + 1) % 3;
            s4_state(state);
        }
        break;

        case 5:
        {
            show_state = ~show_state;

            led_value[3] = show_state;
            led_value[4] = ~show_state;
        }
        break;

        case 8:
        {
            if (state == 1)
            {
                adjust = (adjust + 1) % 100;
                adjust_proc();
            }
            else if (state == 2)
            {
                argument = (argument + 1) % 100;
                argument_proc();
            }
        }
        break;

        case 9:
        {
            if (state == 1)
            {
                adjust--;
                if (adjust == -99)
                    adjust = 0;
            }
            else if (state == 2)
            {
                argument--;
                if (argument == -99)
                    argument = 0;
            }
        }
        break;
    }
}

void state_machine()
{
    // 数码管显示
    
    switch (state)
    {
        case 0:
        {
            //C x x x x T T T
            set_seg(12, 16, 16, 16, 16, temp_value[2], temp_value[1] + 32, temp_value[0]);
        }
        break;

        case 1:
        {
            // 需要显示负数
            set_seg(14, 16, 16, 16, 16, adjust_value[2], adjust_value[1], adjust_value[0]);
        }
        break;

        case 2:
        {
            set_seg(21, 16, 16, 16, 16, argument_value[2], argument_value[1], argument_value[0]);
        }
        break;
    }
}

void temperature_proc()
{
    // 获取温度并转换为全局变量的数组
    uchar i;
    int temperature;

    temperature = (int) (read_temperature() * 100);

    uchar temp_check = (uchar)(temperature / 100) + adjust;
    if (show_state)
    {
        if (temp_check > adjust)
        {
            led_value[7] = 1; 
        }
        else
        {
            led_value[7] = 0;
        }
    }
    else
    {
        if (temp_check < adjust)
        {
            led_value[7] = 1; 
        }
        else
        {
            led_value[7] = 0;
        }
    }
    
    temperature = temperature + adjust;
    temp_value[0] = (uchar) (temperature / 1000 % 10);
    temp_value[1] = (uchar) (temperature / 100 % 10);
    temp_value[2] = (uchar) (temperature / 10 % 10) ;

    delete_0(temp_value, 3);
}

void adjust_proc()
{
    hex_to_seg(adjust_value, adjust);
}

void argument_proc()
{
    hex_to_seg(argument_value, argument);
}

void hex_to_seg(char *output, char input)
{
    if (input < 0)
    {
        input = -input;
        output[1] = input % 10;
        output[0] = input / 10 % 10;

        // 删0加负号
        if (arrays[1] == 0)
        {
            arrays[1] = 17;
        }
        else
            arrays[2] = 17;
        
    }
    else
    {
        output[1] = input % 10;
        output[0] = input / 10 % 10;

        delete_0(input_value, 2);
    }
}

void delete_0(uchar* arrays, uchar j)
{
    for (i = 0;i < (j - 1); i++)
    {
        if (arrays[i] == 0)
        {
            arrays[i] = 16;
        }
        else
            break;
    }
}
