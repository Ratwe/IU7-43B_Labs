#include <stdio.h>
#include <math.h>

#include "defines.h"

int process(FILE *f, double *res)
{
    int count = 0;
    double sum = 0;
    double mid = 0;
    double now = 0;

    while (fscanf(f, "%lf", &now) == INPUT_ELEM_COUNT)
    {
        count++;
        sum += now;
    }

    if (!count)
        return EMPTY_INPUT;

    rewind(f);

    mid = sum / count;
    *res = now + 1;

    while (fscanf(f, "%lf", &now) == INPUT_ELEM_COUNT)
        if (fabs(now - mid) < fabs(*res - mid))
            *res = now;

    if (fclose(f))
        return FCLOSE_ERROR;

    return EXIT_SUCCESS;
}
