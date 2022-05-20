#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#ifndef MAX_SIZE
#error size constant not defined
#endif

unsigned long long get_microseconds_now(void);
void fill_array(int arr[]);
int find_max(int arr[]);

int global_arr[1000];

int main(void)
{
        int arr[MAX_SIZE];

        unsigned long long start, stop;

        srand(time(NULL));
        
        fill_array(arr);

        start = get_microseconds_now();

        for (size_t i = 0; i < 1000; i++)
                global_arr[i] = find_max(arr);

        stop = get_microseconds_now();

        double time = (stop - start);
        
        printf("%lf\n", time / 1000);
        
        return EXIT_SUCCESS;
}

void fill_array(int arr[])
{
        for (size_t i = 0; i < MAX_SIZE; i++)
                *(arr + i) = rand() % 200 - 100;
}

unsigned long long get_microseconds_now(void)
{
        struct timeval val;

        gettimeofday(&val, NULL);

        return val.tv_sec * 1000000ULL + val.tv_usec;
}

int find_max(int arr[])
{
        int max = *arr + *(arr + MAX_SIZE - 1);
        
        for (size_t i = 1; i < MAX_SIZE; i++)
        {
                int temp = *(arr + i) + *(arr + MAX_SIZE - i - 1);
                
                if (temp > max)
                        max = temp;
        }

        return max;
}
