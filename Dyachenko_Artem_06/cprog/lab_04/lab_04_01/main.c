#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 20
#define M 5

char *my_strpbrk(const char *str, const char *sym)
{
    size_t str_len = strlen(str);
    size_t sym_len = strlen(sym);

    for (size_t i = 0; i < str_len; i++)
        for (size_t j = 0; j < sym_len; j++)
            if (str[i] == sym[j])
                return (char *)&str[i];

    return NULL;
}

size_t my_strspn(const char *str, const char *sym)
{
    size_t str_len = strlen(str);
    size_t sym_len = strlen(sym);
    size_t row = 0;

    for (size_t i = 0; i < str_len; i++)
    {
        for (size_t j = 0; j < sym_len; j++)
        {
            if (str[i] == sym[j])
            {
                row++;
                break;
            }
        }

        if (i == row)
            break;
    }

    return row;
}

size_t my_strcspn(const char *str, const char *sym)
{
    size_t str_len = strlen(str);
    size_t sym_len = strlen(sym);

    for (size_t i = 0; i < str_len; i++)
        for (size_t j = 0; j < sym_len; j++)
            if (str[i] == sym[j])
                return i;

    return str_len;
}

char *my_strchr(const char *str, int ch)
{
    size_t str_len = strlen(str);

    if (ch == '\0')
        return (char *)&str[str_len];

    for (size_t i = 0; i < str_len; i++)
        if (str[i] == ch)
            return (char *)&str[i];

    return NULL;
}

char *my_strrchr(const char *str, int ch)
{
    size_t str_len = strlen(str);
    size_t t = -1;

    if (ch == '\0')
        return (char *)&str[str_len];

    for (size_t i = 0; i < str_len; i++)
        if (str[i] == ch)
            t = i;

    if (t == -1)
        return NULL;

    return (char *)&str[t];
}

int main(void)
{
    int err = 0;
    char sym[M] = "k234";
    char str[N] = "Abac 124 hak\n";

    #ifdef RAND
    for (size_t i = 0; i < N; i++)
        str[i] = 'a' + rand() % 25;

    for (size_t i = 0; i < M; i++)
        sym[i] = 'a' + rand() % 22;
    #endif


    #ifdef PRINT
    printf("str: ");
    for (size_t i = 0; i < N; i++)
        printf("%c", str[i]);

    printf("\nsym: ");

    for (size_t i = 0; i < M; i++)
        printf("%c", sym[i]);
    #endif

    char *a = strpbrk(str, sym);
    char *ma = my_strpbrk(str, sym);

    size_t b = strspn(str, sym);
    size_t mb = my_strspn(str, sym);

    size_t c = strcspn(str, sym);
    size_t mc = my_strcspn(str, sym);

    char *d = my_strchr(str, sym[0]);
    char *md = strchr(str, sym[0]);

    char *e = my_strrchr(str, sym[0]);
    char *me = strrchr(str, sym[0]);

    if (*a != *ma)
        err++;
    if (b != mb)
        err++;
    if (c != mc)
        err++;
    if (*d != *md)
        err++;
    if (*e != *me)
        err++;

    printf("%d\n", err);

    #ifdef DEBUG
    printf("\nstrpbrk = %c\n", *a);
    printf("my_strpbrk = %c\n\n", *ma);

    printf("strspn = %ld\n", b);
    printf("my_strspn = %ld\n\n", mb);

    printf("strcspn = %ld\n", c);
    printf("my_strcspn = %ld\n\n", mc);

    printf("strchr = %c\n", *d);
    printf("my_strchr = %c\n\n", *md);
    #endif
}
