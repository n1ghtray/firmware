#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H
#include <stdint.h>
#include "pico.h"

void initialize_interrupts();
void fire_handler(uint gpio, uint32_t events);

#endif