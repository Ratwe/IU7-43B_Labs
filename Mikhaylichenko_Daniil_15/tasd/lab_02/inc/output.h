#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "../inc/defines.h"
#include "../inc/struct.h"

#include "../inc/scan.h"

void print_table(table_t table);
void print_keys(table_t table);
void print_table_by_keys(table_t table);
int search_cars(table_t table);

#endif // __OUTPUT_H__
