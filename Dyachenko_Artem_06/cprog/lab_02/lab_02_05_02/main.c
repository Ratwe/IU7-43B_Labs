/*
* Дьяченко Артём ИУ7-23Б
* Вычислить значение элементов
* 𝐴[0] + 𝐴[0] · 𝐴[1] + 𝐴[0] · 𝐴[1] · 𝐴[2] + · · · A[m]
* где m - индекс первого отрицательного элемента или n - 1
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define INPUT_ELEM 1

#define INPUT_SUCCESS 0
#define INPUT_FAILED 1
#define SIZE_ERROR 2

int input_array(int *pa, int *pb)
{
    for (int *pcur = pa; pcur < pb; pcur++)
        if (scanf("%d", pcur) != INPUT_ELEM)
            return INPUT_FAILED;

    return INPUT_SUCCESS;
}

int calc_value(int *pa, int *pb)
{
    int count = 0;
    int temp = 1;

    for (int *pcur = pa; pcur < pb && *(pcur - 1) > 0; pcur++)
    {
        temp *= *pcur;
        count += temp;
    }

    return count;
}

int main(void)
{
    // Ввод массива
    int arr[N];
    int n;

    printf("Введите размерность массива: ");
    if (scanf("%d", &n) != INPUT_ELEM)
        return INPUT_FAILED;
    if (n <= 0 || n > N)
        return SIZE_ERROR;

    int *pa = arr; // Pointer to the first elem
    int *pb = arr + n; // Pointer after the last elem

    printf("Введите массив: \n");
    if (input_array(pa, pb))
        return INPUT_FAILED;

    int res = calc_value(pa, pb);
    printf("Результат: %d\n", res);

    return EXIT_SUCCESS;
}
