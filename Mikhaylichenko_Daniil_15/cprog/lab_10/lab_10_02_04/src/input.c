#include "../inc/input.h"

int enter_string(char *str, size_t max_len)
{
    size_t str_len = 0;

    for (char ch; (ch = getchar()) != '\n' && ch != EOF;)
    {
        if (str_len < max_len - 1)
            str[str_len++] = ch;
        else
        {
            ERROR_LOG("TOO LONG STR");
            return WRONG_INPUT;
        }
    }

    str[str_len] = '\0';

    if (str[0] == '\0')
    {
        ERROR_LOG("EMPTY STR");
        return WRONG_INPUT;
    }

    return EXIT_SUCCESS;
}
