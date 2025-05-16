#ifndef DATA_ARRAY_H
#define DATA_ARRAY_H

#include <stdint.h>
#include "config.h"

typedef struct
{
    uint16_t data[A_LENGTH];
} data_entry_t;

extern data_entry_t purge;
extern data_entry_t pic[8000];

#endif // DATA_ARRAY_H
