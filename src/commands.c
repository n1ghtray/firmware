#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_array.h"
#include "config.h"
#include "fire.h"

int set_accel_delay(int delay)
{
    accel_delay = delay;
}

int get_accel_delay()
{
    return accel_delay;
}

int set_after_firing_delay(int delay)
{
    after_firing_delay = delay;
}

int get_after_firing_delay()
{
    return after_firing_delay;
}

int set_pic_index(int index)
{
    pic_index = index;
}

int get_pic_index()
{
    return pic_index;
}

int set_pic_size(int size)
{
    pic_size = size;
}

int get_pic_size()
{
    return pic_size;
}

int set_pic_at_index(int index, data_entry_t data)
{
    for (int j = 0; j < A_LENGTH; j++)
    {
        pic[index].data[j] = data.data[j] &= 0b0011111111111111; // Ensure the two most significant bits are 0
    }
}

int set_pic(data_entry_t data)
{
    for (int j = 0; j < A_LENGTH; j++)
    {
        pic[pic_index].data[j] = data.data[j] &= 0b0011111111111111;
    }
    pic_index++;
    pic_size = pic_index;
}

int set_p_mask(long long p_mask)
{
    GPIO_P_MASK = p_mask;
}

long long get_p_mask()
{
    return GPIO_P_MASK;
}

int clear_pic()
{
    memset(pic, 0, sizeof(pic));
    pic_index = 0;
    pic_size = 0;
}

int fire_pic()
{
    sem_release(&start_firing);
}

int purge_nozzles(int times)
{
    for (int i = 0; i < times; i++)
        fire(&purge);
}