#include <stdio.h>
#include "average.h"
#include "defines.h"

int calc_average(FILE *file, double *average)
{
    fseek(file, 0, SEEK_SET);

    double sum = 0;
    int counter = 0;

    for (double num; fscanf(file, "%lf", &num) == EXPECTED_NUMBER; counter++)
        sum += num; 

    if (!counter)
        return DIVISION_ZERO;

    *average = sum / counter;

    return RIGHT_INPUT;
}
