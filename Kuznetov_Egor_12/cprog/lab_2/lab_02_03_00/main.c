/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Remove palindroms and print input array
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
 * @param[in] number - Value
 * @return Value is palindrome
 * @brief Check value is palindrom
 */
int is_palindrome(int number)
{
    int temp = number;
    int reversed = 0;

    while (temp)
    {
        reversed *= 10;
        reversed += temp % 10;
        temp /= 10;
    }
    return number == reversed;   
}

/**
 * @param[out] a - Array
 * @param[in] pos - Position to remove
 * @param[in] n - Array length
 * @brief Remove value in 'pos' from array
 */
void remove_value(int a[], size_t pos, size_t n)
{
    for (size_t i = pos; i < n - 1; i++)
    {
        a[i] = a[i + 1];
    }
}

/**
 * @param[out] a - Edited array
 * @param[in] n - Length array
 * @return New array length
 * @brief Remove all palindrom from array and return new length
 */
size_t edit_array(int a[], size_t n)
{
    for (size_t i = 0; i < n;)
    {
        if (is_palindrome(a[i]))
        {
            remove_value(a, i, n--);
        }
        else
        {
            i++;
        }
    }
    return n;
}

int main(void)
{
    size_t n;
    int a[N];
    
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
    
    if (!(n = edit_array(a, n)))
    {
        printf("Edited array is empty\n");
        return CALCULATION_ERROR;
    }

    printf("Edited array: ");
    print_array(a, n);
    return EXIT_SUCCESS;
}

