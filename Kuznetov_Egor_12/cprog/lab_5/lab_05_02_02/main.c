/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Program calculate variance of values in input file
 */
#include <stdio.h>
#include <stdlib.h>
#include "variance.h"

#define NO_FILE_IN_ARG  1
#define ARGC_EXPECTED   2
#define CANT_OPEN_FILE  2

int main(int argc, char **argv)
{
    int error_code = EXIT_SUCCESS;

    FILE *input_file;
    double result;

    if (argc != ARGC_EXPECTED)
        error_code = NO_FILE_IN_ARG;

    if (!error_code && !(input_file = fopen(argv[1], "r")))
        error_code = CANT_OPEN_FILE;

    if (!error_code && !(error_code = variance(input_file, &result)))
        printf("%lf", result);

    return error_code;
}
