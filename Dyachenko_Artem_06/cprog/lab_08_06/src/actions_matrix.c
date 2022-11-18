#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "essential_matrix.h"
#include "defines.h"

void search_minimal(int **matrix, int m, int n, int *min_m, int *min_n)
{
    int min = matrix[0][0];
    *min_m = 0, *min_n = 0;

    for (int i = 0; i < m; i++)
    {
        int *p_str = matrix[i];

        for (int j = 0; j < n; j++)
            if (p_str[j] <= min)
            {
                min = p_str[j];
                *min_m = i;
                *min_n = j;
            }
    }
}

int delete_column(int **matrix, int m, int n, int min_n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = min_n; j < n - 1; j++)
            matrix[i][j] = matrix[i][j + 1];

        int *buff = (int *)realloc(matrix[i], (n - 1) * sizeof(int));

        // if (!buff)
        // {
        //     // free_matrix(matrix, m);
        //     return REALLOC_ERROR;
        // }

        matrix[i] = buff;
    }

    return EXIT_SUCCESS;
}

int delete_string(int **matrix, int m, int min_m)
{
    free(matrix[min_m]);

    for (int i = min_m; i < m - 1; i++)
        matrix[i] = matrix[i + 1];

    int **buff = (int **)realloc(matrix, (m - 1) * sizeof(int *));

    // if (!(*buff))
    // {
    //     // free_matrix(matrix, m - 1); // m - 1?
    //     return REALLOC_ERROR;
    // }

    matrix = buff;

    return EXIT_SUCCESS;
}

int square_down(int **matrix, int *m, int *n, int k)
{
    int min_m = 0, min_n = 0, error_code = 0;

    while (*m > k || *n > k)
    {
        // Нужно удалить столбцы
        if (k == (*m))
        {
            search_minimal(matrix, *m, *n, &min_m, &min_n);

            if ((error_code = delete_column(matrix, *m, *n, min_n)))
                return error_code;

            (*n)--;
        }
        else
        {
            search_minimal(matrix, *m, *n, &min_m, &min_n);

            if ((error_code = delete_string(matrix, *m, min_m)))
                return error_code;

            (*m)--;
        }
    }

    return EXIT_SUCCESS;
}

int square_up(int **matrix, int *m, int *n, int z)
{
    // Добавляем строки
    while ((*m) < z)
    {
        matrix = realloc(matrix, (*m + 1) * sizeof(int *));
        if (!matrix)
            return REALLOC_ERROR;

        matrix[*m] = malloc(*n * sizeof(int));
        if (!matrix[*m])
            return REALLOC_ERROR;

        for (int j = 0; j < *n; j++)
        {
            int comp = 1;  // ???
            for (int i = 0; i < *m; i++)
                comp *= matrix[i][j];

            int new = (int)floor(pow(comp, 1.0 / *m));

            matrix[*m][j] = new;
        }

        (*m)++;
    }

    // Добавляем столбцы
    while ((*n) < z)
    {
        for (int i = 0; i < *m; i++)
        {
            matrix[i] = realloc(matrix[i], (*n + 1) * sizeof(int));
            if (!matrix[i])
                return REALLOC_ERROR;

            int min = matrix[i][0];
            for (int j = 0; j < *n; j++)
                min = (matrix[i][j] < min) ? matrix[i][j] : min;

            matrix[i][*n] = min;
        }

        (*n)++;
    }

    return EXIT_SUCCESS;
}

// int multiply(int **am, int **bm, int **res, int z)
// {
//     res = allocate_matrix(z, z);
//     if (!res)
//         return ALLOCATE_MATRIX_ERR;
//
//     int *temp_row = malloc(z * sizeof(int));
//     if (!temp_row)
//         return ALLOCATE_MATRIX_ERR;
//
//     int sum;
//     for (int i = 0; i < z; i++)
//     {
//         for (int j = 0; j < z; j++)
//         {
//             sum = 0;
//             for (int k = 0; k < z; k++)
//                 sum += am[i][k] * bm[k][j];
//
//             temp_row[j] = sum;
//         }
//
//         for (int m = 0; m < z; m++)
//             res[i][m] = temp_row[m];
//     }
//
//     free(temp_row);
//
//     return EXIT_SUCCESS;
// }

int multiply(int **am, int **res, int z)
{
    int *temp_row = malloc(z * sizeof(int));
    if (!temp_row)
        return ALLOCATE_MATRIX_ERR;

    int sum;
    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < z; j++)
        {
            sum = 0;
            for (int k = 0; k < z; k++)
                sum += res[i][k] * am[k][j];

            temp_row[j] = sum;
        }

        for (int m = 0; m < z; m++)
            res[i][m] = temp_row[m];
    }

    free(temp_row);

    return EXIT_SUCCESS;
}

void one_matrix(int **am, int z)
{
    for (int i = 0; i < z; i++)
        for (int j = 0; j < z; j++)
        {
            if (i == j)
                am[i][j] = 1;
            else
                am[i][j] = 0;
        }
}

int multi_multiply(int **am, int **bm, int **res, int z, int r, int y)
{
    int error_code = EXIT_SUCCESS;

    // res = allocate_matrix(z, z);
    // if (!res)
    //     return ALLOCATE_MATRIX_ERR;

    // int **res_a = allocate_matrix(z, z);
    // if (!res_a)
    //     return ALLOCATE_MATRIX_ERR;
    //
    // int **res_b = allocate_matrix(z, z);
    // if (!res_b)
    //     return ALLOCATE_MATRIX_ERR;

    // for (int i = 0; i < z; i++)
    //     memcpy(res_a[i], am[i], z * sizeof(int));

    // if (r == 0)
    //     one_matrix(res_a, z);

    one_matrix(res, z);

    for (int i = 0; i < r; i++)
        if ((error_code = multiply(am, res, z)))
            return error_code;

    // print_matrix(res, z, z);

    // for (int i = 0; i < z; i++)
    //     memcpy(res_b[i], bm[i], z * sizeof(int));
    //
    // if (y == 0)
    //     one_matrix(res_b, z);


    for (int i = 0; i < y; i++)
        if ((error_code = multiply(bm, res, z)))
            return error_code;

    // print_matrix(res, z, z);

    // if ((error_code = multiply(res_a, res_b, z)))

    // free_matrix(res_a, z);
    // free_matrix(res_b, z);

    return EXIT_SUCCESS;
}
