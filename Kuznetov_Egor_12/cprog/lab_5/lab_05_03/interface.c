#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "defines.h"
#include "file.h"

int print(char *filename)
{
    int error_code = EXIT_SUCCESS;
    FILE *file; 
    int value;
    size_t count = 0;

    if (!(file = fopen(filename, "rb")))
        error_code = CANT_OPEN_FILE;
    else
    {
        while (fread(&value, sizeof(value), COUNT_INPUT_VALUES, file) == COUNT_INPUT_VALUES)
        {
            printf("%d ", value);
            count++;
        }

        if (count)
            printf("\n");
        else
            error_code = EMPTY_FILE;
    }
    
    fclose(file);

    return error_code;
}

int sort(char *filename)
{
    int error_code = EXIT_SUCCESS;
    FILE *file;
    size_t length;
    int a_i, a_j;

    if (!(file = fopen(filename, "rb+")))
        error_code = CANT_OPEN_FILE;
    if (!error_code && !(length = get_length(file)))
        error_code = EMPTY_FILE;
    if (!error_code)
    {
        for (size_t i = 0; i < length - 1; i++)
            for (size_t j = i + 1; j < length; j++)
            {          
                a_i = get_number_by_pos(file, i);
                a_j = get_number_by_pos(file, j);

                if (a_i > a_j)
                {
                    put_number_by_pos(file, i, a_j);
                    put_number_by_pos(file, j, a_i);
                }
            }
    }

    fclose(file);

    return error_code;
}

int create(char *filename, size_t count)
{
    srand(time(NULL));

    int error_code = EXIT_SUCCESS;
    int value;
    FILE *file; 

    if (!(file = fopen(filename, "wb")))
        error_code = CANT_OPEN_FILE;
    else
        for (size_t i = 0; i < count; i++)
        {
            value = rand() % 2000;
            fwrite(&value, sizeof(value), COUNT_INPUT_VALUES, file);
        }
    
    fclose(file);

    return error_code;
}
