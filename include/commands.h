#ifndef COMMANDS_H
#define COMMANDS_H
#include "config.h"
#include "data_array.h"

int set_accel_delay(int delay);
int get_accel_delay();

int set_after_firing_delay(int delay);
int get_after_firing_delay();

int set_pic_index(int index);
int get_pic_index();

int set_pic_size(int size);
int get_pic_size();

int set_pic_at_index(int index, data_entry_t data);
int set_pic(data_entry_t data);

int set_p_mask(long long p_mask);
long long get_p_mask();

int clear_pic();

int fire_pic();
int purge_nozzles(int times);

#endif