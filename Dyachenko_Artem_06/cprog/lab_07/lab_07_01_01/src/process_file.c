#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "process_file.h"
#include "defines.h"

int check_open_file(char *filename)
{
    struct stat buffer;
    return stat(filename, &buffer);
}

void read_file(FILE *f, int *ps, int *pf)
{
    int num = 0;

    for (; ps < pf; ps++)
    {
        if (fscanf(f, "%d", &num) == 1)
        {
            *ps = num;
            LOG_DEBUG("[DB] *ps = %d\n", *ps);
        }
    }
}

int write_file(char *filename, int *pb_dst, int *pe_dst)
{
    if (check_open_file(filename))
        return OPEN_FILE_ERROR;

    FILE* f = fopen(filename, "w");
    int *ptr = pb_dst;

    while (ptr < pe_dst)
    {
        fprintf(f, "%d ", *ptr);
        ptr++;
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int calc_count(char *filename, int *count)
{
    if (check_open_file(filename))
        return OPEN_FILE_ERROR;

    FILE* f = fopen(filename, "r");
    int num = 0;

    while (fscanf(f, "%d", &num) != EOF)
        (*count)++;

    fclose(f);

    if (*count == 0)
        return EMPTY_ARRAY_ERROR;

    return EXIT_SUCCESS;
}

int fill_array(char *filename, int **arr, int count)
{
    if (check_open_file(filename))
        return OPEN_FILE_ERROR;

    *arr = (int *)malloc(count * sizeof(int));

    if (*arr == NULL)
        return CALLOC_ERROR;

    int *ps = *arr;
    int *pf = ps + count;
    int *pa = *arr;
    int num = 0;

    FILE* f = fopen(filename, "r");

    read_file(f, ps, pf);

    while (pa < pf)
    {
        LOG_DEBUG("[DB] pa: %d\n", *pa);
        LOG_DEBUG("[DB] %p\n", (void*) pa);
        fscanf(f, "%d\n", pa);
        if (fscanf(f, "%d", &num) == 1)
            *pa = num;

        pa++;
    }
    
    fclose(f);
    return EXIT_SUCCESS;
}
