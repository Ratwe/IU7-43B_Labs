#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum bool
{
    FALSE,
    TRUE
};

char *my_strpbrk(const char *str1, const char *str2)
{
    for (;*str1 != '\0'; str1++)
        for (const char *psymbol = str2; *psymbol != '\0'; psymbol++)
            if (*psymbol == *str1)
                return (char *) str1;

    return NULL;
}

size_t my_strspn(const char *str1, const char *str2)
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

size_t my_strcspn(const char *str1, const char *str2)
{
    size_t count = 0;

    for (;*str1 != '\0'; str1++, count++)
        for (const char *psymbol = str2; *psymbol != '\0'; psymbol++)
            if (*psymbol == *str1)
                return count;

    return count;
}

char *my_strchr(const char *str, int val)
{
    do
    {
        if (*str == val)
            return (char *) str;
    }
    while (*str++);

    return NULL;
}

char *my_strrchr(const char *str, int val)
{
    char *position = NULL;

    do
    {
        if (*str == val)
            position = (char *) str;
    }
    while (*str++);

    return position;
}

int main(void)
{
    int errors_counter = 0;

    //strpbrk
    errors_counter += (strpbrk("This is test line", "s") != my_strpbrk("This is test line", "s"));
    errors_counter += (strpbrk("This is test line", "$") != my_strpbrk("This is test line", "$"));

    //strspn
    errors_counter += (strspn("0123456789", "210") != my_strspn("0123456789", "210"));
    errors_counter += (strspn("0123456789", "$") != my_strspn("0123456789", "$"));

    //strcspn
    errors_counter += (strcspn("0123456789", "9876") != my_strcspn("0123456789", "9876"));
    errors_counter += (strcspn("0123456789", "$") != my_strcspn("0123456789", "$"));

    //strchr
    errors_counter += (strchr("This is test line", 's') != my_strchr("This is test line", 's'));
    errors_counter += (strchr("This is test line", '$') != my_strchr("This is test line", '$'));

    //strrchr
    errors_counter += (strrchr("This is test line", 's') != my_strrchr("This is test line", 's'));
    errors_counter += (strrchr("This is test line", '$') != my_strrchr("This is test line", '$'));

    printf("%d\n", errors_counter);

    return EXIT_SUCCESS;
}
