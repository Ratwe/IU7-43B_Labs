#include <string.h>

#include "numchecker.h"

// Функция проверки на целое число
bool is_integer(char *str, size_t max_len)
{
    int temp;
    char extra;

    if (strlen(str) <= max_len && str[0] != '0')
        if (sscanf(str, "%d%c", &temp, &extra) == 1)
            return true;

    return false;
}

// Функция проверки на действительное число
int is_double(char *str)
{
    double temp;
    char extra;
    size_t str_len = strlen(str);

    if (str_len > 1)
        if (str[0] == '0' && str[1] != '.')
            return false;

    if (str_len <= MANTISSA_LEN)
        if (sscanf(str, "%lf%c", &temp, &extra) == 1)
            return true;

    return false;
}

// Функция проверки на действительно число с экспонентой
bool is_exp_double(char *str)
{
    int rc = 0;

    char *copy = malloc(sizeof(strlen(str)));
    if (copy != NULL)
    {
        strcpy(copy, str);

        char *pch = strtok(copy, "eE");
        if (!is_double(pch))
            rc++;

        pch = strtok(NULL, "eE");
        if (pch == NULL || !is_integer(pch, EXP_LEN))
            rc++;

        free(copy);

        if (rc == 0)
            return true;
    }
    
    return false;
}

// Функция счёта символов "eE" в строке
int count_exp(char *str)
{
    int counter = 0;

    for(; *str != '\0'; str++)
        if (*str == 'e' || *str == 'E')
            counter++;

    return counter;
           
}

// Основная функция проверки строки на число
bool check_number(char *str)
{
    switch (count_exp(str))
    {
        case 0:
            return is_double(str);
            break;
        case 1:
            return is_exp_double(str);
            break;
        default:
            return false;
            break;
    }
}
