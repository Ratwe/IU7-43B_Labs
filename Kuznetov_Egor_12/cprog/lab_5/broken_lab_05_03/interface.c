#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "defines.h"
#include "file.h"

int get_number_diff(int a, int b)
{
    char buff_a[BUFF_SIZE];
    char buff_b[BUFF_SIZE];

    sprintf(buff_a, "%d", a);
    sprintf(buff_b, "%d", b);

    return strlen(buff_a) - strlen(buff_b);
}

size_t get_count_number(int value)
{
    char buff[BUFF_SIZE];
    
    sprintf(buff, "%d", value);

    return strlen(buff);
}

int print(char *filename)
{
    int error_code = EXIT_SUCCESS;
    FILE *file; 
    int value;
    size_t count = 0;

    if (!(file = fopen(filename, "r")))
        error_code = CANT_OPEN_FILE;
    else
    {
        while (fscanf(file, "%d", &value) == COUNT_INPUT_VALUES)
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
    int diff;
    int pos_i, pos_j;
    int a_i, a_j;
    char diff_str[BUFF_SIZE];

    if (!(file = fopen(filename, "r+")))
        error_code = CANT_OPEN_FILE;
    if (!error_code && !(length = get_length(file)))
        error_code = EMPTY_FILE;
    if (!error_code)
    {
        for (size_t i = 0; i < length - 1; i++)
            for (size_t j = i + 1; j < length; j++)
            {          
                pos_i = get_pos_by_index(file, i);
                pos_j = get_pos_by_index(file, j);
                
                a_i = get_number_by_pos(file, pos_i);
                a_j = get_number_by_pos(file, pos_j);
                
                diff = get_number_diff(a_i, a_j);
                get_pos_diff(file, pos_i + get_count_number(a_i), pos_j - diff, diff_str);

                if (a_i > a_j)
                {
                    put_number_by_pos(file, pos_i, a_j);
                    put_pos_diff(file, pos_i + get_count_number(a_j), diff_str);
                    put_number_by_pos(file, pos_j + diff, a_i);
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
    FILE *file; 

    if (!(file = fopen(filename, "w")))
        error_code = CANT_OPEN_FILE;
    else
        for (size_t i = 0; i < count; i++)
            fprintf(file, "%d\n", rand() % 2000);
    
    fclose(file);

    return error_code;
}
