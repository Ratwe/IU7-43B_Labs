#ifndef __FILES_H__
#define __FILES_H__

#include "../inc/defines.h"

#define READ_MODE       "r"
#define WRITE_MODE      "w"
#define APPEND_MODE     "a"

typedef struct
{
    char *first_fin;
    char *second_fin;
    char *fout;
} files_t;

int file_open(const FILE **const file, const char *const fname, const char *const mode);
int file_close(FILE **const file);

#endif // __FILES_H__
