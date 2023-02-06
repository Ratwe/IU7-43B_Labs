/*
Найти наибольшее число подряд идущих элементов последовательности,
которые равны друг другу;
*/

#include <stdio.h>
#include "process.h"

#include "defines.h"

int main(void)
{
    int count = 0;
    int error_code = process(stdin, &count);

    if (error_code == EXIT_SUCCESS)
        printf("Result: %d\n", count);

    return error_code;
}
