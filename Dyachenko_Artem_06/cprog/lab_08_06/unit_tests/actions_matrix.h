#ifndef __ACTIONS_MATRIX__H__
#define __ACTIONS_MATRIX__H__

void search_minimal(int **matrix, int m, int n, int *min_m, int *min_n);

int** square_down(int** matrix, int *m, int *n, int k);

int** square_up(int** matrix, int *m, int *n, int z);

int** delete_string(int **matrix, int m, int n, int min_m);

int** delete_column(int **matrix, int m, int n, int min_n);

int** multi_multiply(int **A, int **B, int z, int r, int y);

int** multiply(int** A, int** B, int z);

#endif
