/**
 * @file
 * @author Kuztetsov Egor IU7-23B
 * @brief Enter array and print sorted by bubble sort
 */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 10
#define EXIT_OVERFLOW 100
#define CORRECT 0
#define INCORRECT_ARRAY 1
#define INCORRECT_LENGTH 2

/**
 * @param[in] a - Array to print
 * @param[in] n - Array length
 * @brief Print array to console
 */
void print_array(const int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
/**
 * @param[out] a - Array to sort
 * @param[in] n - Length
 * @brief In plase sork array by bubble sort
 */
void bubble_sort(int a[], size_t n)
{
    int temp;

    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int main(void)
{
    int a[N];
    size_t n;
    int temp;

    printf("Enter array: ");
    for (n = 0; (n < N) && (scanf("%d", &a[n]) == 1); n++);
    if (n == 0)
    {
        printf("Array is empty\n");
        return INCORRECT_LENGTH;
    }

    bubble_sort(a, n);

    printf("Sorted array: ");
    print_array(a, n);
    return scanf("%d", &temp) != 1 ? EXIT_SUCCESS : EXIT_OVERFLOW;
}

