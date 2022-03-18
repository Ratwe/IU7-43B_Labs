/*
 * Дьяченко Артём ИУ7-23Б
 * Удалить из исходного массива все элементы, которые являются полными квадратами.
 * Ситуацию, когда массив после операции не изменился, ошибочной не считать.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define INVALID_INPUT 1
#define EMPTY_ARRAY 2
#define EPS 1e-4

// Сравнение вещественного с целым
int equal(double a, int b)
{
    #ifdef DEBUG
    if (fabs(a - (double) b) < EPS)
        printf("[DB]: %f equal %d\n", a, b);
    #endif
    return fabs(a - (double) b) < EPS;
}

// Считаем результирующий массив
int calc_new_array(int *arr, size_t n)
{
    int count = 0;

    for (size_t i = 0; i < n; i++)
    {
        double root = sqrt(arr[i]);

        // Если корень равен целому числу
        if (!equal(root, (int) root))
        {
            arr[count] = arr[i];
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
        for (size_t i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
        #endif

    // Подсчёт и вывод результата
    int count = calc_new_array(res_arr, n);


    printf("Результат: ");
    for (int i = 0; i < count; i++)
        printf("%d ", res_arr[i]);
    printf("\n");

    return EXIT_SUCCESS;
}
