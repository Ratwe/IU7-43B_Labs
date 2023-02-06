#include <stdio.h>

#include "defines.h"

int get_size(FILE *f, int *size)
{
    if (fseek(f, 0L, SEEK_END))
        return SEEK_ERROR;

    long pos = ftell(f);

    if (fseek(f, 0L, SEEK_SET))
        return SEEK_ERROR;

    if (pos % SIZE || pos < (long) SIZE)
        return FILE_SIZE_ERROR;

    *size = pos / SIZE;

    return EXIT_SUCCESS;
}

int put_number_by_pos(FILE *f, int num, int pos)
{
    int n;
    if (get_size(f, &n) || pos >= n)
        return EXIT_FAILURE;

    if (fseek(f, SIZE * pos, SEEK_SET))
        return SEEK_ERROR;

    if (fwrite(&num, SIZE, 1, f) != WRITE_ELEM_COUNT)
        return WRITE_ERROR;

    rewind(f);

    return EXIT_SUCCESS;
}

int get_number_by_pos(FILE *f, int pos, int *num)
{
    int n;
    if (get_size(f, &n) || pos >= n)
        return EXIT_FAILURE;

    if (fseek(f, SIZE * pos, SEEK_SET))
        return SEEK_ERROR;

    if (fread(num, SIZE, 1, f) != READ_ELEM_COUNT)
        return READ_ERROR;

    rewind(f);

    return EXIT_SUCCESS;
}

int print_file(char *filename)
{
    FILE *f = fopen(filename, "rb");

    if (!f)
        return OPEN_FILE_ERROR;

    int now;
    int n;

    if (get_size(f, &n))
        return EXIT_FAILURE;

    while (fread(&now, SIZE, 1, f) == READ_ELEM_COUNT)
        printf("%d ", now);

    if (fclose(f))
        return FILE_CLOSE_ERROR;

    return EXIT_SUCCESS;
}

int fill_file(char *filename, int n)
{
    FILE *f = fopen(filename, "wb");

    if (!f)
        return OPEN_FILE_ERROR;

    for (int i = 0; i < n; i++)
    {
        int num = rand() % 100;
        if (fwrite(&num, SIZE, 1, f) != WRITE_ELEM_COUNT)
            return WRITE_ERROR;
    }

    if (fclose(f))
        return FILE_CLOSE_ERROR;

    return EXIT_SUCCESS;
}

int sort_file_data(char *filename)
{
    FILE *f = fopen(filename, "rb+");

    int n;
    int rc;

    if ((rc = get_size(f, &n)))
        return rc;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
        {
            int a, b;
            get_number_by_pos(f, j, &a);
            get_number_by_pos(f, j + 1, &b);

            if (a > b)
            {
                if ((rc = put_number_by_pos(f, b, j)))
                    return rc;

                if ((rc = put_number_by_pos(f, a, j + 1)))
                    return rc;
            }
        }

    if (fclose(f))
        return FILE_CLOSE_ERROR;

    return EXIT_SUCCESS;
}
