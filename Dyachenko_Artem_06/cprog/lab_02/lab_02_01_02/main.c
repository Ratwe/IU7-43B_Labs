/*
 * Дьяченко Артём ИУ7-23Б
 * Задача №1
 * Найти и вывести на экран среднее арифметическое отрицательных элементов массива.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define EPS 1e-5

#define ZERO_DIVISION 1
#define NUM_OF_ARGS 1
#define INVALID_INPUT 2
#define INVALID_SIZE 3


// Ввод массива
int input_array(int *arr, size_t *n)
{
    printf("Введите размер массива: ");

    if (scanf("%zu", n) != NUM_OF_ARGS)
        return INVALID_INPUT;

    if (*n > 10 || *n <= 0)
        return INVALID_SIZE;

    printf("Введите элементы массива: ");
    for (size_t i = 0; i < *n; i++)
    {
        // Если ввели не число
        if (scanf("%d", &arr[i]) != NUM_OF_ARGS)
            return INVALID_INPUT;
    }

    return EXIT_SUCCESS;
}

int calc_mid_of_negative(int arr[], size_t n, double *res)
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

    *res = sum / count;

    return EXIT_SUCCESS;
}

int equal(double a, double b)
{
    return fabs(a - b) < EPS;
}

int main(void)
{
    // Ввод массива
    int arr[N];
    size_t n;
    double res = 0;

    int rc = input_array(arr, &n);
    if (rc)
        return rc;

    // Подсчёт среднего отрицательного
    rc = calc_mid_of_negative(arr, n, &res);
    if (rc)
        return rc;

    // Вывод результата
    if (equal(res, 0))
    {
        printf("Ошибка: в массиве нет отрицательных чисел!\n");
        return ZERO_DIVISION;
    }

    printf("Среднее арифметическое отрицательных чисел массива: %f\n", res);

    return EXIT_SUCCESS;
}
