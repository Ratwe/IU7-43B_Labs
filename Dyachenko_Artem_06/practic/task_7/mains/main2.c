#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NMAX 10000
#define M 1000

int arr[1000000];

int calc_value(int *arr, int n)
{
    long long count = 0;
    long long temp = 1;

    for (int i = 0; i < n; i++)
    {
        if (i > 0 && *(arr + i - 1) < 0)
            break;

        temp *= *(arr + i);
        count += temp;
    }

    return temp;
}

unsigned long long get_millitime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1e6 + tv.tv_usec;
}

int main(void)
{
    int arr[NMAX];

    for (int t = 0; t <= NMAX; t += 500)
    {
        int n = t;
        long long start_time, end_time;

        for (int i = 0; i < n; i++)
            arr[i] = rand();

        start_time = get_millitime();
        for (int i = 0; i < M; i++)
        {
            arr[i] = calc_value(arr, n);
        }
        end_time = get_millitime();

        double res = end_time - start_time;
        printf("%d:%f\n", n, res / M);
    }

    printf("\n");
    return EXIT_SUCCESS;
}
