#include "command_parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_array.h"
#include "commands.h"
#include "config.h"

bool command_executed = false;

void process_command(char *command)
{
    if (strlen(command) > 199)
    {
        printf("COMMAND TOO LONG\n");
        return;
    }

    if (strncmp(command, "SET_PIC", 7) == 0)
    {
        data_entry_t new_entry;
        if (sscanf(command + 7,
                   "%hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx",
                   &new_entry.data[0], &new_entry.data[1], &new_entry.data[2], &new_entry.data[3], &new_entry.data[4], &new_entry.data[5], &new_entry.data[6], &new_entry.data[7],
                   &new_entry.data[8], &new_entry.data[9], &new_entry.data[10], &new_entry.data[11], &new_entry.data[12], &new_entry.data[13], &new_entry.data[14],
                   &new_entry.data[15], &new_entry.data[16], &new_entry.data[17], &new_entry.data[18], &new_entry.data[19], &new_entry.data[20], &new_entry.data[21]) == A_LENGTH)
        {
            set_pic(new_entry);
            command_executed = true;
            printf("%d", pic_index);
        }
    }

    if (strncmp(command, "SET_PIC_AT_INDEX", 16) == 0)
    {
        int input_index;
        data_entry_t new_entry;
        if (sscanf(command + 16,
                   "%d %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx %hx", &input_index,
                   &new_entry.data[0], &new_entry.data[1], &new_entry.data[2], &new_entry.data[3], &new_entry.data[4], &new_entry.data[5], &new_entry.data[6], &new_entry.data[7],
                   &new_entry.data[8], &new_entry.data[9], &new_entry.data[10], &new_entry.data[11], &new_entry.data[12], &new_entry.data[13], &new_entry.data[14],
                   &new_entry.data[15], &new_entry.data[16], &new_entry.data[17], &new_entry.data[18], &new_entry.data[19], &new_entry.data[20], &new_entry.data[21]) == A_LENGTH + 1)
        {
            set_pic_at_index(input_index, new_entry);
            command_executed = true;
        }
    }

    if (strncmp(command, "SET_ACCEL_DELAY", 15) == 0)
    {
        set_accel_delay(atoi(command + 15));
        printf("%d\n", atoi(command + 15));
        command_executed = true;
    }

    if (strcmp(command, "GET_ACCEL_DELAY") == 0)
    {
        printf("%d\n", get_accel_delay());
        command_executed = true;
    }

    if (strncmp(command, "SET_AFTER_FIRING_DELAY", 22) == 0)
    {
        set_after_firing_delay(atoi(command + 22));
        printf("%d\n", atoi(command + 22));
        command_executed = true;
    }

    if (strcmp(command, "GET_AFTER_FIRING_DELAY") == 0)
    {
        printf("%d\n", get_after_firing_delay());
        command_executed = true;
    }

    if (strncmp(command, "SET_PIC_INDEX", 13) == 0)
    {
        set_pic_index(atoi(command + 13));
        printf("%d\n", atoi(command + 13));
        command_executed = true;
    }

    if (strcmp(command, "GET_PIC_INDEX") == 0)
    {
        printf("%d\n", get_pic_index());
        command_executed = true;
    }

    if (strncmp(command, "SET_PIC_SIZE", 22) == 0)
    {
        set_pic_size(atoi(command + 22));
        printf("%d\n", atoi(command + 22));
        command_executed = true;
    }

    if (strcmp(command, "GET_PIC_SIZE") == 0)
    {
        printf("%d\n", get_pic_size());
        command_executed = true;
    }

    if (strncmp(command, "SET_P_MASK", 10) == 0)
    {
        long long input_gpio_p_mask;
        sscanf(command + 10, "%llx", &input_gpio_p_mask);
        set_p_mask(input_gpio_p_mask);
        printf("%llX\n", input_gpio_p_mask);
        command_executed = true;
    }

    if (strcmp(command, "GET_P_MASK") == 0)
    {
        printf("%llX\n", get_p_mask());
        command_executed = true;
    }

    if (strcmp(command, "CLEAR_PIC") == 0)
    {
        clear_pic();
        printf("OK\n");
        command_executed = true;
    }

    if (strcmp(command, "FIRE") == 0)
    {
        fire_pic();
        printf("OK\n");
        command_executed = true;
    }

    if (strncmp(command, "PURGE", 5) == 0)
    {
        int times;
        sscanf(command + 5, "%d", &times);
        purge_nozzles(times);
        command_executed = true;
    }

    if (!command_executed)
        printf("UNKNOWN COMMAND\n");
    command_executed = false;
}