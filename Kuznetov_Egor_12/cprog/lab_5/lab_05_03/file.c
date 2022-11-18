#include <ctype.h>
#include <string.h>
#include "file.h"

#define FIELD_LENGTH        sizeof(int)
#define COUNT_INPUT_VALUES  1

size_t get_length(FILE *file) 
{
    fseek(file, 0, SEEK_END);

    return ftell(file) / FIELD_LENGTH;
}

int get_number_by_pos(FILE *file, int pos)
{
    int value;

    fseek(file, pos * sizeof(value), SEEK_SET);
    fread(&value, sizeof(value), COUNT_INPUT_VALUES, file);

    return value;
}

void put_number_by_pos(FILE *file, int pos, int number)
{
    fseek(file, pos * sizeof(number), SEEK_SET);
    fwrite(&number, sizeof(number), COUNT_INPUT_VALUES, file);
}
