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

#define READ_MODE               "r"
#define WRITE_MODE              "w"
#define APPEND_MODE             "a"

#define EXPECTED_INPUT          1
#define MIN_ARGS                3
#define MAX_ARGS                3

#define WRONG_ARGS              101
#define FILE_OPEN_ERROR         102
#define FILE_CLOSE_ERROR        103
#define FILE_READING_ERROR      104
#define WRONG_DATA              105
#define ALLOCATE_ERROR          106
#define EMPTY_LIST              107

#endif // __DEFINES_H___
