/*
Сортировка строк матрицы по сумме элементов в строке с кешированием сумм и без.
По желанию можно рассмотреть дополнительный вариант с размещением матрицы
по столбцам.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NMAX 1000
#define M 100

int glob_arr[NMAX];

unsigned long long get_millitime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000ULL + tv.tv_usec * 1ULL;
}

void set_random_vals(int arr[NMAX][NMAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand();
}

int bigger(int arr[NMAX][NMAX], size_t m, size_t a, size_t b)
{
    int count_a = 0, count_b = 0;

    for (size_t j = 0; j < m; j++)
    {
        count_a += arr[a][j];
        count_b += arr[b][j];
    }

    return count_a > count_b;
}

int change_lines(int arr[NMAX][NMAX], size_t m, size_t a, size_t b)
{
    int temp;

    for (size_t j = 0; j < m; j++)
    {
        temp = arr[a][j];
        arr[a][j] = arr[b][j];
        arr[b][j] = temp;
    }

    return temp;
}

// сортировка строк матрицы по возрастанию произведения их элементов
int sort_matrix(int arr[NMAX][NMAX], size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (bigger(arr, n, j, j + 1))
                return change_lines(arr, n, j, j + 1);
    return 0;
}

int main(void)
{
    int arr[NMAX][NMAX];
    long long start_time, end_time;

    for (int i = 1; i <= NMAX; i++)
    {
        set_random_vals(arr, i);

        start_time = get_millitime();
        for (int j = 0; j < M; j++)
        {
            glob_arr[i] = sort_matrix(arr, i);
        }
        end_time = get_millitime();

        double res = end_time - start_time;
        printf("%d:%f\n", i, res / M);
    }

    return EXIT_SUCCESS;
}
