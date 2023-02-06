#include <stdio.h>
#include <stdlib.h>

#include "process_file.h"

#define TESTS_NUM 4

int main()
{
    int err = 0;
    int *pb_dst = NULL, *pe_dst = NULL;
    int count = 0;
    char *filename = "random_file.txt";

    if (check_open_file(filename))
        err++;

    if (calc_count(filename, &count))
        err++;

    if (write_file(filename, pb_dst, pe_dst))
        err++;

    int *arr = malloc(5 * sizeof(int));

    for (int i = 0; i < count; i++)
        arr[i] = i;

    if (fill_array(filename, &arr, count))
        err++;

    free(arr);

    if (err == TESTS_NUM)
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}
