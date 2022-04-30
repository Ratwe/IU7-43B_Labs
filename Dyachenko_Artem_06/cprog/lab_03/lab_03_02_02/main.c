#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10
#define WRONG_SIZE 1
#define WRONG_ELEM 2
#define INPUT_SIZE_ERROR 3
#define INPUT_SUCCESS 0
#define YES_TWO_NUMS 0
#define NO_TWO_NUMS 1
#define RADIX 10

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

int odd_sum_of_num(int x)
{
    int count = 0;

    while (x)
    {
        count += x % RADIX;
        x /= RADIX;
    }

    return count % 2;
}

int check_two_elems(int arr[M], size_t m)
{
    int count = 0;

    for (size_t j = 0; j < m; j++)
        if (odd_sum_of_num(arr[j]))
        {
            count++;
            if (count == 2)
                return YES_TWO_NUMS;
        }

    return NO_TWO_NUMS;
}

void calc_res(int arr[N][M], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        if (!check_two_elems(arr[i], m))
        {
            for (size_t j = 0; j < m; j++)
                printf("-1 ");
            printf("\n");
        }

        for (size_t j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int arr[N][M];
    size_t n = 0, m = 0;

    int rc = matrix_input(arr, &n, &m);
    if (rc)
        return rc;

    calc_res(arr, n, m);

    return EXIT_SUCCESS;
}
