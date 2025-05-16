#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "command_parser.h"
#include "interrupt_handler.h"
#include "utils.h"
#include "fire.h"
#include "gpio_control.h"
#include "data_array.h"

int main()
{
    memset(pic, 0, sizeof(pic));
    stdio_init_all();
    initialize_gpio();
    sem_init(&start_firing, 0, 1);
    initialize_interrupts();
    multicore_launch_core1(wait_and_fire);

    char input_buffer[200];
    uint8_t buffer_index = 0;

    while (true)
    {
        int c = getchar_timeout_us(0);
        if (c == PICO_ERROR_TIMEOUT)
        {
            continue;
        }

        if (c == '\n' || c == '\r')
        {
            input_buffer[buffer_index] = '\0';
            printf("Received: '%s'\n", input_buffer);
            process_command(input_buffer);
            buffer_index = 0;
            while (getchar_timeout_us(1) != PICO_ERROR_TIMEOUT)
                ; // Clear buffer
        }
        else if (buffer_index < sizeof(input_buffer) - 1)
        {
            input_buffer[buffer_index++] = (char)c;
        }
    }
}