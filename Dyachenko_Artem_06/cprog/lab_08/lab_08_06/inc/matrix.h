#ifndef __MATRIX__H__
#define __MATRIX__H__

typedef struct
{
    int **matrix;
    int row;
    int column;
} matrix_t;

void search_minimal(matrix_t matrix, int *min_row, int *min_column);

int square_down(matrix_t *matrix);

int matrix_convert_to_square(matrix_t *matrix);

int delete_row_by_index(matrix_t *matrix, int index_row);

int delete_column_by_index(matrix_t *matrix, int index_column);

int matrix_convert_to_same_size(matrix_t *matrix_a, matrix_t *matrix_b);

int square_up(matrix_t *matrix_a, matrix_t *matrix_b);

int delete_minimal_string(matrix_t *matrix);

int delete_minimal_column(matrix_t *matrix);

void fill_matrix_rows(matrix_t *matrix, matrix_t *matrix_to);

void fill_matrix_columns(matrix_t *matrix, matrix_t *matrix_to);

void one_matrix(matrix_t *matrix);

int multi_multiply(matrix_t *matrix_a, matrix_t *matrix_b, matrix_t *matrix_res);

int multiply(matrix_t *matrix, matrix_t *matrix_res);

void free_matrix(matrix_t *matrix);

int allocate_matrix(matrix_t *matrix);

int read_matrix(matrix_t *matrix);

void print_matrix(matrix_t matrix);

int reallocate_matrix(matrix_t *matrix, matrix_t *matrix_to);

#endif
