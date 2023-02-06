#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10

#define WRONG_SIZE 1
#define WRONG_ELEM 2
#define INPUT_SIZE_ERROR 3
#define INPUT_SUCCESS 0
#define NO_ALTERNATION -1
#define YES_ALTERNATION 0

// ввод матрицы
int matrix_input(int arr[N][M], size_t *n, size_t *m)
{
    if (!scanf("%zu", n))
        return INPUT_SIZE_ERROR;

    if (!scanf("%zu", m))
        return INPUT_SIZE_ERROR;

    if (*n <= 0 || *m <= 0 || *n > N || *m > M)
        return WRONG_SIZE;

    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
            if (scanf("%d", &arr[i][j]) != 1)
                return WRONG_ELEM;

    return INPUT_SUCCESS;
}

// изменение значения k-го элемента
void change_value(int arr[N][M], size_t n, size_t m, int k, int value)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++, k--)
            if (k == 0)
            {
                arr[i][j] = value;
                return;
            }
}

// вывод матрицы
void print_matrix(int arr[N][M], size_t n, size_t m)
{
    printf("Матрица: \n");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    printf("\n");
}

// вывод массива
void print_array(int arr[N * M], size_t n)
{
    printf("Массив: \n");
    for (size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

// проверка на чередование
int check_alternation(int arr[N][M], size_t n, size_t j)
{
    if (n == 1)
        return NO_ALTERNATION;

    for (size_t i = 1; i < n; i++)
        if ((arr[i - 1][j] >= 0 && arr[i][j] >= 0) || (arr[i - 1][j] < 0 && arr[i][j] < 0))
            return NO_ALTERNATION;

    return YES_ALTERNATION;
}

int main(void)
{
    size_t n = N, m = M;
    int arr[N][M];

    int rc = matrix_input(arr, &n, &m);
    if (rc)
        return rc;

    for (size_t j = 0; j < m; j++)
    {
        int k = check_alternation(arr, n, j);
        change_value(arr, n, m, j, k > -1 ? 1 : 0);
    }

    print_array(arr[0], m);

    return EXIT_SUCCESS;
}
