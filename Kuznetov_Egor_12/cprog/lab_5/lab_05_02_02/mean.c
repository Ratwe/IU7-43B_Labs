#include "mean.h"
#include <stdlib.h>

#define COUNT_INPUT_VALUES  1
#define EMPTY_FILE          3

int function_mean(FILE *const input_file, double (*edit_value)(double), double *result)
{
    int error_code = EXIT_SUCCESS;
    size_t size = 0;
    double temp;

    fseek(input_file, 0, SEEK_SET);
    *result = 0;

    while (fscanf(input_file, "%lf", &temp) == COUNT_INPUT_VALUES)
    {
        *result += (*edit_value)(temp);
        size++;
    }

    if (size)
        *result /= size;
    else
        error_code = EMPTY_FILE;

    return error_code;
}
