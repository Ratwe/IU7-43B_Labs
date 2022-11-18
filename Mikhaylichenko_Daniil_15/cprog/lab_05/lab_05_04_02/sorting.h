#ifndef __SORTING_H__
#define __SORTING_H__

#include <stdio.h>

size_t get_len(FILE *file);
int copy_file(char input_name[], char output_name[]);
void sort_products(FILE *file);

#endif // __SORTING_H__