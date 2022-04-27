/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Find sum of multiply while positive number
 */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 10
#define CORRECT 0
#define INCORRECT_ARRAY 1
#define INCORRECT_LENGTH 2

/**
 * @param[out] a - Result array
 * @param[in] n - Array length
 * @return Reading success code
 * @brief Read 'n' values from stream and write to array 'a'
 */
int get_array(int *a, size_t n)
{
    for (int *pa = a; pa < a + n; pa++)
    {
        if (scanf("%d", pa) < 1)
        {
            return INCORRECT_ARRAY;
        }
    }
    return CORRECT;
}

/**
 * @param[in] p_start - Pointer to array start
 * @param[in] p_end - Pointer to array end
 * @return Sum of multiply positive number
 * @brief Calc sum of multiply
 */
int calc_value(const int *p_start, const int *p_end)
{
    int result = 0;
    int value = 1;
  
    while (p_start != p_end)
    {
        value *= *p_start;
        result += value;
        if (*p_start <= 0)
        {
            break;
        }
        p_start++;
    }
    return result;
}

int main(void)
{
    int a[N];
    size_t n;

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

    printf("Result value: %d\n", calc_value(a, a + n));
    return EXIT_SUCCESS;
}

