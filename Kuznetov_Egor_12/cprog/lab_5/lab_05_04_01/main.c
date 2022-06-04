#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#include "file_interface.h"

#define COUNT_INPUT_VALUES  1
#define MINIMAL_ARGC        3
#define MAXIMAL_ARGC        5
#define UNCORRECT_ARGS      53

int main(int argc, char **argv)
{
    int error_code = EXIT_SUCCESS;

    if (argc < MINIMAL_ARGC || argc > MAXIMAL_ARGC)
        error_code = UNCORRECT_ARGS;
    
    if (!error_code)
    {
        if (strncmp(argv[1], "sb", 2) == 0 && argc == MINIMAL_ARGC)
            error_code = sort_file(argv[2]);
        else if (strncmp(argv[1], "fb", 2) == 0 && argc == MAXIMAL_ARGC)
            error_code = find_students_in_file(argv[2], argv[3], argv[4]);
        else if (strncmp(argv[1], "db", 2) == 0 && argc == MINIMAL_ARGC)
            error_code = delete_students_in_file(argv[2]);
        else
            error_code = UNCORRECT_ARGS;
    }

    return error_code;
}
