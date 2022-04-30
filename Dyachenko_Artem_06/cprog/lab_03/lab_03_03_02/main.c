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

void print_matrix(int arr[N][M], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}

int bigger(int arr[N][M], size_t m, size_t a, size_t b)
{
    int count_a = 1, count_b = 1;

    for (size_t j = 0; j < m; j++)
    {
        #ifdef DEBUG
        printf("arr_a[%zu][%zu] = %d\n", a, j, arr[a][j]);
        printf("arr_b[%zu][%zu] = %d\n\n", b, j, arr[b][j]);
        #endif

        count_a *= arr[a][j];
        count_b *= arr[b][j];
    }

    #ifdef DEBUG
    printf("%d and %d\n", count_a, count_b);
    #endif

    return count_a > count_b;
}

void change_lines(int arr[N][M], size_t m, size_t a, size_t b)
{
    for (size_t j = 0; j < m; j++)
    {
        int temp = arr[a][j];
        arr[a][j] = arr[b][j];
        arr[b][j] = temp;
    }
}

// сортировка строк матрицы по возрастанию произведения их элементов
void sort_matrix(int arr[N][M], size_t n, size_t m)
{
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (bigger(arr, m, j, j + 1))
                change_lines(arr, m, j, j + 1);
}

int main(void)
{
    int arr[N][M];
    size_t n = N, m = M;

    int rc = matrix_input(arr, &n, &m);
    if (rc)
        return rc;

    #ifdef DEBUG
    printf("Initial matrix: \n");
    print_matrix(arr, n, m);
    #endif

    sort_matrix(arr, n, m);

    print_matrix(arr, n, m);

    return EXIT_SUCCESS;
}
