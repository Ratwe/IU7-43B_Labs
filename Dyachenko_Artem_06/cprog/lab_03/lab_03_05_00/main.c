#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10

#define WRONG_SIZE 1
#define WRONG_ELEM 2
#define INPUT_SIZE_ERROR 3
#define INPUT_SUCCESS 0

#define IS_PRIME 1
#define IS_NOT_PRIME 0

#define NO_PRIME_NUMS 2

// ввод матрицы
int input_matrix(int arr[N][M], size_t *n, size_t *m)
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

void print_array(int arr[N * M], size_t n)
{
    printf("Массив: \n");
    for (size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
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

int is_prime(int x)
{
    if (x < 2)
        return IS_NOT_PRIME;

    for (int i = 2; i * i <= abs(x); i++)
        if (x % i == 0)
            return IS_NOT_PRIME;

    return IS_PRIME;
}

int put_primes(int prime_arr[N * M], int arr[N][M], size_t n, size_t m)
{
    int count = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_prime(arr[i][j]))
            {
                prime_arr[count] = arr[i][j];
                count++;
            }

    return count;
}

void revers_array(int arr[N * M], int k)
{
    for (int i = 0; i < k / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[k - 1 - i];
        arr[k - 1 - i] = temp;
    }
}

void put_back_in_matrix(int prime_arr[N * M], int arr[N][M], size_t n, size_t m)
{
    int count = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_prime(arr[i][j]))
                arr[i][j] = prime_arr[count++];
}

int main(void)
{
    int arr[N][M];
    size_t n = N, m = M;

    int rc = input_matrix(arr, &n, &m);
    if (rc)
        return rc;

    int prime_arr[N * M];
    int k = put_primes(prime_arr, arr, n, m);

    if (k == 0)
        return NO_PRIME_NUMS;

    #ifdef DEBUG
    printf("\n");
    print_matrix(arr, n, m);
    print_array(prime_arr, k);
    #endif

    revers_array(prime_arr, k);

    #ifdef DEBUG
    print_array(prime_arr, k);
    #endif

    put_back_in_matrix(prime_arr, arr, n, m);

    print_matrix(arr, n, m);

    return EXIT_SUCCESS;
}
