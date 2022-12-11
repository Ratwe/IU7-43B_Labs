#include "../inc/scan.h"
#include <stdlib.h>

int check_buffer(void)
{
    int counter = 0;
    char ch;

    do
    {
        scanf("%c", &ch);

        if (ch == EOF)
            break;

        counter++;
    }
    while (ch != '\n');

    return counter;
}

int scan_command(int *command)
{
    int rc;

    printf("%s", "Введите номер комманды: ");

    rc = scanf("%d", command);

    if (check_buffer() != 1 || rc != 1)
    {
        ERROR_LOG("Ошибка считывании номера команды");
        return WRONG_INPUT;
    }

    if (*command < MIN_COMMAND || *command > MAX_COMMAND)
    {
        ERROR_LOG("Введённекоректный номер команды");
        return WRONG_INPUT;
    }

    return EXIT_SUCCESS;
}

int enter_string(char str[], size_t max_len)
{
    size_t str_len = 0;

    for (char symbol; (symbol = getchar()) != '\n' && symbol != EOF;)
    {
        if (str_len < max_len - 1)
            str[str_len++] = symbol;
        else
            return WRONG_STR;
    }

    str[str_len] = '\0';

    if (str[0] == '\0')
        return WRONG_STR;

    return EXIT_SUCCESS;
}
