/*
 * Дьяченко Артём ИУ7-23Б
 * Задача №1
 * Найти и вывести на экран среднее арифметическое отрицательных элементов массива.
 */

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define ZERO_DIVISION 1

// Ввод массива
void get_array(int arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        scanf("%d", &arr[i]);
}

// Подсчёт среднего отрицательных чисел
double calc_mid_of_negative(int arr[], size_t n)
{
    double sum = 0;
    int count = 0;

    for (size_t i = 0; i < n; i++)
        if (arr[i] < 0)
        {
            sum += arr[i];
            count++;
        }

    if (!count)
        return ZERO_DIVISION;
    return sum / count;
}

int main(void)
{
    int n;
    printf("Введите кол-во элементов массива: ");
    scanf("%d", &n);

    #ifdef DEBUG
    printf("[DB]: n = %d\n", n);
    #endif

    int arr[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    get_array(arr, n);

    // Вывод массива
    #ifdef DEBUG
    printf("[DB]: arr = ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    #endif

    if (calc_mid_of_negative(arr, n) > 0)
    {
        printf("Ошибка: в массиве нет отрицательных чисел!\n");
        return EXIT_FAILURE;
    }

    printf("Среднее арифметическое отрицательных чисел массива: %f\n", \
           calc_mid_of_negative(arr, n));

    return EXIT_SUCCESS;
}
