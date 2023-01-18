#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>

#ifdef DEBUG
#define ERROR_LOG(str) fprintf(stderr, "\033[31m>> ERROR: %s\033[0m\n", str)
#else
#define ERROR_LOG(str) ((void)0)
#endif

#define SHORT                   'h'
#define INT                     'd'
#define CHAR                    'c'
#define STR                     's'
#define OCT                     'o'

#define DEC_RADIX               10
#define OCT_RADIX               8

#define STR_LEN                 20

#endif // __DEFINES_H___
