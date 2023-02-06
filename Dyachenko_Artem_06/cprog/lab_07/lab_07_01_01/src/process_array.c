#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "process_array.h"
#include "defines.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (!pb_src || !pe_src || !pb_dst || !pe_dst)
        return NULL_POINTER_ERROR;

    if (pb_src > pe_src)
        return DATA_RANGE_ERROR;

    int count = 0;
    int const *ptr = pb_src, *p_max = ptr, *p_min = ptr;

    while (ptr < pe_src)
    {
        if (*ptr > *p_max)
            p_max = ptr;

        if (*ptr < *p_min)
            p_min = ptr;

        ptr++;
    }

    LOG_DEBUG("[DB] min = %d, max = %d\n", *p_min, *p_max);

    ptr = p_min < p_max ? p_min : p_max;  // указатель на первый мин/макс элемент
    int const *ptr_r = p_max > p_min ? p_max : p_min;
    LOG_DEBUG("[DB] right side of ptr: %p\n", ptr_r);

    while (ptr < ptr_r)
    {
        if (ptr != p_min && ptr != p_max)
            count++;

        ptr++;
    }

    LOG_DEBUG("p_max - p_min: %ld\n", p_max - p_min);
    LOG_DEBUG("count: %d\n", count);

    if (!count)
        return EMPTY_ARRAY_ERROR;

    *pb_dst = malloc(count * sizeof(int));

    *pe_dst = *pb_dst + count;

    int *pb = *pb_dst;
    ptr = (p_min < p_max ? p_min : p_max) + 1;

    LOG_DEBUG("[DB] pe_dst - pb: %ld\n", *pe_dst - pb);

    while (ptr < ptr_r)
    {
        // LOG_DEBUG("[DB] --------------------\n");
        // LOG_DEBUG("[DB] *ptr_: %d\n", *ptr);
        // LOG_DEBUG("[DB] *pb: %d\n", *pb);

        *pb = *ptr;
        pb++;
        ptr++;
    }

    LOG_DEBUG("[DB] --------------------\n");

    return EXIT_SUCCESS;
}

int funccmp(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

void swap(char *a, char *b, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        char temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void*, const void*))
{
    char *fp = first;

    for (size_t i = 0; i < number; i++)
    {
        if (i % 2 == 0)
        {
            for (size_t j = 0; j < number - 1; j++)
                if (comparator(fp + j * size, fp + (j + 1) * size) > 0)
                    swap(fp + j * size, fp + (j + 1) * size, size);
        }
        else
            for (size_t j = number - 1; j > 0; j--)
                if (comparator(fp + (j - 1) * size, fp + j * size) > 0)
                    swap(fp + j * size, fp + (j - 1) * size, size);
    }
}
