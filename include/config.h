#ifndef CONFIG_H
#define CONFIG_H

#include "pico/sem.h"

#define A_LENGTH 22

#define GPIO_CLEAR_MASK 0b000111101111111111111100011111111111111111111110
#define GPIO_A_MASK 0b011111111111111111111110
#define GPIO_A_START 1
#define GPIO_P_START 26

#define FIRE_PIN 40
#define BUTTON_PIN 23

extern semaphore_t start_firing;

extern volatile int pic_index;
extern volatile int pic_size;

extern long long GPIO_P_MASK;

extern volatile uint32_t accel_delay;
extern volatile uint16_t after_firing_delay;

extern bool interrupt_triggered;
extern bool printing;

#endif