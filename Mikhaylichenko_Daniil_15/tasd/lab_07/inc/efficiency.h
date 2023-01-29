#ifndef __EFFICIENCY_H__
#define __EFFICIENCY_H__

#include <time.h>

#include "../inc/defines.h"
#include "../inc/tree.h"
#include "../inc/bst.h"
#include "../inc/avl.h"
#include "../inc/array.h"
#include "../inc/hash.h"

#define ITERS                       100
#define NUMBER_OF_FILES             5

#define SMALL_FILE_NAME             "./data/small.txt"
#define MIDDLE_FILE_NAME            "./data/middle.txt"
#define BIG_FILE_NAME               "./data/big.txt"
#define SORTED_FILE_NAME            "./data/sorted.txt"
#define REVERSE_SORTED_FILE_NAME    "./data/reverse.txt"

#define GET_TIME(start, end)        (end - start) / (CLOCKS_PER_SEC / 1000000)

typedef struct results
{
    size_t bst_searching[NUMBER_OF_FILES];
    size_t avl_searching[NUMBER_OF_FILES];
    size_t file_searching[NUMBER_OF_FILES];
    size_t htable_opened_searching[NUMBER_OF_FILES];
    size_t htable_closed_searching[NUMBER_OF_FILES];
    size_t htable_opened_restruct_searching[NUMBER_OF_FILES];
    size_t htable_closed_restruct_searching[NUMBER_OF_FILES];
    size_t bst_compares[NUMBER_OF_FILES];
    size_t avl_compares[NUMBER_OF_FILES];
    size_t file_compares[NUMBER_OF_FILES];
    size_t htable_opened_compares[NUMBER_OF_FILES];
    size_t htable_closed_compares[NUMBER_OF_FILES];
    size_t htable_opened_restruct_compares[NUMBER_OF_FILES];
    size_t htable_closed_restruct_compares[NUMBER_OF_FILES];
    size_t bst_size[NUMBER_OF_FILES];
    size_t avl_size[NUMBER_OF_FILES];
    size_t file_size[NUMBER_OF_FILES];
    size_t htable_opened_size[NUMBER_OF_FILES];
    size_t htable_closed_size[NUMBER_OF_FILES];
    size_t htable_opened_restruct_size[NUMBER_OF_FILES];
    size_t htable_closed_restruct_size[NUMBER_OF_FILES];
} results_t;

void run_efficiency(void);

#endif //__EFFICIENCY_H__
