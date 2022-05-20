/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Program calculate variance of values in input file
 */
#include <stdio.h>
#include "variance.h"
#include "defines.h"

int main(int argc, char **argv)
{
    int error_code = EXIT_SUCCESS;

    FILE *input_file;
    double result;

    if (argc != NORMAL_ARGC)
        error_code = NO_FILE_IN_ARG;

    if (!error_code && !(input_file = fopen(argv[1], "r")))
        error_code = CANT_OPEN_FILE;

    if (!error_code && !(error_code = variance(input_file, &result)))
        printf("%lf", result);

    return error_code;
}
