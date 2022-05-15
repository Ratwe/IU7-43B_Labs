/*
Сортировка строк матрицы по сумме элементов в строке с кешированием сумм и без.
По желанию можно рассмотреть дополнительный вариант с размещением матрицы
по столбцам.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NMAX 100
#define M 100

long long glob_arr[NMAX + 1];
long long sum[NMAX];

unsigned long long get_millitime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000ULL + tv.tv_usec * 1ULL;
}

void set_random_vals(int arr[NMAX][NMAX], size_t n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            arr[i][j] = rand() % 100;
}

void clear_sum()
{
    for (size_t i = 0; i < NMAX; i++)
        sum[i] = 0;
}

void print_matrix(int arr[NMAX][NMAX], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}

int change_lines(int arr[NMAX][NMAX], size_t m, size_t a, size_t b)
{
    int temp = 0;

    for (size_t j = 0; j < m; j++)
    {
        temp = arr[a][j];
        arr[a][j] = arr[b][j];
        arr[b][j] = temp;

        temp = sum[a];
        sum[a] = sum[b];
        sum[b] = temp;
    }

    return temp;
}

// сортировка строк матрицы по возрастанию суммы их элементов
int sort_matrix(int arr[NMAX][NMAX], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            sum[i] += arr[i][j];

    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (sum[j] > sum[j + 1])
                change_lines(arr, m, j, j + 1);

    return 0;
}

int main(void)
{
    int arr[NMAX][NMAX];

    for (size_t i = 1; i <= NMAX; i++)
    {
        long long start_time, end_time;
        set_random_vals(arr, i);
        clear_sum();

        start_time = get_millitime();
        for (size_t j = 0; j < M; j++)
        {
            glob_arr[i] = sort_matrix(arr, i, i);
        }
        end_time = get_millitime();

        double res = end_time - start_time;

        //print_matrix(arr, i, i);

        printf("%ld:%f\n", i, res / M);
    }

    return EXIT_SUCCESS;
}
