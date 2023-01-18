#include "../inc/my_snprintf.h"

void reverse(char *str, int index)
{
    for (int i = 0; i < index / 2; i++)
    {
        char temp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = temp;
    }
}

int transform(char *str, int data, int radix)
{
    int index = 0;

    if (data == 0)
        str[index++] = '0';

    for (char temp; data != 0; data /= radix)
    {
        temp = data % radix;
        str[index++] = temp;
    }

    reverse(str, index);

    if (index != 0)
        str[index] = '\0';

    return index;
}

int convert_num(char *str, int count_limit, int *index, int data, int radix)
{
    int counter = 0;

    if (data < 0)
    {
        counter++;
        data *= -1;

        if (count_limit > *index)
            str[(*index)++] = '-';
    }

    char num_str[STR_LEN];
    int str_len = transform(num_str, data, radix);

    for (int i = 0; i < str_len; i++, counter++)
    {
        if (count_limit > *index)
            str[(*index)++] = num_str[i];
    }

    return counter;
}

int convert_char(char *str, int count_limit, int *index, char data)
{
    if (count_limit > *index)
        str[(*index)++] = data;

    return 1;
}

int convert_str(char *str, int count_limit, int *index, char *src)
{
    int counter = 0;

    for (; src[counter] != '\0'; counter++)
        if (count_limit > *index)
            str[(*index)++] = src[counter];

    return counter;
}

int my_snprintf(char *str, size_t count, const char *fmt, ...)
{
    va_list v1;

    int index = 0, fmt_count = 0;

    va_start(v1, fmt);

    for (; *fmt != '\0';)
    {
        if (*fmt == '%')
        {
            fmt++;

            if (*fmt == '%')
            {
                fmt_count++;
                fmt++;

                if (count > index)
                    str[index++] = *fmt;
            }
            else if (*fmt == SHORT && *(fmt + 1) == INT)
            {
                int data = va_arg(v1, int);
                fmt_count += convert_num(str, count, &index, data, DEC_RADIX);
                fmt += 2;
            }
            else if (*fmt == CHAR)
            {
                char data = va_arg(v1, int);
                fmt_count += convert_char(str, count, &index, data);
                fmt++;
            }
            else if (*fmt == STR)
            {
                char *data = va_arg(v1, char*);
                fmt_count += convert_str(str, count, &index, data);
                fmt++;
            }
            else if (*fmt == OCT)
            {
                int data = va_arg(v1, int);
                fmt_count += convert_num(str, count, &index, data, OCT_RADIX);
                fmt++;
            }
        }
        else
        {
           fmt_count++;
           fmt++;

           if (count > index)
               str[index++] = *fmt;
        }
    }

    if (count == index && count != 0)
        str[--index] = '\0';
    else if (count > 0)
        str[index] = '\0';

    va_end(v1);

    return fmt_count;
}
