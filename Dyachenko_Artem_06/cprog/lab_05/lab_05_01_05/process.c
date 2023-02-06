#include "process.h"
#include "defines.h"

int process(FILE *f, int *res_row)
{
    int now = 0;
    int last = 0;
    int error_code = EMPTY_INPUT;

    int row = 1;
    int max_row = 1;

    while (fscanf(f, "%d", &now) == INPUT_ELEM_COUNT)
    {
        if (last == now && error_code != EMPTY_INPUT)
        {
            row++;
            if (row > max_row)
                max_row = row;
        }
        else
            row = 1;

        if (error_code == EMPTY_INPUT)
            error_code = EXIT_SUCCESS;

        last = now;
    }

    *res_row = max_row;

    return error_code;
}
