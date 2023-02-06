/*
Тип чисел - целочисленные, int
Алгоритм сортировки - пузырьком
Сортировка по неубыванию
*/

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "defines.h"

int get_mode(int argc, char **argv, char *mode)
{
    if (argc < 3 || argc > 4)
        return WRONG_MAIN_ARGS;

    if (!strcmp(argv[1], "c"))
    {
        if (argc != 4)
            return WRONG_MAIN_ARGS;
        *mode = 'c';
    }
    else if (!strcmp(argv[1], "p"))
        *mode = 'p';
    else if (!strcmp(argv[1], "s"))
        *mode = 's';
    else
        return WRONG_MODE;

    return EXIT_SUCCESS;
}

int process_mode(char **argv, char mode)
{
    int error_code;

    switch (mode)
    {
        case 'c':
            if (atoi(argv[2]) < 1)
                return FILL_FILE_ERROR;
            error_code = fill_file(argv[3], atoi(argv[2]));
            break;
        case 'p':
            error_code = print_file(argv[2]);
            break;
        case 's':
            error_code = sort_file_data(argv[2]);
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
