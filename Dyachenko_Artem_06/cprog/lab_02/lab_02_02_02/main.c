/*
 * Дьяченко Артём ИУ7-23Б
 * Сформировать и вывести на экран новый массив, в который скопировать элементы
 * исходного массива, которые начинаются и заканчиваются на одну и ту же цифру.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define NUM_OF_ARGS 1

#define ZERO_DIVISION 1
#define INVALID_INPUT 2
#define INVALID_SIZE 3
#define EMPTY_ARRAY 4

// Вывод массива
void print_array(int *arr, size_t n)
{
    printf("Array:");
    for (size_t i = 0; i < n; i++)
        printf(" %d", arr[i]);
    printf("\n");
}

// Ввод массива
int input_array(int *arr, size_t *n)
{
    printf("Введите размер массива: ");

    if (scanf("%zu", n) != NUM_OF_ARGS)
        return INVALID_INPUT;

    if (*n > N || *n <= 0)
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

// Считаем результирующий массив
int calc_new_array(int *arr, int *res, size_t n)
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
            res[count] = temp;
            count++;
        }
    }

    return count;
}

int main(void)
{
    // Ввод массива
    int arr[N], res[N];
    size_t n;

    int rc = input_array(arr, &n);
    if (rc)
        return rc;

    // Подсчёт и вывод результата
    int num_of_elems = calc_new_array(arr, res, n);
    if (!num_of_elems)
        return EMPTY_ARRAY;

    print_array(res, num_of_elems);

    return EXIT_SUCCESS;
}
