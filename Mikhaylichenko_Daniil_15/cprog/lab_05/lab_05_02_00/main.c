#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "average.h"
#include "closest_value.h"


int main(int argc, char **argv)
{
    if (argc != MAX_ARGS)
        return ARGS_ERROR;

    int check;

    FILE *file = fopen(argv[1], "r");
    double average, closest_value;

    check = calc_average(file, &average);
    if (check != EXIT_SUCCESS)
    {
        fclose(file);
        return check;
    }

    find_closest_value(file, &average, &closest_value);

    fclose(file);

    printf("Result: %lf\n", closest_value);

    return EXIT_SUCCESS;
}
