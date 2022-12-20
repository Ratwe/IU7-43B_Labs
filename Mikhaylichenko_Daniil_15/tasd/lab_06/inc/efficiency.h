#ifndef __EFFICIENCY_H__
#define __EFFICIENCY_H__

#include <time.h>

#include "../inc/defines.h"

#define ITERS                        100

#define SMALL_FILE_NAME             "./data/small.txt"
#define MIDDLE_FILE_NAME            "./data/middle.txt"
#define BIG_FILE_NAME               "./data/big.txt"
#define SORTED_FILE_NAME            "./data/sorted.txt"
#define REVERSE_SORTED_FILE_NAME    "./data/reverse.txt"

typedef struct results
{
    size_t tree_sorting[ITERS];
    size_t file_sorting[ITERS];
    size_t tree_searching[ITERS];
    size_t file_searching[ITERS];
} results_t;

void run_efficiency(void);

#endif //__EFFICIENCY_H__
