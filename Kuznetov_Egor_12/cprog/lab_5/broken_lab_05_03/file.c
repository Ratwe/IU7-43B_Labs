#include <ctype.h>
#include <string.h>
#include "defines.h"
#include "file.h"

size_t get_length(FILE *file) 
{
    int value;
    size_t size = 0;
    fseek(file, 0, SEEK_SET);

    while (fscanf(file, "%d", &value) == COUNT_INPUT_VALUES)
        size++;

    return size;
}

int get_pos_by_index(FILE *file, size_t index)
{
    int pos;
    int value;

    fseek(file, 0, SEEK_SET);
    for (size_t i = 0; i < index && fscanf(file, "%d", &value); i++);
    pos = ftell(file);

    while(isspace(fgetc(file)))
        pos++;
    
    return pos;
}

void get_pos_diff(FILE *file, int start_pos, int end_pos, char *dest)
{
    size_t i;

    fseek(file, start_pos, SEEK_SET);

    for (i = 0; start_pos <= end_pos; i++, start_pos++)
        dest[i] = fgetc(file);

    dest[i] = '\0';
}

void put_pos_diff(FILE *file, int pos, const char *diff)
{
    fseek(file, pos, SEEK_SET);
    fprintf(file, "%s", diff);
}

int get_number_by_pos(FILE *file, int pos)
{
    int value;

    fseek(file, pos, SEEK_SET);
    fscanf(file, "%d", &value);

    return value;
}

void put_number_by_pos(FILE *file, int pos, int number)
{
    fseek(file, pos, SEEK_SET);
    fprintf(file, "%d", number);
}
