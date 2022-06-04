#include "student.h"
#include <string.h>

int compare_students(student_t *first, student_t *second)
{
    int value = strncmp(first->surname, second->surname, MAX_SURNAME_LENGTH);
    
    if (value == 0)
        value = strncmp(first->name, second->name, MAX_NAME_LENGTH);

    return value;
}

bool is_surname_begin(student_t *student, char *substr)
{
    return strncmp(student->surname, substr, strlen(substr)) == 0;
}

bool check_mark_normality(student_t *student, double normal)
{
    double sum = 0;

    for (size_t i = 0; i < MARK_COUNT; i++)
        sum += student->mark[i];

    return sum - normal >= 0;
}
