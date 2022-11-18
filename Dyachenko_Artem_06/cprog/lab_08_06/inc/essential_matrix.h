#ifndef __ESSENTIAL_MATRIX__H__
#define __ESSENTIAL_MATRIX__H__

void free_matrix(int **matrix, int m);

int **allocate_matrix(int m, int n);

int read_matrix(int **matrix, int m, int n);

void print_matrix(int **matrix, int m, int n);

#endif
