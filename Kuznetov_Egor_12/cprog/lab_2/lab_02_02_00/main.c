/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Create and print new array with grate then middle value of input
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
 * @param[in] a - Input array
 * @param[in] n - Array length
 * @return Middle value
 * @brief Find middle value of input array
 */
double find_middle_value(const int a[], size_t n)
{
    double sum = 0;
    
    for (size_t i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum / n;
}

/**
 * @param[in] a - Input array
 * @param[in] n - Array length
 * @param[out] new_a - New array
 * @return Length of new array
 * @brief Fill new array and return length
 */
size_t fill_new_array(const int a[], size_t n, int new_a[])
{
    size_t new_len = 0;
    double val = find_middle_value(a, n);

    for (size_t i = 0; i < n; i++)
    {
        if (a[i] > val)
        {
            new_a[new_len++] = a[i];
        }
    }
    return new_len;
}

int main(void)
{
    size_t n, new_n;
    int a[N], new_a[N];

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

    if (!(new_n = fill_new_array(a, n, new_a)))
    {
        printf("All values less or equal middle value\n");
        return CALCULATION_ERROR;
    }

    printf("New array: ");
    print_array(new_a, new_n);
    return EXIT_SUCCESS;
}

