#ifndef __NUMCHECKER_H__
#define __NUMCHECKER_H__

#include "defines.h"
#include <stdbool.h>

bool is_integer(char *str, size_t max_len);
int count_exp(char *str);
bool check_number(char *str);

#endif // __NUMCHECKER_H__
