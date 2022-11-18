#include <stdio.h>
#include <math.h>
#include "closest_value.h"
#include "defines.h"

void find_closest_value(FILE *file, double *average, double *closest_value)
{
    fseek(file, 0, SEEK_SET);

    double first_num;
    fscanf(file, "%lf", &first_num);

    double diff = fabs(*average - first_num);
    *closest_value = first_num;

    for (double num, temp_diff; fscanf(file, "%lf", &num) == EXPECTED_NUMBER;)
    {
        temp_diff = fabs(*average - num);

        if (temp_diff <= diff)
        {
            *closest_value = num;
            diff = temp_diff;
        }
    }
}
