#ifndef __FILES_H__
#define __FILES_H__

#include "../inc/defines.h"

int file_open(const FILE **const file, const char *const fname, const char *const mode);
int file_close(FILE **const file);

#endif // __FILES_H__
