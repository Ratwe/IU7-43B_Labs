/*
 * Дьяченко Артём ИУ7-23Б
 * Упорядочить массив по возрастанию с помощью сортировки пузырьком
 * и вывести на экран.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define INPUT_ELEM 1

#define INPUT_OVERFLOW 100
#define EMPTY_ARRAY 1
#define INPUT_SUCCESS 0

// Вывода массива
void print_array(int *arr, size_t n)
{
    // printf("Array:");
    for (size_t i = 0; i < n; i++)
        printf(" %d", arr[i]);
    printf("\n");
}

// Ввод массива
int input_array(int *arr, size_t *n)
{
    size_t i = 0;

    printf("Вводите значения массива: ");

    while (scanf("%d", &arr[i]) == INPUT_ELEM)
    {
        i++;
        if (i > N)
        {
            *n = N;
            return INPUT_OVERFLOW;
        }
    }

    *n = i;
    return INPUT_SUCCESS;
}

// Пузырьковая сортировка
void bubble_sort(int *arr, size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main(void)
{
    // Ввод массива
    int arr[N + 1];
    size_t n;
    int flag_overflow = 0;

    if (input_array(arr, &n) == INPUT_OVERFLOW)
        flag_overflow = 1;

    if (n == 0)
        return EMPTY_ARRAY;

    #ifdef DEBUG
    printf("[DB] n = %zu\n", n);
    print_array(arr, n);
    #endif

    bubble_sort(arr, n);

    print_array(arr, n);

    if (flag_overflow)
        return INPUT_OVERFLOW;

    return EXIT_SUCCESS;
}
