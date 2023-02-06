#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "matrix.h"

void search_minimal(matrix_t matrix, int *min_row, int *min_column)
{
    *min_row = 0, *min_column = 0;

    for (int j = 0; j < matrix.column; j++)
        for (int i = 0; i < matrix.row; i++)
            if (matrix.matrix[i][j] <= matrix.matrix[*min_row][*min_column])
            {
                *min_row = i;
                *min_column = j;
            }
}

int search_minimal_in_row(int *arr, int n)
{
    int min = arr[0];

    for (int i = 0; i < n; i++)
        if (arr[i] < min)
            min = arr[i];

    return min;
}

int delete_minimal_column(matrix_t *matrix)
{
    int min_row, min_column;
    int *buff;

    search_minimal(*matrix, &min_row, &min_column);

    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = min_column; j < matrix->column - 1; j++)
            matrix->matrix[i][j] = matrix->matrix[i][j + 1];

        buff = realloc(matrix->matrix[i], (matrix->column - 1) * sizeof(int));

        if (buff == NULL)
            return REALLOC_ERROR;

        matrix->matrix[i] = buff;
    }

    matrix->column--;

    return EXIT_SUCCESS;
}

int delete_minimal_string(matrix_t *matrix)
{
    int min_row, min_column;
    search_minimal(*matrix, &min_row, &min_column);

    free(matrix->matrix[min_row]);

    for (int i = min_row; i < matrix->row - 1; i++)
        matrix->matrix[i] = matrix->matrix[i + 1];

    int **buff = realloc(matrix->matrix, (matrix->row - 1) * sizeof(int *));

    if (buff == NULL)
        free_matrix(matrix);

    matrix->matrix = buff;
    matrix->row--;

    return EXIT_SUCCESS;
}


int square_down(matrix_t *matrix)
{
    int error_code = 0;

    if (matrix->row > matrix->column)
    {
        while (matrix->row > matrix->column)
            if ((error_code = delete_minimal_string(matrix)))
            {
                free_matrix(matrix);
                return error_code;
            }
    }
    else if (matrix->column > matrix->row)
    {
        while (matrix->column > matrix->row)
            if ((error_code = delete_minimal_column(matrix)))
            {
                free_matrix(matrix);
                return error_code;
            }
    }

    return EXIT_SUCCESS;
}

void fill_matrix_rows(matrix_t *matrix, matrix_t *matrix_to)
{
    for (int j = 0; j < matrix->column; j++)
    {
        double comp = 1;

        for (int i = 0; i < matrix_to->row; i++)
        {
            if (matrix->row < i + 1)
                matrix->matrix[i][j] = (int)floor(pow(comp, 1.0 / i));
            comp *= matrix->matrix[i][j];
        }
    }

    matrix->row = matrix_to->row;
}

void fill_matrix_columns(matrix_t *matrix, matrix_t *matrix_to)
{
    for (int j = matrix->column; j < matrix_to->column; j++)
    {
        for (int i = 0; i < matrix->row; i++)
            matrix->matrix[i][j] = search_minimal_in_row(matrix->matrix[i], matrix->column);
    }

    matrix->column = matrix_to->column;
}

int square_up(matrix_t *matrix_a, matrix_t *matrix_b)
{
    int error_code = 0;

    // Добавляем строки
    if (matrix_a->row < matrix_b->row)
    {
        if ((error_code = reallocate_matrix(matrix_a, matrix_b)))
            return error_code;

        fill_matrix_rows(matrix_a, matrix_b);
        fill_matrix_columns(matrix_a, matrix_b);
    }
    else if (matrix_b->row < matrix_a->row)
    {
        if ((error_code = reallocate_matrix(matrix_b, matrix_a)))
            return error_code;

        fill_matrix_rows(matrix_b, matrix_a);
        fill_matrix_columns(matrix_b, matrix_a);
    }

    return EXIT_SUCCESS;
}

int multiply(matrix_t *matrix, matrix_t *matrix_res)
{
    int *temp_row = malloc(matrix->row * sizeof(int));
    if (temp_row == NULL)
        return ALLOCATE_MATRIX_ERR;

    int sum;
    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = 0; j < matrix->column; j++)
        {
            sum = 0;
            for (int k = 0; k < matrix->row; k++)
                sum += matrix_res->matrix[i][k] * matrix->matrix[k][j];

            temp_row[j] = sum;
        }

        for (int m = 0; m < matrix->row; m++)
            matrix_res->matrix[i][m] = temp_row[m];
    }

    free(temp_row);

    return EXIT_SUCCESS;
}

void identity_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->column; j++)
            matrix->matrix[i][j] = i == j;
}

int multi_multiply(matrix_t *matrix_a, matrix_t *matrix_b, matrix_t *matrix_res)
{
    int error_code = EXIT_SUCCESS;

    matrix_res->row = matrix_a->row;
    matrix_res->column = matrix_a->column;

    if ((error_code = allocate_matrix(matrix_res)))
        return error_code;

    int r, y, rc;

    printf("Введите r: ");
    if ((rc = scanf("%d", &r) != 1))
    {
        free_matrix(matrix_res);
        return SCANF_ERR;
    }

    if (r < 0)
    {
        free_matrix(matrix_res);
        return WRONG_POW_ERR;
    }

    printf("Введите y: ");
    if ((rc = scanf("%d", &y) != 1))
    {
        free_matrix(matrix_res);
        return SCANF_ERR;
    }

    if (y < 0)
    {
        free_matrix(matrix_res);
        return WRONG_POW_ERR;
    }

    identity_matrix(matrix_res);

    for (int i = 0; i < r; i++)
        if ((error_code = multiply(matrix_a, matrix_res)))
        {
            free_matrix(matrix_res);
            return error_code;
        }

    for (int i = 0; i < y; i++)
        if ((error_code = multiply(matrix_b, matrix_res)))
        {
            free_matrix(matrix_res);
            return error_code;
        }

    return EXIT_SUCCESS;
}
