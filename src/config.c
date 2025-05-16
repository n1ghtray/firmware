#include "config.h"

long long GPIO_P_MASK = 0xFFFC000000;

volatile int pic_index = 0;
volatile int pic_size = 0;

volatile uint32_t accel_delay = 100000;
volatile uint16_t after_firing_delay = 30;

bool interrupt_triggered = false;
bool printing = false;

semaphore_t start_firing;
