/*
* Дьяченко Артём ИУ7-23Б
* Вычислить значение элементов
* 𝐴[0] + 𝐴[0] · 𝐴[1] + 𝐴[0] · 𝐴[1] · 𝐴[2] + · · · A[m]
* где m - индекс первого отрицательного элемента или n - 1
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define INPUT_OVERFLOW 100
#define INPUT_SUCCESS 0
#define INPUT_FAILED 1
#define INPUT_ELEM 1
#define SIZE_ERROR 2

int input_array(int *pa, int *pb)
{
    for (int *i = pa; i < pb; i++)
        if (scanf("%d", i) != INPUT_ELEM)
            return INPUT_FAILED;

    return INPUT_SUCCESS;
}

void calc_value(int *pa, int *pb)
{
    int count = 0;
    int temp = 1;

    for (int *i = pa; i < pb && *(i - 1) > 0; i++)
    {
        temp *= *i;
        count += temp;
    }

    printf("Результат: %d\n", count);
}

int main(void)
{
    // Ввод массива
    int arr[N];
    size_t n;

    printf("Введите размерность массива: ");
    if (scanf("%zu", &n) != INPUT_ELEM || n <= 0 || n > N)
        return SIZE_ERROR;

    int *pa = arr; // Pointer to the first elem
    int *pb = arr + n; // Pointer after the last elem

    printf("Введите массив: \n");
    if (input_array(pa, pb))
        return EXIT_FAILURE;

    calc_value(pa, pb);

    return EXIT_SUCCESS;
}
