#ifndef __FILE__H__
#define __FILE__H__

#include <stdio.h>

void get_pos_diff(FILE *file, int start_pos, int end_pos, char *dest);
void put_pos_diff(FILE *file, int pos, const char *diff);
int get_pos_by_index(FILE *file, size_t index);
size_t get_length(FILE *file);
int get_number_by_pos(FILE *file, int pos);
void put_number_by_pos(FILE *file, int pos, int number);

#endif // #ifndef __FILE__H__
