/*
 * Дьяченко Артём ИУ7-23Б
 * Удалить из исходного массива все элементы, которые являются полными квадратами.
 * Ситуацию, когда массив после операции не изменился, ошибочной не считать.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define EPS 1e-5
#define NUM_OF_ARGS 1

#define ZERO_DIVISION 1
#define INVALID_INPUT 2
#define INVALID_SIZE 3
#define EMPTY_ARRAY 4


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
        int root = 1;
        for (; root * root <= arr[i]; root++)
            if (root * root == arr[i])
                break;

    	#ifdef DEBUG
    	printf("\nroot(%d) = %f\n", arr[i], root);
    	printf("int(root(%d)) = %d\n", arr[i], (int) root);
    	#endif

        // Если корень НЕ равен целому числу
        if (root * root > arr[i])
        {
            res[count] = arr[i];
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
    int count = calc_new_array(arr, res, n);

    if (count == 0)
        return EMPTY_ARRAY;

    print_array(res, count);

    return EXIT_SUCCESS;
}
