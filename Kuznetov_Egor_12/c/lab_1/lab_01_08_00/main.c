/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Cyclic shift input value 'a' to 'n' bytes
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @param[in] source Source to printing
 * @param[in] n Sount bits to print
 * @brief Recursive printing source an binary
 */
void print_in_2(const uint32_t source, int n)
{
    if (n == 0)
    {
        return;
    }
    print_in_2(source >> 1, n - 1);
    printf("%u", source & 1);
}

/**
 * @param[in] source Source to shifting
 * @paran[in] n Count bits to shift
 * @return Shifted source
 * @brief Cycle shifting source value by 'n' bits
 */
uint32_t cyclic_shift(uint32_t source, int n)
{
    for (int i = 0; i < n; i++)
    {	    
        source = ((source & 1) << 31) | (source >> 1);
    }
    return source;
}

int main(void)
{
    uint32_t a;
    int n;
    
    printf("Enter a: ");
    if (scanf("%u", &a) < 1)
    {
        printf("Error: uncorrect value a\n");
        return EXIT_FAILURE;
    }
    printf("Enter n: ");
    if (scanf("%d", &n) < 1 || n < 0)
    {
        printf("Error: uncorrect value n\n");
        return EXIT_FAILURE;
    }

    n %= 32;  
    a = cyclic_shift(a, n);

    printf("Result: ");
    print_in_2(a, 32);
    printf("\n");
    return EXIT_SUCCESS;
}

