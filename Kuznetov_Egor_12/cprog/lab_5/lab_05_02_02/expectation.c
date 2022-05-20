#include "expectation.h"
#include "defines.h"

int expectation_x(FILE *const input_file, double *result)
{
    int error_code = EXIT_SUCCESS;
    size_t size = 0;
    double temp;

    fseek(input_file, 0, SEEK_SET);
    *result = 0;

    while (fscanf(input_file, "%lf", &temp) == COUNT_INPUT_VALUES)
    {
        *result += temp;
        size++;
    }

    if (size)
        *result /= size;
    else
        error_code = EMPTY_FILE;

    return error_code;
}

int expectation_sqr_x(FILE *const input_file, double *result)
{
    int error_code = EXIT_SUCCESS;
    size_t size = 0;
    double temp;

    fseek(input_file, 0, SEEK_SET);
    *result = 0;

    while (fscanf(input_file, "%lf", &temp) == COUNT_INPUT_VALUES)
    {
        *result += temp * temp;
        size++;
    }

    if (size)
        *result /= size;
    else
        error_code = EMPTY_FILE;

    return error_code;
}
