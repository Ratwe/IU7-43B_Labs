#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#ifndef MAX_SIZE
#error size constant not defined
#endif

unsigned long long get_microseconds_now(void);
void fill_array(int *pbeg, int *pend);
int find_max(int *pbeg, int *pend);

int global_arr[1000];

int main(void)
{
        int arr[MAX_SIZE];

        unsigned long long start, stop;
                
        int *pbeg = arr;
        int *pend = pbeg + MAX_SIZE;
        
        fill_array(pbeg, pend);

        start = get_microseconds_now();

        for (size_t i = 0; i < 1000; i++)
                global_arr[i] = find_max(pbeg, pend);

        stop = get_microseconds_now();

        double time = (stop - start);

        printf("%lf\n", time / 1000);
        
        return EXIT_SUCCESS;
}

unsigned long long get_microseconds_now(void)
{
        struct timeval val;

        gettimeofday(&val, NULL);

        return val.tv_sec * 1000000ULL + val.tv_usec;
}

void fill_array(int *pbeg, int *pend)
{
        do
        {                
                *pbeg = rand() % 200 - 100;
                pbeg++;
        }
        while (pbeg != pend);
}

int find_max(int *pbeg, int *pend)
{
        int max = *pbeg + *(pend - 1);
        
        do
        {
                int temp = *pbeg + *(pend - 1);
                
                if (temp > max)
                        max = temp;
                
                pbeg++;
                pend--;
        }
        while (pbeg <= pend);

        return max;
}
