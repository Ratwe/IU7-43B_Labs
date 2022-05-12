#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NMAX 10000
#define M 10000

void calc_value(int *arr, int n)
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
}

long long get_millitime(void)
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

        for (int i = 0; i < n; i++)
            arr[i] = i + 1;

        long long start_time = get_millitime();
        for (int i = 0; i < M; i++)
            calc_value(arr, n);
        long long end_time = get_millitime();

        double res = end_time - start_time;
        printf("%d:%f\n", n, res / M);
    }

    return EXIT_SUCCESS;
}
