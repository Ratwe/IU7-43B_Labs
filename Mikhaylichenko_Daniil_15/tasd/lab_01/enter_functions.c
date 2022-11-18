#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "enter_functions.h"
#include "numchecker.h"
#include "normalizing.h"

// Функция ввода строки
int enter_string(char *str, size_t *str_len, size_t max_len)
{
    *str_len = 0;

    for (char symbol; (symbol = getchar()) != '\n' && symbol != EOF;)
    {
        if (*str_len < max_len + 1)
            str[(*str_len)++] = symbol;
        else
        {
            ERROR_LOG("TOO LONG STR");
            return TOO_LONG_STR;
        }
    }

    str[*str_len] = '\0';

    if (str[0] == '\0')
    {
        ERROR_LOG("EMPTY STRING");
        return EMPTY_STRING;
    }

    return EXIT_SUCCESS;
}

// Функция ввода действительного числа
int scan_my_double(my_double *num)
{
    memset(num->mantissa, 0, sizeof(uint8_t) * (MANTISSA_LEN * 2));

    int rc;

    char str[MAX_STR_LEN + 1];

    printf("Enter double:\n");
    printf("---------|---------|---------|[eE][-----]\n");
    rc = enter_string(str, &(num->str_len), MAX_STR_LEN + 1);
    if (rc != EXIT_SUCCESS)
    {
        ERROR_LOG("WRONG INPUT");
        return rc;
    }

    rc = !check_number(str);
    if (rc != EXIT_SUCCESS)
    {
        ERROR_LOG("WRONG INPUT");
        return rc;
    }

    rc = normalize_double(num, str);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

// Функция ввода целого числа
int scan_my_int(my_double *num)
{
    memset(num->mantissa, 0, sizeof(uint8_t) * (MANTISSA_LEN * 2));

    int rc;

    char str[MANTISSA_LEN + 1];

    printf("Enter int:\n");
    printf("---------|---------|---------|\n");
    rc = enter_string(str, &(num->str_len),  MANTISSA_LEN + 1);
    if (rc != EXIT_SUCCESS)
    {
        ERROR_LOG("WRONG INPUT");
        return rc;
    }

    rc = !is_integer(str, MANTISSA_LEN);
    if (rc != EXIT_SUCCESS)
    {
        ERROR_LOG("WRONG INPUT");
        return rc;    
    }

    normalize_int(num, str);

    return EXIT_SUCCESS;
}
