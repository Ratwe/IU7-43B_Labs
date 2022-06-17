#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STR_LEN 256

#define TOO_LONG_STR 101
#define EMPTY_STRING 102
#define WRONG_INPUT 103

#define RIGHT_INPUT 0

int enter_string(char str[], size_t *str_len, size_t max_len);
int check_string(char str[]);
int right_first_part(char *pch);
int right_second_part(char *pch);
int right_third_part(char *pch);
int right_forth_part(char *pch);
bool is_right_number(char number[]);

int main(void)
{
    int check;

    char number[MAX_STR_LEN + 1];
    size_t len = 0;

    check = enter_string(number, &len, MAX_STR_LEN);
    if (check != EXIT_SUCCESS && check != EMPTY_STRING)
        return check;
    else if (check == EMPTY_STRING)
    {
        printf("NO\n");
        return EXIT_SUCCESS;
    }

    check = check_string(number);
    if (check != EXIT_SUCCESS)
    {
        printf("NO\n");
        return EXIT_SUCCESS;
    }

    printf(is_right_number(number) ? "YES\n" : "NO\n");

    return EXIT_SUCCESS;
}

int enter_string(char str[], size_t *str_len, size_t max_len)
{
    for (char symbol; (symbol = getchar()) != '\n' && symbol != EOF;)
    {
        if (*str_len < max_len - 1)
            str[(*str_len)++] = symbol;
        else
            return TOO_LONG_STR;
    }
    
    str[*str_len] = '\0';

    if (str[0] == '\0')
        return EMPTY_STRING;

    return RIGHT_INPUT;
}

int check_string(char str[])
{
    for (char *symbol = str + 1; *symbol != '\0'; symbol++)
        if (*symbol == '-' && *(symbol - 1) == '-')
            return WRONG_INPUT;

    size_t counter = 0;
    for (char *symbol = str + 1; *symbol != '\0'; symbol++)
        if (*symbol == '-')
            counter++;

    if (counter != 3)
        return WRONG_INPUT;

    if (str[0] == '-')
        return WRONG_INPUT;

    if (!strchr(str, '(') || !strchr(str, ')'))
        return WRONG_INPUT;

    if (*(strchr(str, ')') + 1) != '-')
        return WRONG_INPUT;

    return RIGHT_INPUT;
}

int right_first_part(char *pch)
{
    int check = 0;
    size_t len = strlen(pch);

    if (len >= 5)
    { 
        char *symbol = pch;
        for (; *symbol != '+' && *symbol != '('; symbol++)
            if (!isspace(*symbol))
                check++;

        if (*symbol == '+')
            for (symbol++; *symbol != '('; symbol++)
                if (!isdigit(*symbol))
                    check++;

        if (*symbol == '(')
        {
            size_t counter = 1;
            for (symbol++; *symbol != ')'; symbol++, counter++)
                if (!isdigit(*symbol) || counter > 3)
                    check++;
        }
    }
    else
        check++;

    return check;
}

int right_second_part(char *pch)
{
    return (strlen(pch) == 3 && isdigit(pch[0]) && isdigit(pch[1]) && isdigit(pch[2])) ? 0 : 1;
}

int right_third_part(char *pch)
{
    return (strlen(pch) == 2 && isdigit(pch[0]) && isdigit(pch[1])) ? 0 : 1;
}

int right_forth_part(char *pch)
{
    int check = 0;
    size_t len = strlen(pch);

    if (len >= 2)
    {
        if (!isdigit(pch[0]) || !isdigit(pch[1]))
            check++;
        else
            for (size_t i = 2; i < len; i++)
                if (!isspace(pch[i]))
                    check++;
    }
    else
        check++;

    return check;
}

bool is_right_number(char number[])
{
    char *pch = strtok(number, "-");
    int check = 0, parts_counter = 0;

    for (size_t part = 1; pch != NULL; pch = strtok(NULL, "-"), part++)
    {
        if (part == 1)
            check += right_first_part(pch);
        else if (part == 2)
            check += right_second_part(pch);
        else if (part == 3)
            check += right_third_part(pch);
        else if (part == 4)
            check += right_forth_part(pch);

        parts_counter++;
    }
    return (!check && parts_counter == 4) ? true : false;
}
