#ifndef __POSITIONS_H__
#define __POSITIONS_H__

#include <stdio.h>
#include <stdlib.h>

int get_number_by_pos(FILE *file, size_t pos);
void put_number_by_pos(FILE *file, size_t pos, int num);

#endif // __POSITIONS_H__