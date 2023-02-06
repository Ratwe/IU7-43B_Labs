#define  _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "task.h"

int read_type(int *type)
{
    char *option = NULL;
    size_t len = 0;

    if ((getline(&option, &len, stdin)) == -1)
        return GETLINE_ERR;

    option[strlen(option) - 1] = '\0';

    if (strcmp(option, "out") == 0)
        *type = OUT;
    else if (strcmp(option, "mul") == 0)
        *type = MUL;
    else if (strcmp(option, "sqr") == 0)
        *type = SQR;
    else if (strcmp(option, "div") == 0)
        *type = DIV;

    free(option);

    if (*type == 0)
       return WRONG_TYPE_ERR;

    return EXIT_SUCCESS;
}

int main(void)
{
    int error_code = 0;
    int type = 0;

    if ((error_code = read_type(&type)))
        return error_code;

    switch (type)
    {
        case OUT:
            if ((error_code = print_num()))
                return error_code;
            break;
        case MUL:
            if ((error_code = multiply()))
                return error_code;
            break;
        case SQR:
            if ((error_code = square()))
                return error_code;
            break;
        case DIV:
            if ((error_code = division()))
                return error_code;
            break;
    }

    return EXIT_SUCCESS;
}
