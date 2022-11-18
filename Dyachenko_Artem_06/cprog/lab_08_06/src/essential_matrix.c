#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

void free_matrix(int **matrix, int m)
{
    if (matrix)
    {
        for (int i = 0; i < m; i++)
            free(matrix[i]);  // Освобождение памяти строк
        free(matrix);  // Освобождение памяти массивов указателей
    }
}

int **allocate_matrix(int m, int n)
{
    int **buff;

    buff = calloc(m, sizeof(int *));  // Массив указателей на строки матрицы
    if (!buff)
        return NULL;

    int **data = buff;

    for (int i = 0; i < m; i++)
    {
        data[i] = malloc(n * sizeof(int));
        if (!data[i])
        {
            free_matrix(data, i);
            return NULL;
        }
    }

    return data;
}

int read_matrix(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        int *p_str = matrix[i];  // Указатель на i-ю строку

        for (int j = 0; j < n; j++)
        {
            int rc = scanf("%d", &p_str[j]);
            if (rc != 1)
                return READ_MATRIX_ERR;
        }
    }

    return EXIT_SUCCESS;
}

void print_matrix(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        int *p_str = matrix[i];

        for (int j = 0; j < n; j++)
            printf("%d ", p_str[j]);

        printf("\n");
    }
}
