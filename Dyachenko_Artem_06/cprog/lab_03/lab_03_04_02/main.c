/*
    Найти максимальное число, которое заканчивается на цифру 5
    и расположено под побочной диагональю.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 10
#define M 10

#define WRONG_SIZE 1
#define WRONG_ELEM 2
#define INPUT_SIZE_ERROR 3
#define INPUT_SUCCESS 0

// ввод матрицы
int input_squared_matrix(int arr[N][M], size_t *n, size_t *m)
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

int find_max_num_end_of_5_under(int arr[N][M], size_t n, size_t m)
{
    int res = INT_MIN;

    for (size_t i = 0; i < n; i++)
        for (size_t j = m - 1; j > m - 1 - i; j--)
            if (arr[i][j] > res && abs(arr[i][j]) % 10 == 5)
                res = arr[i][j];

    return res;
}


int main(void)
{
    int arr[N][M];
    size_t n = N, m = M;

    int rc = input_squared_matrix(arr, &n, &m);
    if (rc)
        return rc;

    int k = find_max_num_end_of_5_under(arr, n, m);

    if (k == INT_MIN)
        return EXIT_FAILURE;

    printf("%d", k);

    return EXIT_SUCCESS;
}
