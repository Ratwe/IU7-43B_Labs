#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EXPECTED_INPUT 2

// проверка ввода
int input(int *a, int *n)
{
    int rc = scanf("%d %d", *&a, *&n);

    if (rc != EXPECTED_INPUT || *n <= 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int main(void)
{
    int a, n;
    if (input(&a, &n))
       return EXIT_FAILURE;

    printf("%lf\n", pow(a, n));
    return EXIT_SUCCESS;
}
