#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "matrix.h"

void free_matrix(matrix_t *matrix)
{
    if (matrix->matrix != NULL)
    {
        for (int i = 0; i < matrix->row; i++)
            free(matrix->matrix[i]);  // Освобождение памяти строк

        free(matrix->matrix);  // Освобождение памяти массивов указателей
        matrix->matrix = NULL;
    }
}

int allocate_matrix(matrix_t *matrix)
{
    int m = matrix->row;
    int n = matrix->column;

    matrix->matrix = calloc(m, sizeof(*matrix->matrix));  // Массив указателей на строки матрицы
    if (matrix->matrix == NULL)
        return ALLOCATE_MATRIX_ERR;

    for (int i = 0; i < m; i++)
    {
        matrix->matrix[i] = malloc(n * sizeof(**matrix->matrix));
        if (matrix->matrix[i] == NULL)
        {
            free_matrix(matrix);
            return ALLOCATE_MATRIX_ERR;
        }
    }

    return EXIT_SUCCESS;
}

int reallocate_matrix(matrix_t *matrix, matrix_t *matrix_to)
{
    matrix_t new_matrix = { .matrix = NULL, .row = matrix_to->row, .column = matrix_to->column };

    int error_code = EXIT_SUCCESS;

    if ((error_code = allocate_matrix(&new_matrix)))
        return error_code;

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->column; j++)
            new_matrix.matrix[i][j] = matrix->matrix[i][j];

    free_matrix(matrix);

    matrix->matrix = new_matrix.matrix;

    return EXIT_SUCCESS;
}

int read_matrix(matrix_t *matrix)
{
    int rc, error_code = 0;

    printf("Введите размерность матрицы: ");
    if ((rc = scanf("%d %d", &matrix->row, &matrix->column) != RC))
        return SCANF_ERR;

    if (matrix->row < 1 || matrix->column < 1)
        return MATRIX_SIZE_ERR;

    if ((error_code = allocate_matrix(matrix)))
        return error_code;

    int m = matrix->row;
    int n = matrix->column;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            int rc = scanf("%d", &matrix->matrix[i][j]);
            if (rc != 1)
            {
                free_matrix(matrix);
                return READ_MATRIX_ERR;
            }
        }

    return EXIT_SUCCESS;
}

void print_matrix(matrix_t matrix)
{
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.column; j++)
            printf("%d ", matrix.matrix[i][j]);

        printf("\n");
    }
}
