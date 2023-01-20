#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define ERROR_LOG(str) fprintf(stderr, "\033[31m>> ERROR: %s\033[0m\n", str)
#else
#define ERROR_LOG(str) ((void)0)
#endif

#define EXPECTED_INPUT          1
#define MAX_STR_LEN             3

#define OUT_MODE                1
#define MUL_MODE                2
#define SQR_MODE                3
#define DIV_MODE                4

#define WRONG_MODE              101
#define WRONG_INPUT             102
#define ALLOCATE_ERROR          103
#define EMPTY_LIST              104
#define NO_OUT                  105
#define DIVISION_BY_ZERO        106

#endif // __DEFINES_H___
