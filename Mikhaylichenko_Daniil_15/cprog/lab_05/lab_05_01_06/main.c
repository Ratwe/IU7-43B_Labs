#include <stdio.h>
#include <stdlib.h>

#include "process.h"

int main(void)
{
    unsigned int max_len = 1;

    int check = process(stdin, &max_len);
    if (check != EXIT_SUCCESS)
        return check;

    printf("Result: %u\n", max_len);

    return EXIT_SUCCESS;
}
