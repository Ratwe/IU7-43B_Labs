#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "process_file.h"
#include "process_array.h"

int process_args(int argc, char **argv, int *filter_flag)
{
    if (argv == NULL)
        return NULL_POINTER_ERROR;

    if (argc > ARGC_MAX || argc < ARGC_MIN)
        return ARGC_ERROR;

    if (argc == ARGC_MAX)
    {
        if (*argv[3] != 'f')
            return ARGV_ERROR;

        *filter_flag = 1;
    }

    return EXIT_SUCCESS;
}

int check_flag(int filter_flag, int **arr, int count, int **pb_dst, int **pe_dst)
{
    int error_code = EXIT_SUCCESS;

    if (filter_flag)
    {
        for (int i = 0; i < count; i++)
            LOG_DEBUG("[DB] arr[%d]: %d\n", i, *(*arr + i));

        if ((error_code = key(*arr, *arr + count, pb_dst, pe_dst)))
        {
            free(*arr);
            return error_code;
        }
    }
    else
    {
        *pb_dst = (int *) malloc(count * sizeof(int));

        if (*pb_dst == NULL)
        {
            free(*pb_dst);
            free(*arr);
            return CALLOC_ERROR;
        }

        int *ptr = *pb_dst;

        for (int *p = *arr; p < *arr + count; p++, ptr++)
            *ptr = *p;

        *pe_dst = ptr;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    int filter_flag = 0, count = 0, error_code = EXIT_SUCCESS;
    int *arr = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    if ((error_code = process_args(argc, argv, &filter_flag)))
        return error_code;

    if ((error_code = calc_count(argv[1], &count)))
        return error_code;

    LOG_DEBUG("[DB] count: %d\n", count);

    if (count == 0)
        return EMPTY_ARRAY_ERROR;

    if ((error_code = fill_array(argv[1], &arr, count)))
        return error_code;

    if ((error_code = check_flag(filter_flag, &arr, count, &pb_dst, &pe_dst)))
        return error_code;

    mysort(pb_dst, pe_dst - pb_dst, sizeof(int), funccmp);

    LOG_ARR_DEBUG(pb_dst, pe_dst);

    error_code = write_file(argv[2], pb_dst, pe_dst);

    free(pb_dst);
    free(arr);

    return error_code;
}
