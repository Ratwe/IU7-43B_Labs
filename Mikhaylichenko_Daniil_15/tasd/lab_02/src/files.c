#include "../inc/files.h"

int file_open(const FILE **const file, const char *const fname, const char *const mode)
{
    if ((*file = fopen(fname, mode)) == NULL)
    {
        ERROR_LOG("FILE OPEN ERROR");
        return FILE_OPEN_ERROR;
    }

    return EXIT_SUCCESS;
}

int file_close(FILE **const file)
{
    if (fclose(*file) == EOF)
    {
        ERROR_LOG("FILE CLOSE ERROR");
        return FILE_CLOSE_ERROR;
    }

    return EXIT_SUCCESS;
}
