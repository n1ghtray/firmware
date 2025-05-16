#include "fire.h"
#include "utils.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include "data_array.h"

void fire(data_entry_t *entry)
{

    for (int i = 0; i < A_LENGTH; i++)
    {
        // if (print)
        //     print_binary(entry->data[i]);

        gpio_put(42, 1); // set CLR pin HIGH for TLC59213AIPWR P1-P14
        gpio_put(44, 1); // set CLR pin HIGH for TLC59213AIPWR A1-A22

        uint32_t address = (1 << (GPIO_A_START + i));

        gpio_put_masked64(GPIO_A_MASK, address);

        gpio_put(43, 1); // rise CLK for all A
        busy_wait_us(1);
        gpio_put(43, 0); // fall CLK for all A
        busy_wait_us(1);
        gpio_put(43, 1); // rise CLK for all A

        // at this point, A is high and 2us has passed

        uint64_t repositioned_data = (uint64_t)entry->data[i] << GPIO_P_START;

        gpio_put_masked64(GPIO_P_MASK, repositioned_data);

        gpio_put(41, 1); // rise CLK for all P
        busy_wait_us(0.7);
        gpio_put(41, 0); // fall CLK for all P
        busy_wait_us(0.7);
        gpio_put(41, 1); // rise CLK for all P

        // at this point, all selected P are high and 1.4us has passed

        gpio_clr_mask64(GPIO_P_MASK);

        gpio_put(41, 1); // rise CLK for all P
        busy_wait_us(1);
        gpio_put(41, 0); // fall CLK for all P
        busy_wait_us(1);
        gpio_put(41, 1); // rise CLK for all P

        busy_wait_us(1);

        gpio_clr_mask64(GPIO_CLEAR_MASK); // Clear all A, P, CLK and CLR GPIO's

        // total time = ?us, we can desconsider the time wasted on CPU proccessing
        busy_wait_us(after_firing_delay);
    }
}

void wait_and_fire()
{

    while (true)
    {
        if (sem_try_acquire(&start_firing))
        {
            printf("FIRE REACHED\n");
            busy_wait_us(accel_delay);
            if (printing)
            {

                int local_size = pic_size;
                for (int i = 0; i < local_size; i++)
                {
                    fire(&pic[i]);
                }
                printing = false;
            }
        }

        // Evicts 100% CPU spinning
        tight_loop_contents();
    }
}