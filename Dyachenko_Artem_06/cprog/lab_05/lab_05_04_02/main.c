#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "products.h"

int get_mode(int argc, char **argv, char *mode)
{
    if (argc < 3 || argc > 4)
        return WRONG_MAIN_ARGS;

    if (!strcmp(argv[1], "sb") && argc == SORT_ARGS_COUNT)
        *mode = 's';
    else if (!strcmp(argv[1], "fb") && argc == PRINT_ARGS_COUNT)
        *mode = 'f';
    else if (!strcmp(argv[1], "ab") && argc == INSERT_ARGS_COUNT)
        *mode = 'a';
    else
        return WRONG_MODE;

    return EXIT_SUCCESS;
}

int process_mode(char **argv, char mode)
{
    int error_code = EXIT_SUCCESS;

    switch (mode)
    {
        case 's':
            error_code = sort_products(argv[2], argv[3]);
            break;
        case 'f':
            error_code = print_products(argv[2], argv[3]);
            break;
        case 'a':
            error_code = insert_product(argv[2]);
            break;
    }

    return error_code;
}

int main(int argc, char **argv)
{
    char mode;
    int error_code = get_mode(argc, argv, &mode);

    if (error_code)
        return error_code;

    error_code = process_mode(argv, mode);

    return error_code;
}
