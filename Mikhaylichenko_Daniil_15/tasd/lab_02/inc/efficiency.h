#ifndef __EFFICIENCY_H__
#define __EFFICIENCY_H__

#include <time.h>

#include "../inc/defines.h"
#include "../inc/struct.h"

#include "../inc/files.h"
#include "../inc/table.h"
#include "../inc/sort.h"

typedef struct
{
    size_t bubble_table_time;
    size_t bubble_keys_time;
    size_t qsort_table_time;
    size_t qsort_keys_time;
} results_t;

void run_efficiency(void);

#endif // __EFFICIENCY_H__
