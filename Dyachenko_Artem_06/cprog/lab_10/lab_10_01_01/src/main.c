#include <stdio.h>

#include "defines.h"
#include "task.h"

int main(int argc, char **argv)
{
    int error_code = EXIT_SUCCESS;

    if (argc != 3)
        return ARGS_COUNT_ERR;

    if ((error_code = do_task(argv[1], argv[2])))
        return error_code;

    return EXIT_SUCCESS;
}
