#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define N 32
#define EXPECTED_INPUT 2

// проверка ввода
int input(unsigned int *a, int *n)
{
    if (scanf("%u%d", &*a, &*n) < EXPECTED_INPUT || *n < 0)
        return EXIT_FAILURE;
        
    return EXIT_SUCCESS;
}

// вывод ответа
void print_bits(char num[], int array_size, int n)
{
    printf("Result: ");

    for (int i = n; i < array_size; i++)
        printf("%d", num[i]);

    for (int i = 0; i < n; i++)
        printf("%d", num[i]);

    printf("\n");
}

// рассчёт ответа
void calc_bits(unsigned int a, int n)
{
    char num[N] = { 0 };
    int i;
    int count = 0; // сколько бит в числе
    
    while (a >= pow(2, count))
        count++;

    #ifdef DEBUG
    printf("[DB]: %d bits\n", count);
    #endif

    // заполняем незначащими нулями
    for (i = 0; i < N - count; i++)
        num[i] = 0;

    // пишем само число
    while (count)
    {
        if (a >= pow(2, count - 1))
        {
            num[i] = 1;
            a -= (int)pow(2, count - 1);
        }
        else
        {
            num[i] = 0;
        }
        count--;
        i++;
    }

    int array_size = N;
    // sizeof (num) / sizeof (char);

    #ifdef DEBUG
    printf("[DB]: num = ");
    for (int i = 0; i < N; i++)
        printf("%d", num[i]);

    printf("\n[DB]: array_size: %d\n", array_size);
    #endif

    print_bits(num, array_size, n);
}



int main(void)
{
    // Проверка на поддержку 32-битных переменных
    if (ULLONG_MAX < 4294967295)
    {
        printf("Ваша система не может обработать эту программу!");
        return EXIT_FAILURE;
    }

    unsigned int a;
    int n;

    if (input(&a, &n))
    {
        printf("Error: некорректные введённые значения!\n");
        return EXIT_FAILURE;
    }

    n %= N;

    #ifdef DEBUG
    printf("[DB]: a = %u, n = %d\n", a, n);
    #endif


    calc_bits(a, n);

    return EXIT_SUCCESS;
}
