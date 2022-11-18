/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief  Program printed number sing changes in sequence
 */
#include <stdio.h>
#include "process.h"

int main(void)
{
    int count;
    int error_code = process(stdin, &count);

    if (!error_code)
        printf("Result: %d\n", count);

    return error_code;
}
