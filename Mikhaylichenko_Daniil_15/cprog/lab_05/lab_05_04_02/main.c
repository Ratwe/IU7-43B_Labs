#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "file_functions.h"

int main(int argc, char **argv)
{
    if (argc < MIN_ARGS || argc > MAX_ARGS)
        return WRONG_ARGS;

    int check;

    if (argc == MAX_ARGS && !strcmp(argv[1], "sb"))
    {
        check = sort_products_to_new_file(argv[2], argv[3]);
        if (check != EXIT_SUCCESS)
            return check;
    }
    else if (argc == MAX_ARGS && !strcmp(argv[1], "fb"))
    {
        check = print_certain_product(argv[2], argv[3]);
        if (check != EXIT_SUCCESS)
            return check;
    }
    else if (argc == MIN_ARGS && !strcmp(argv[1], "ab"))
    {
        check = add_to_data(argv[2]);
        if (check != EXIT_SUCCESS)
            return check;
    }
    else
        return WRONG_ARGS;

    return EXIT_SUCCESS;
}