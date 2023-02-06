/*
Найти число, наиболее близкое по значению к среднему значению всех чисел;
*/

#include <stdio.h>

#include "defines.h"
#include "process.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return EXIT_FAILURE;

    FILE *f = fopen(argv[1], "r");
    double res = 0;

    int error_code = process(f, &res);

    if (!error_code)
        printf("Result: %lf\n", res);

    return error_code;
}
