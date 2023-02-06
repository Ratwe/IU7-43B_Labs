#ifndef __MY_SNPRINTF__H__
#define __MY_SNPRINTF__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_STR_LEN 1000

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...);

#endif
