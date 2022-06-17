#include <stdio.h>
#include <time.h>
#include "file_functions.h"
#include "positions.h"
#include "defines.h"

void fill_file(char file_name[], size_t num_counter)
{
    FILE *file = fopen(file_name, "wb");

    srand(time(NULL));

    for (size_t i = 0; i < num_counter; i++)
    {
        int num = rand() % 200 - 100;

        fwrite(&num, sizeof(num), 1, file);
    }

    fclose(file);
}

int print_file(char file_name[])
{
    size_t num_counter = 0;

    FILE *file = fopen(file_name, "rb");

    for (int num; READ_NUM; num_counter++)
        printf("%d\n", num);

    fclose(file);

    if (num_counter == 0)
        return EMPTY_FILE;

    return NUMBER_WERE_PRINTED;
}

void sort_file(char file_name[])
{
    FILE *file = fopen(file_name, "rb+");

    fseek(file, 0, SEEK_END);

    size_t len = ftell(file) / sizeof(int);

    fseek(file, 0, SEEK_SET);

    for (size_t i = 0; i < len - 1; i++)
        for (size_t j = 0; j < len - i - 1; j++)
        {
            int first_num = get_number_by_pos(file, j);
            int second_num = get_number_by_pos(file, j + 1);

            if (first_num > second_num)
            {
                put_number_by_pos(file, j + 1, first_num);
                put_number_by_pos(file, j, second_num);
            }
        }

    fclose(file);
}