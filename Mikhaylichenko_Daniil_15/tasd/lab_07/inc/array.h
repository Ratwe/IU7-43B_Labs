#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "../inc/defines.h"

typedef struct array
{
    char **data;
    size_t size;
} array_t;

void free_array(char **data, size_t size);
array_t *fill_array(char *file_name);
size_t get_arr_size_in_bytes(array_t *array);

#endif // __ARRAY_H__
