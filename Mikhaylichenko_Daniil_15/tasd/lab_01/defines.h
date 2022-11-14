#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MANTISSA_LEN            30
#define EXP_LEN                 5
#define MAX_STR_LEN             MANTISSA_LEN + EXP_LEN + 2
#define MAX_EXP                 99999

#define IS_POSITIVE             1
#define IS_NEGATIVE             -1

#define WRONG_NUM               101
#define TOO_LONG_STR            102
#define EMPTY_STRING            103
#define DIVISION_BY_ZERO        104
#define ARRAY_ALLOCATE_ERROR    105
#define EXPONENT_OVERFLOW       106

#ifdef DEBUG
#define ERROR_LOG(str) fprintf(stderr, "\033[31m>> ERROR: %s\033[0m\n", str)
#else
#define ERROR_LOG(str) ((void)0)
#endif

typedef struct
{
    char sign;
    uint8_t mantissa[MANTISSA_LEN * 2];
    int exp;
    size_t str_len;
} my_double; 

#endif // __DEFINES_H__
