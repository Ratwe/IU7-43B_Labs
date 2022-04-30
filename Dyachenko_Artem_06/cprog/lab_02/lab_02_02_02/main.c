/*
 * Дьяченко Артём ИУ7-23Б
 * Сформировать и вывести на экран новый массив, в который скопировать элементы
 * исходного массива, которые начинаются и заканчиваются на одну и ту же цифру.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define INVALID_INPUT 1
#define EMPTY_ARRAY 2
#define NUM_OF_ARGS 1

// Ввод массива
int input_array(int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        int num = scanf("%d", &arr[i]);
        if (num != NUM_OF_ARGS)
            return INVALID_INPUT;
    }
    return EXIT_SUCCESS;
}

// Считаем результирующий массив
int calc_new_array(int *arr, size_t n)
{
    int count = 0;

    for (size_t i = 0; i < n; i++)
    {
        int first = 0, last = 0;
        int temp = arr[i];
        last = arr[i] % 10;

        while (arr[i])
        {
            first = arr[i] % 10;
            arr[i] /= 10;
        }

        if (first == last)
        {
            arr[count] = temp;
            count++;
        }
    }

    return count;
}

int main(void)
{
    // Ввод размера массива
    size_t n = 11;
    printf("Введите размер массива: ");
    scanf("%zu", &n);
    if (n > 10 || n <= 0)
        return EXIT_FAILURE;

    // Ввод массива
    int arr[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    if (input_array(arr, n))
        return EXIT_FAILURE;

    // Вывод массива
    #ifdef DEBUG
    printf("[DB]: arr = ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    #endif

    // Подсчёт и вывод результата
    int count = calc_new_array(arr, n);
    if (!count)
        return EMPTY_ARRAY;

    printf("Результат: ");
    for (int i = 0; i < count; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return EXIT_SUCCESS;
}
