#include <stdio.h>
#include <stdlib.h>
#include "file_interface.h"

#define UNCORRECT_ARGS      1
#define COUNT_INPUT_VALUES  1
#define MINIMAL_ARGC        3
#define MAXIMAL_ARGC        4

int main(int argc, char **argv)
{
    int error_code = EXIT_SUCCESS;

    if (argc < MINIMAL_ARGC || argc > MAXIMAL_ARGC)
        error_code = UNCORRECT_ARGS;
    if (!error_code)
    {
        if (argv[1][0] == 'c' && argc == MAXIMAL_ARGC)
        {
            size_t number;

            if (sscanf(argv[3], "%zu", &number) != COUNT_INPUT_VALUES)
                error_code = UNCORRECT_ARGS;
            else 
                error_code = fill_file(argv[2], number);
        }
        else if (argv[1][0] == 'p')
            error_code = print_file(argv[2]);
        else if (argv[1][0] == 's')
            error_code = sort_file(argv[2]);
        else
            error_code = UNCORRECT_ARGS;
    }

    return error_code;
}
