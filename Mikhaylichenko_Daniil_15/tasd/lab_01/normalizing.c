#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"
#include "normalizing.h"
#include "numchecker.h"

/*
 * Функция получения начального индекса
 * Если в строке есть "+" или "-",  возвращает 1
 * Иначе 0
 */
size_t get_start_index(char ch, char *sign)
{
    switch (ch)
    {
        case '-':
            *sign = IS_NEGATIVE;
            return 1;
            break;
        case '+':
            *sign = IS_POSITIVE;
            return 1;
            break;
        default:
            *sign = IS_POSITIVE;
            return 0;
            break;
    }
}

// Функция нормализации действительного числа без экспаненты
void normalize_noexp_double(my_double *num, char *str)
{
    size_t start_index = get_start_index(str[0], &(num->sign));
    num->exp = 0;

    bool point_flag = false, null_flag = false;
    int index = 0;

    size_t str_len = strlen(str);

    for (size_t i = start_index; i < str_len; i++, index++)
    {
        if (str[i] == '.')
        {
            point_flag = true;
            index--;
            continue;
        }

        if (str[i] != '0')
            null_flag = true;

        if (null_flag && isdigit(str[i]))
        {
            if (index <= MANTISSA_LEN)
                num->mantissa[index] = str[i] - 48;
        }
        else
        {
            num->exp--;
            index--;
        }

        if (!point_flag)
            num->exp++;
    }
}

// Функция нормализации действительного числа с экспанентой
int normalize_exp_double(my_double *num, char *str)
{
    char *copy = malloc(sizeof(num->str_len + 1));
    if (copy != NULL)
    {
       strncpy(copy, str, num->str_len + 1);

       char *pch = strtok(copy, "eE");

       normalize_noexp_double(num, pch);

       pch = strtok(NULL, "eE");       

       int temp_exp;
       sscanf(pch, "%d", &temp_exp);
       num->exp += temp_exp;

       free(copy);
    }
    else
    {
        ERROR_LOG("ARRAY ALLOCATE ERROR");
        return ARRAY_ALLOCATE_ERROR;
    }

    return EXIT_SUCCESS;
}

// Функция нормализации действительного числа
int normalize_double(my_double *num, char *str)
{
    int rc;

    switch (count_exp(str))
    {
        case 0:
            normalize_noexp_double(num, str);
            break;
        case 1:
            rc = normalize_exp_double(num, str);
            if (rc != EXIT_SUCCESS)
                return rc;
            break;
    }

    return EXIT_SUCCESS; 
}

void normalize_int(my_double *num, char *str)
{
    size_t start_index = get_start_index(str[0], &(num->sign));
    num->exp = num->str_len; 

    for (size_t i = start_index, arr_i = 0; i < num->str_len; i++)
        num->mantissa[arr_i++] = str[i] - 48;
}
