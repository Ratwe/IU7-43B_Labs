#include <stdio.h>
#include "interface.h"
#include "defines.h"

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
                error_code = create(argv[2], number);
        }
        else if (argv[1][0] == 'p')
            error_code = print(argv[2]);
        else if (argv[1][0] == 's')
            error_code = sort(argv[2]);
        else
            error_code = UNCORRECT_ARGS;
    }

    return error_code;
}
