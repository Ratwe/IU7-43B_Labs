/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Print a^n when 'a' and 'n' is input value
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @param[in] a Base
 * @param[in] n Grade
 * @return a^n
 * @brief Calculating a^n 
 */
int64_t pow_i(int a, int n)
{
    int64_t res;
    res = a;
    for (int i = 1; i < n; i++)
    {
        res *= a;
    }
    return res;
}

int main(void)
{
    int a, n;

    printf("Enter a: ");
    if (scanf("%d", &a) < 1)
    {
        printf("Wrong value a\n");
        return EXIT_FAILURE;
    }
    printf("Enter n: ");
    if ((scanf("%d", &n) < 1) || n <= 0)
    {
        printf("Wrong value n\n");
        return EXIT_FAILURE;
    }

    printf("Result: %ld", pow_i(a, n));
    return EXIT_SUCCESS;
}

