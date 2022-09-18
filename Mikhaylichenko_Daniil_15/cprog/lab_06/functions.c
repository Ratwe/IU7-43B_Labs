#include "functions.h"
#include <string.h>

int get_string(FILE *file, char *str)
{
    if (fgets(str, MAX_NAME_LEN + 2, file) == NULL)
        return WRONG_STR;

    return RIGHT_STR;
}

int get_double(FILE *file, double *var)
{
    if (fscanf(file, "%lf", var) != EXPECTED_NUMBER || *var <= 0.0f)
        return WRONG_DOUBLE;

    return RIGHT_STRUCT;
}

int get_structs(FILE *file, s_subject all_subjects[], size_t *size)
{
    int check;

    for (; *size < MAX_STRUCT; (*size)++)
    {
        check = get_string(file, all_subjects[*size].name);
        if (check != RIGHT_STRUCT)
            return check;

        check = get_double(file, &all_subjects[*size].weight);
        if (check != RIGHT_STRUCT)
            return check;

        check = get_double(file, &all_subjects[*size].volume);
        if (check != RIGHT_STRUCT)
            return check;

        if (fgetc(file) == EOF)
        {
            (*size)++;
            break;
        }
    }

    if (*size == 0)
        return NO_STRUCTS;

    if (*size >= 15)
        return TOO_MUCH_STRUCTS;

    return RIGHT_STRUCT;
}

void sort_by_density(s_subject all_subjects[], size_t size)
{   
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = 0; j < size - i - 1; j++)
        {
            double density_i = all_subjects[j].weight / all_subjects[j].volume;
            double density_j = all_subjects[j + 1].weight / all_subjects[j + 1].volume;

            if (density_i > density_j)
            {
                s_subject temp = all_subjects[j];
                all_subjects[j] = all_subjects[j + 1];
                all_subjects[j + 1] = temp;
            }
        }
}

// Проверка на начало из подстроки
int is_begining(char *sub_str, char *str)
{
    size_t len = strlen(sub_str);

    for (size_t i = 0; i < len; i++)
        if (str[i] != sub_str[i])
            return WRONG_STR;

    return RIGHT_STR;
}

void print_struct(s_subject subject)
{
    printf("%s%f\n%f\n", subject.name, subject.weight, subject.volume);
}
