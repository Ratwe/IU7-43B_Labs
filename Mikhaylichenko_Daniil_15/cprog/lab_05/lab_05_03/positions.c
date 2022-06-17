#include "defines.h"
#include "positions.h"

int get_number_by_pos(FILE *file, size_t pos)
{
    int num;

    fseek(file, pos * sizeof(num), SEEK_SET);
    fread(&num, sizeof(num), EXPECTED_NUMBER, file);

    return num;
}

void put_number_by_pos(FILE *file, size_t pos, int num)
{
    fseek(file, pos * sizeof(num), SEEK_SET);
    fwrite(&num, sizeof(num), EXPECTED_NUMBER, file);
}