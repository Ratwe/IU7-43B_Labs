#include "process.h"
#include "defines.h"
#include <stdbool.h>

int process(FILE *f, int *count)
{
    int error_code = EXIT_SUCCESS;
    int old_value, value;
    bool have_value = false;

    *count = 0;
    
    if (fscanf(f, "%d", &old_value) != COUNT_INPUT_VALUE)
        error_code = EMPTY_INPUT;

    while (!error_code && fscanf(f, "%d", &value) == COUNT_INPUT_VALUE)
    {
        have_value = true;
    
        if (old_value * value < 0 || (old_value * value == 0 && (old_value + value) < 0))
            (*count)++;
        
        old_value = value;
    }

    if (!have_value)
        error_code = ONE_VALUE_INPUT;

    return error_code;
}
