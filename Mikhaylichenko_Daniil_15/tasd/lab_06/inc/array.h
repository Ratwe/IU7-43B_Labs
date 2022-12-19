#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "../inc/defines.h"

typedef struct array
{
    char **data;
    size_t size;
    size_t max_size;
} array_t;

void free_array(char **data, size_t size);
array_t *fill_array(char *file_name);

#endif // __ARRAY_H__
