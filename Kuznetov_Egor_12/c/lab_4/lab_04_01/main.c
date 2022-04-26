/**
 * @file
 * @author  Kuznetsov Egor IU7-23B
 * @brief   Unit testing self realization library function
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @param[in] str1  Source string
 * @param[in] str2  Match string
 * @return  First occurence
 * @breif   Find first occurence in `str1` of any characters from `str2`
 */
char *my_strpbrk(const char *str1, const char *str2)
{
    while (*str1 != '\0')
    {
        for (const char *c = str2; *c != '\0'; c++)
            if (*str1 == *c)
                return (char *)str1;
        
        str1++;
    }

    return NULL;
}

/**
 * @param[in] str1  Source string
 * @param[in] str2  Match string
 * @return  Count same character
 * @breif   Find count character from start same as `str2`
 */
size_t my_strspn(const char *str1, const char *str2)
{
    size_t count = 0;
    bool in_substring = true;

    for (; *str1 != '\0' && in_substring; str1++)
    {
        in_substring = false;

        for (const char *i = str2; *i != '\0'; i++)
            if (*str1 == *i)
            {
                count++;
                in_substring = true;
            }
    }

    return count;
}

/**
 * @param[in] str1  Source string
 * @param[in] str2  Match string
 * @return  Count not same character
 * @breif   Find count characrer from start not finded in `str2`
 */
size_t my_strcspn(const char *str1, const char *str2)
{
    size_t part_lenght = 0;

    for (; *str1 != '\0'; str1++, part_lenght++)
        for (const char *i = str2; *i != '\0'; i++)
            if (*str1 == *i)
                return part_lenght;

    return part_lenght;
}

/**
 * @param[in] str       Source string
 * @param[in] character Match character
 * @return  Pointer on first `character` in line or NULL
 * @breif   Find first `character` in line
 */
char *my_strchr(const char *str, int character)
{
    do
    {
        if (*str == character)
            return (char *)str;
    } while (*str++);
    
    return NULL;
}

/**
 * @param[in] str       Source string
 * @param[in] character Match character
 * @return  Pointer on last `character` in line or NULL
 * @breif   Find last `character` in line
 */
char *my_strrchr(const char *str, int character)
{
    char *result = NULL;

    do
    {
        if (*str == character)
            result = (char *)str;
    } while (*str++);
    
    return result;
}

int main(void)
{
    size_t count_failed = 0;    
    
    // 0) strpbrk
    // 1 symbol in str2 
    count_failed += (my_strpbrk("Simple line", "l") != strpbrk("Simple line", "l"));
    count_failed += (my_strpbrk("Test string", "q") != strpbrk("Test string", "q"));
    count_failed += (my_strpbrk("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", "e") != strpbrk("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", "e"));
    
    // Strings don`t have same elements
    count_failed += (my_strpbrk("QWERTY", "qwerty") != strpbrk("QWERTY", "qwerty"));
    count_failed += (my_strpbrk("Test string", "1234567890") != strpbrk("Test string", "1234567890"));

    // Srtings have same elements
    count_failed += (my_strpbrk("Same string", "Same string") != strpbrk("Same string", "Same string"));
    count_failed += (my_strpbrk("Same elements", "el;,") != strpbrk("Same elements", "el;,"));
    
    // 1) strspn
    // 1 symbol in str2 
    count_failed += (my_strspn("Simple line", "l") != strspn("Simple line", "l"));
    count_failed += (my_strspn("Test string", "q") != strspn("Test string", "q"));
    count_failed += (my_strspn("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", "e") != strspn("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", "e"));
    
    // Strings don`t have same elements
    count_failed += (my_strspn("QWERTY", "qwerty") != strspn("QWERTY", "qwerty"));
    count_failed += (my_strspn("Test string", "1234567890") != strspn("Test string", "1234567890"));

    // Srtings have same elements
    count_failed += (my_strspn("Same string", "Same string") != strspn("Same string", "Same string"));
    count_failed += (my_strspn("Same elements", "el;,") != strspn("Same elements", "el;,"));

    // 2) strcspn
    // 1 symbol in str2 
    count_failed += (my_strcspn("Simple line", "l") != strcspn("Simple line", "l"));
    count_failed += (my_strcspn("Test string", "q") != strcspn("Test string", "q"));
    count_failed += (my_strcspn("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", "e") != strcspn("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", "e"));
    
    // Strings don`t have same elements
    count_failed += (my_strcspn("QWERTY", "qwerty") != strcspn("QWERTY", "qwerty"));
    count_failed += (my_strcspn("Test string", "1234567890") != strcspn("Test string", "1234567890"));

    // Srtings have same elements
    count_failed += (my_strcspn("Same string", "Same string") != strcspn("Same string", "Same string"));
    count_failed += (my_strcspn("Same elements", "el;,") != strcspn("Same elements", "el;,"));
    
    // 3) strchr
    count_failed += (my_strchr("Simple line", 'l') != strchr("Simple line", 'l'));
    count_failed += (my_strchr("Test string", 'q') != strchr("Test string", 'q'));
    count_failed += (my_strchr("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", 'e') != strchr("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", 'e'));
    
    // 4) strrchr
    count_failed += (my_strrchr("Simple line", 'l') != strrchr("Simple line", 'l'));
    count_failed += (my_strrchr("Test string", 'q') != strrchr("Test string", 'q'));
    count_failed += (my_strrchr("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", 'e') != strrchr("Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long Long long long long string", 'e'));
    
    printf("Count failed: %zu\n", count_failed);

    return EXIT_SUCCESS;
}
