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
#define EPS 1e-7
#define NUM_OF_ARGS 1

// Ввод массива
int input_array(int *arr, size_t n)
{
    printf("Введите элементы массива: ");
    for (size_t i = 0; i < n; i++)
    {
        // Если ввели не число
        if (scanf("%d", &arr[i]) != NUM_OF_ARGS)
            return INVALID_INPUT;
    }

    return EXIT_SUCCESS;
}

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
        double root = sqrt(abs(arr[i]));
	
	#ifdef DEBUG
	printf("\nroot(%d) = %f\n", arr[i], root);
	printf("int(root(%d)) = %d\n", arr[i], (int) root);
	#endif

        // Если корень НЕ равен целому числу
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
    size_t n = 11;
    printf("Введите размер массива: ");
    scanf("%zu", &n);

    if (n > 10 || n <= 0)
        return EXIT_FAILURE;

    // Ввод массива
    int arr[N];
    
    if (input_array(arr, n))
        return EXIT_FAILURE;
    
    // Вывод массива
    #ifdef DEBUG
    printf("[DB]: arr = ");
    for (size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    #endif

    // Подсчёт и вывод результата
    unsigned int count = calc_new_array(arr, n);
    
    if (count == 0)
        return EMPTY_ARRAY;

    printf("Результат: ");
    for (size_t i = 0; i < count; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return EXIT_SUCCESS;
}
