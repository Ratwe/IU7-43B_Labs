#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "my_snprintf.h"

#define MAX_LEN_STR 100

int test_null(void)
{
    char format[MAX_LEN_STR] = "%c";
    char res1[MAX_LEN_STR] = "";
    char res2[MAX_LEN_STR] = "";
    int len1 = my_snprintf(res1, MAX_LEN_STR, format, '\0');
    int len2 = snprintf(res2, MAX_LEN_STR, format, '\0');

    if (len1 == len2)
        return strcmp(res1, res2) == 0 ? 0 : 1;

    return 1;
}

int test_standart(void)
{
    char format[MAX_LEN_STR] = "%c";
    char res1[MAX_LEN_STR] = "";
    char res2[MAX_LEN_STR] = "";
    int len1 = my_snprintf(res1, MAX_LEN_STR, format, 'a');
    int len2 = snprintf(res2, MAX_LEN_STR, format, 'a');

    if (len1 == len2)
        return strcmp(res1, res2) == 0 ? 0 : 1;

    return 1;
}

int test_begin(void)
{
    char format[MAX_LEN_STR] = "%cwefdr";
    char res1[MAX_LEN_STR] = "";
    char res2[MAX_LEN_STR] = "";
    int len1 = my_snprintf(res1, MAX_LEN_STR, format, 'a');
    int len2 = snprintf(res2, MAX_LEN_STR, format, 'a');

    if (len1 == len2)
        return strcmp(res1, res2) == 0 ? 0 : 1;

    return 1;
}

int test_end(void)
{
    char format[MAX_LEN_STR] = "rfevd%c";
    char res1[MAX_LEN_STR] = "";
    char res2[MAX_LEN_STR] = "";
    int len1 = my_snprintf(res1, MAX_LEN_STR, format, 'a');
    int len2 = snprintf(res2, MAX_LEN_STR, format, 'a');

    if (len1 == len2)
        return strcmp(res1, res2) == 0 ? 0 : 1;

    return 1;
}

int test_middle(void)
{
    char format[MAX_LEN_STR] = "rfevd%cewfrv";
    char res1[MAX_LEN_STR] = "";
    char res2[MAX_LEN_STR] = "";
    int len1 = my_snprintf(res1, MAX_LEN_STR, format, 'a');
    int len2 = snprintf(res2, MAX_LEN_STR, format, 'a');

    if (len1 == len2)
        return strcmp(res1, res2) == 0 ? 0 : 1;

    return 1;
}

int test_many(void)
{
    char format[MAX_LEN_STR] = "%crvf%c%crevs";
    char res1[MAX_LEN_STR] = "";
    char res2[MAX_LEN_STR] = "";
    int len1 = my_snprintf(res1, MAX_LEN_STR, format, 'a', 'r', 'f');
    int len2 = snprintf(res2, MAX_LEN_STR, format, 'a', 'r', 'f');

    if (len1 == len2)
        return strcmp(res1, res2) == 0 ? 0 : 1;

    return 1;
}

int main(void)
{
    int err_count = 0;

    err_count += test_null() + test_end() + test_standart() + test_begin() + test_middle() + test_many();

    return err_count;
}
