#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "file_functions.h"
#include "functions.h"

int print_sort_file(char *file_name)
{
    int check;

    FILE *file = NULL;

    if ((file = fopen(file_name, "r")) == NULL)
        return FILE_OPEN_ERROR;

    s_subject all_subjects[15];

    memset(all_subjects, 0, sizeof(all_subjects));
    
    size_t size = 0;

    check = get_structs(file, all_subjects, &size);
    if (check != RIGHT_STRUCT)
    {
        fclose(file);
        return check;
    }
    
    sort_by_density(all_subjects, size);

    for (size_t i = 0; i < size; print_struct(all_subjects[i]), i++);
   
    fclose(file);
    
    return EXIT_SUCCESS;
}

int print_certain_subject(char *file_name, char *sub_str)
{
    int check;

    FILE *file = NULL;

    if ((file = fopen(file_name, "r")) == NULL)
        return FILE_OPEN_ERROR;

    s_subject all_subjects[15];

    memset(all_subjects, 0, sizeof(all_subjects));
    
    size_t size = 0;

    check = get_structs(file, all_subjects, &size);
    if (check != RIGHT_STRUCT)
    {
        fclose(file);
        return check;
    }

    if (!strcmp(sub_str, "ALL"))
        for (size_t i = 0; i < size; print_struct(all_subjects[i]), i++);
    else
    {
        int counter = 0;

        for (size_t i = 0; i < size; i++)
            if (!is_begining(sub_str, all_subjects[i].name))
            {
                print_struct(all_subjects[i]);
                counter++;
            }

        if (counter == 0)
            return NO_STRUCTS;
    }

    fclose(file);

    return EXIT_SUCCESS;
}
