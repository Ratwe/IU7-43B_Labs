#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum bool
{
    FALSE,
    TRUE
};

char *strpbrk_by_me(const char *str1, const char *str2)
{
    for (;*str1 != '\0'; str1++)
        for (const char *psymbol = str2; *psymbol != '\0'; psymbol++)
            if (*psymbol == *str1)
                return (char *) str1;

    return NULL;
}

size_t strspn_by_me(const char *str1, const char *str2)
{
    size_t count = 0;
    size_t is_part_of_segment = TRUE;

    for (;*str1 != '\0' && is_part_of_segment == TRUE; str1++)
    {
        is_part_of_segment = FALSE;

        for (const char *psymbol = str2; *psymbol != '\0'; psymbol++)
            if (*psymbol == *str1)
            {
                count++;
                is_part_of_segment = TRUE;
            }
    }

    return count;
}

size_t strcspn_by_me(const char *str1, const char *str2)
{
    size_t count = 0;

    for (;*str1 != '\0'; str1++, count++)
        for (const char *psymbol = str2; *psymbol != '\0'; psymbol++)
            if (*psymbol == *str1)
                return count;

    return count;
}

char *strchr_by_me(const char *str, int val)
{
    for (;*str != '\0'; str++)
        if (*str == val)
            return (char *) str;

    return NULL;
}

char *strrchr_by_me(const char *str, int val)
{
    char *position = NULL;

    for (;*str != '\0'; str++)
        if (*str == val)
            position = (char *) str;

    return position;
}

int main(void)
{
    int errors_counter = 0;

    //strpbrk
    errors_counter += (strpbrk("This is test line", "s") != strpbrk_by_me("This is test line", "s"));
    errors_counter += (strpbrk("This is test line", "$") != strpbrk_by_me("This is test line", "$"));

    //strspn
    errors_counter += (strspn("0123456789", "210") != strspn_by_me("0123456789", "210"));
    errors_counter += (strspn("0123456789", "$") != strspn_by_me("0123456789", "$"));

    //strcspn
    errors_counter += (strcspn("0123456789", "9876") != strcspn_by_me("0123456789", "9876"));
    errors_counter += (strcspn("0123456789", "$") != strcspn_by_me("0123456789", "$"));

    //strchr
    errors_counter += (strchr("This is test line", 's') != strchr_by_me("This is test line", 's'));
    errors_counter += (strchr("This is test line", '$') != strchr_by_me("This is test line", '$'));

    //strrchr
    errors_counter += (strrchr("This is test line", 's') != strrchr_by_me("This is test line", 's'));
    errors_counter += (strrchr("This is test line", '$') != strrchr_by_me("This is test line", '$'));

    printf("%d\n", errors_counter);

    return EXIT_SUCCESS;
}
