#ifndef __STUDENT__H__
#define __STUDENT__H__

#include <stdint.h>
#include <stdbool.h>

#define MAX_SURNAME_LENGTH  26
#define MAX_NAME_LENGTH     11
#define MARK_COUNT          4

typedef struct
{
    char surname[MAX_SURNAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    uint32_t mark[MARK_COUNT];
} student_t;

/**
 * @param[in]   first   First student to compare
 * @param[in]   second  Second student to compare
 * @return  0 if surname and name equivalent
 *          >0 if first student grater in alphabetical order
 *          <0 in other cases
 * @breif   Compare students in alphabetical order
 */
int compare_students(student_t *first, student_t *second);
bool is_surname_begin(student_t *student, char *substr);
bool check_mark_normality(student_t *student, double normal);

#endif // #ifndef __STUDENT__H__
