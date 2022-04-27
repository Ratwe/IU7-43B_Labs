/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Find sum odd number from input array
 */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 10
#define CORRECT 0
#define INCORRECT_ARRAY 1
#define INCORRECT_LENGTH 2
#define CALCULATION_ERROR 3

/**
 * @param[out] a - Result array
 * @param[in] n - Array length
 * @return Reading success code
 * @brief Read 'n' values from stream and write to array 'a'
 */
int get_array(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (scanf("%d", &a[i]) < 1)
        {
            return INCORRECT_ARRAY;
        }
    }
    return CORRECT;
}

/**
 * @param[in] a - Value array
 * @param[in] n - Array length
 * @param[out] sum - Sum odd number
 * @return Count odd number
 * @brief Find sum odd number from array
 */
int sum_odd(const int a[], size_t n, int *sum)
{
    int count = 0;
    *sum = 0;

    for (size_t i = 0; i < n; i++)
    {
        if (a[i] % 2 == 0)
        {
            *sum += a[i];
            count++;
        }
    }
    return count;
}

int main(void)
{
    size_t n;
    int a[N];
    int sum;

    printf("Enter array length: ");
    if (scanf("%zu", &n) < 1 || n == 0 || n > N)
    {
        printf("Incorrect array length\n");
        return INCORRECT_LENGTH;
    }
    
    printf("Enter array: ");
    if (get_array(a, n))
    {
        printf("Incorrect value\n");
        return INCORRECT_ARRAY;
    }
    
    if (!sum_odd(a, n, &sum))
    {
        printf("No odd num in array\n");
        return CALCULATION_ERROR;
    }

    printf("Sum odd element: %d", sum);
    return EXIT_SUCCESS;
}

