#ifndef __DEFINES__H__
#define __DEFINES__H__

#include <stdio.h>

#define ARGC_MIN 3
#define ARGC_MAX 4

#define EXIT_SUCCESS 0
#define ARGC_ERROR 101
#define OPEN_FILE_ERROR 102
#define CALLOC_ERROR 103
#define EMPTY_ARRAY_ERROR 104
#define DATA_RANGE_ERROR 105
#define NULL_POINTER_ERROR 106
#define ARGV_ERROR 107

#define SWAP(x, y, t) do { t SWAP = x; x = y; y = SWAP; } while (0)

#endif

#ifdef DEBUG
#define LOG_DEBUG(...) { printf(__VA_ARGS__); }
#define LOG_ARR_DEBUG(PTR_START, PTR_END) { \
    do { \
        for (int *p = PTR_START; p < PTR_END; p++) \
            printf("%d ", *p); \
        printf("\n"); \
    } while(0); \
}
#else
#define LOG_DEBUG(...) {}
#define LOG_ARR_DEBUG(...) {}
#endif
