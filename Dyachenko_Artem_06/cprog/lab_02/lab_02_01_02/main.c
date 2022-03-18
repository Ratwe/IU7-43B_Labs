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
/*
int get_array(int arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        int data = scanf("%d", &arr[i]);
        if (!data)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
*/

// Подсчёт среднего отрицательных чисел
/*
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
*/

int main(void)
{
    int n = 0;
    printf("Введите кол-во элементов массива: ");
    scanf("%d", &n);

    if (n > 10)
        return EXIT_FAILURE;

    #ifdef DEBUG
    printf("[DB]: n = %d\n", n);
    #endif

    int arr[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    // Ввод массива
    for (int i = 0; i < n; i++)
    {
        int data = scanf("%d", &arr[i]);
        if (!data)
            return EXIT_FAILURE;
    }

    // Вывод массива
    #ifdef DEBUG
    printf("[DB]: arr = ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    #endif

    // Подсчёт среднего отрицательного
    double sum = 0;
    int count = 0;

    for (int i = 0; i < n; i++)
        if (arr[i] < 0)
        {
            sum += arr[i];
            count++;
        }

    // Вывод результата
    if (!count)
    {
        printf("Ошибка: в массиве нет отрицательных чисел!\n");
        return ZERO_DIVISION;
    }

    double res = sum / count;

    printf("Среднее арифметическое отрицательных чисел массива: %f\n", res);

    return EXIT_SUCCESS;
}
