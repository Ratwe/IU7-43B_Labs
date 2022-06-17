#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16
#define MAX_WORDS_COUNT 128

#define TOO_LONG_STR 101
#define TOO_LONG_WORD 102
#define EMPTY_STRING 103
#define NO_DIFFERENT_WORDS 104
#define WRONG_INPUT 105

#define RIGHT_INPUT 0

#define PUNCTS ".!?,;:-\n"

int enter_string(char str[], size_t *str_len, size_t max_len);
void add_to_array(char words[][MAX_WORD_LEN + 1], char word[], size_t *words_count, size_t *word_len);
int split(char str[], 
char words[][MAX_WORD_LEN + 1], size_t *words_count, 
size_t max_len);
void make_new_word(char word[MAX_WORD_LEN + 1], char new_word[MAX_WORD_LEN + 1]);
int make_new_str(char words[][MAX_WORD_LEN + 1], size_t words_count, char new_str[]);

int main(void)
{
    int check;

    char str[MAX_STR_LEN + 1];
    size_t len = 0;

    printf("Enter string: ");
    check = enter_string(str, &len, MAX_STR_LEN);
    if (check != EXIT_SUCCESS)
        return check;

    char words[MAX_WORDS_COUNT][MAX_WORD_LEN + 1];
    size_t words_count = 0;

    check = split(str, words, &words_count, MAX_WORD_LEN);
    if (check != EXIT_SUCCESS)
        return check;

    char new_str[MAX_STR_LEN + 1] = { "" };
    check = make_new_str(words, words_count, new_str);
    if (check != EXIT_SUCCESS)
        return check;

    printf("Result: %s\n", new_str);

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


int split(char str[], 
char words[][MAX_WORD_LEN + 1], size_t *words_count, 
size_t max_len)
{
    size_t word_len = 0;
    bool all_spaces = true;

    for (; *str != 0; str++)
    {
        if (isspace(*str) || strchr(PUNCTS, *str) != NULL)
        {
            if (word_len > max_len)
                return TOO_LONG_WORD;

            if (word_len > 0)
            {
                words[(*words_count)++][word_len] = '\0';
                word_len = 0;
            }
        }
        else
        {
            words[*words_count][word_len++] = *str;
            all_spaces = false;
        }
    }

    if (word_len > 0)
        words[(*words_count)++][word_len] = '\0';

    if (*words_count == 1 || all_spaces == true)
        return WRONG_INPUT;

    return RIGHT_INPUT;
}

void make_new_word(char word[MAX_WORD_LEN + 1], char new_word[MAX_WORD_LEN + 1])
{
    size_t index = 0;

    for (char *symbol = word; *symbol != '\0'; symbol++)
    {
        if (strchr(word, *symbol) == symbol)
            new_word[index++] = *symbol;
    }
}

int make_new_str(char words[][MAX_WORD_LEN + 1], size_t words_count, char new_str[])
{
    strcpy(new_str, "");

    for (int i = words_count - 2; i >= 0; i--)
    {
        if (strcmp(words[i], words[words_count - 1]))
        {
            char new_word[MAX_WORD_LEN + 1] = { '\0' };

            make_new_word(words[i], new_word);

            if (strcmp(new_str, ""))
                strcat(new_str, " ");

            strcat(new_str, new_word);
        }

        if (new_str[0] == '\0')
            return NO_DIFFERENT_WORDS;
    }

    return RIGHT_INPUT;
}
