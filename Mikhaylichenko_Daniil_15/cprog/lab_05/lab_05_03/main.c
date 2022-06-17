/**
 * Вызовы прораммы:
 * ./app.exe c number file - заполняет file случайным числами в размере number штук
 * ./app.exe p file - выводит все числа file
 * ./app.exe s file - сортирует числа file
 * 
 * Выбранная сортировка: сортировка пузырьком
 * Тип чисел: int
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_functions.h"
#include "defines.h"

int main(int argc, char **argv)
{
    if (argc < MIN_ARGS || argc > MAX_ARGS)
        return WRONG_ARGS;

    int check;

    if (argc == 4 && !strcmp(argv[1], "c"))
    {
        size_t number;

        if (sscanf(argv[2], "%zu", &number) != EXPECTED_NUMBER)
            return WRONG_ARGS;

        fill_file(argv[3], number);
    }
    else if (argc == 3 && !strcmp(argv[1], "p"))
    {
        check = print_file(argv[2]);
        if (check != EXIT_SUCCESS)
            return check;
    }
    else if (argc == 3 && !strcmp(argv[1], "s"))
        sort_file(argv[2]);
    else
        return WRONG_ARGS;

    return EXIT_SUCCESS;
}