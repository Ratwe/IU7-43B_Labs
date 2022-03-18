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
    unsigned int n = 11;
    printf("Введите размер массива: ");
    scanf("%u", &n);
    if (n > 10)
        return EXIT_FAILURE;

    // Ввод массива
    int arr[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int res_arr[N];
    for (size_t i = 0; i < n; i++)
    {
        int num = scanf("%d", &arr[i]);
        res_arr[i] = arr[i];
        if (!num)
            return INVALID_INPUT;
    }

    // Вывод массива
        #ifdef DEBUG
        printf("[DB]: arr = ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
        #endif

    // Подсчёт и вывод результата
    int count = calc_new_array(res_arr, n);
    if (!count)
        return EMPTY_ARRAY;

    printf("Результат: ");
    for (int i = 0; i < count; i++)
        printf("%d ", res_arr[i]);
    printf("\n");

    return EXIT_SUCCESS;
}
