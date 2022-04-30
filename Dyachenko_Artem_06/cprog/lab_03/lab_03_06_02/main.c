#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10

#define WRONG_SIZE 1
#define INPUT_SIZE_ERROR 3

int input_sizes(size_t *n, size_t *m)
{
    if (scanf("%zu %zu", n, m) != 2)
        return INPUT_SIZE_ERROR;

    if (*n <= 0 || *n > N || *m <= 0 || *m > M)
        return WRONG_SIZE;

    return EXIT_SUCCESS;
}

void create_matrix(int arr[N][M], int n, int m)
{
    int go_up = 1;
    int count = 1;

    for (int j = m - 1; j >= 0; j--)
    {
        if (go_up)
        {
            for (int i = n - 1; i >= 0; i--)
                arr[i][j] = count++;
            go_up = 0;
        }
        else
        {
            for (int i = 0; i < n; i++)
                arr[i][j] = count++;
            go_up = 1;
        }
    }
}

void print_matrix(int arr[N][M], size_t n, size_t m)
{
    #ifdef DEBUG
    printf("Матрица: \n");
    #endif

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    printf("\n");
}

int main(void)
{
    size_t n = N, m = M;

    int rc = input_sizes(&n, &m);
    if (rc)
        return rc;

    int arr[N][M];
    create_matrix(arr, n, m);

    print_matrix(arr, n, m);

    return EXIT_SUCCESS;
}
