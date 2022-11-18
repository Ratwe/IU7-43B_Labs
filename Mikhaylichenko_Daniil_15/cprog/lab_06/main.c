#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "file_functions.h"

int main(int argc, char **argv)
{
    if (argc < MIN_ARGS || argc > MAX_ARGS)
        return WRONG_ARGS;

    int check;

    if (argc == MIN_ARGS)
    {
        check = print_sort_file(argv[1]);
        if (check != EXIT_SUCCESS)
            return check;
    }
    else if (argc == MAX_ARGS)
    {
        check = print_certain_subject(argv[1], argv[2]);
        if (check != EXIT_SUCCESS)
            return check;
    }
    else
        return WRONG_ARGS;

    return EXIT_SUCCESS;
}
