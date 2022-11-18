#ifndef __FILE__H__
#define __FILE__H__

#include <stdio.h>

size_t get_length(FILE *file);
int get_number_by_pos(FILE *file, int pos);
void put_number_by_pos(FILE *file, int pos, int number);

#endif // #ifndef __FILE__H__
