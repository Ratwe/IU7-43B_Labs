#include <stdio.h>

#include "my_snprintf.h"

int read_char(char *const dst, const char chr, size_t *const len, const size_t max_len)
{
    if (*len < max_len - 1)
        dst[(*len)++] = chr;

    return 1;
}

int read_string(char *const dst, char *const src, size_t *const len, const size_t max_len)
{
    int return_val = 0;
    int i = 0;

    while (src[i] != '\0')
    {
        return_val += read_char(dst, src[i], len, max_len);
        i++;
    }

    return return_val;
}

char *my_strncpy(char *const dest, const char *src, const size_t n)
{
    size_t len = 0;

    while (*src != '\0' && len < n)
    {
        dest[len] = src[len];
        len++;
    }

    dest[len] = '\0';

    return dest;
}

char *my_itoa(long long value, char *const string, const int degree)
{
    char *nums = "0123456789abcdef";
    size_t len = 0;
    int neg_flag = 0;

    if (value == 0)
        string[len++] = '0';

    if (value < 0)
    {
        value *= -1;
        neg_flag = 1;
    }

    while (value != 0)
    {
        string[len++] = nums[value % degree];
        value /= degree;
    }

    if (neg_flag)
        string[len++] = '-';

    for (size_t i = 0; i < len / 2; i++)
    {
        char temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }

    string[len] = '\0';

    return string;
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    if (n && s == NULL)
        return -1;

    char *temp = calloc(n, sizeof(char));
    char str[MAX_STR_LEN];

    if (!temp)
        return 0;

    size_t len = 0;
    int return_val = 0;

    va_list args;
    va_start(args, format);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case 'd':
                case 'i':
                    my_itoa(va_arg(args, int), str, 10);
                    return_val += read_string(temp, str, &len, n);
                    break;
                case 'x':
                    my_itoa(va_arg(args, unsigned int), str, 16);
                    return_val += read_string(temp, str, &len, n);
                    break;
                case 'o':
                    my_itoa(va_arg(args, unsigned int), str, 8);
                    return_val += read_string(temp, str, &len, n);
                    break;
                case 'c':
                    return_val += read_char(temp, va_arg(args, int), &len, n);
                    break;
                default:
                    return_val += read_char(temp, '%', &len, n);
                    break;
            }
        }
        else
            return_val += read_char(temp, *format, &len, n);

        format++;
    }

    temp[len] = '\0';
    va_end(args);

    if (!s || n == 0)
    {
        free(temp);
        return len;
    }

    my_strncpy(s, temp, len);
    free(temp);

    return return_val;
}
