#include "interrupt_handler.h"
#include "hardware/gpio.h"
#include "config.h"
#include <stdio.h>

void fire_handler(uint gpio, uint32_t events)
{
    printing = true;
    sem_release(&start_firing);
    printf("INTERRUPT TRIGGERED\n");
}

void initialize_interrupts()
{
    gpio_set_irq_callback(fire_handler);

    irq_set_enabled(IO_IRQ_BANK0, true);

    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(FIRE_PIN, GPIO_IRQ_EDGE_RISE, true);
}