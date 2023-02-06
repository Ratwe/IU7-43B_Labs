#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256
#define M 16
#define S 8

#define YES_SEPARATOR 1
#define NO_SEPARATOR 0
#define YES_MATCHED 1
#define NOT_MATCHED 0

#define LINE_SIZE_ERROR 2
#define WORD_SIZE_ERROR 3
#define NO_WORDS_ERROR 4
#define EMPTY_RESULT_ERROR 5

int scan_line(char str[N])
{
    char t = getchar();
    int count = 0;

    while (t != '\n' && t != EOF)
    {
        str[count] = t;

        if (++count > N - 1)
            return LINE_SIZE_ERROR;

        t = getchar();
    }

    if (!count)
        return NO_WORDS_ERROR;

    str[count] = '\0';

    return EXIT_SUCCESS;
}

void copy_word(char *copy_to, char *copy_from, int size)
{
    int i = 0;

    for (; i < size; i++)
        copy_to[i] = copy_from[i];

    copy_to[i] = '\0';
}

int is_matched(char a[M], char b[M])
{
    // printf("matching %s %s\n", a, b);

    if (strlen(a) != strlen(b))
        return NOT_MATCHED;

    for (int i = 0; a[i] != '\0'; i++)
        if (a[i] != b[i])
            return NOT_MATCHED;


    return YES_MATCHED;
}

int split_line(char *str, char words[N][M], int *size)
{
    const char *separators = " .,;:-?!";
    char *token = strtok(str, separators);
    int count = 0;

    while (token != NULL)
    {
        if (strlen(token) > M)
            return WORD_SIZE_ERROR;

        copy_word(words[count++], token, strlen(token));

        token = strtok(NULL, separators);
    }

    if (!count)
        return NO_WORDS_ERROR;

    *size = count;

    return EXIT_SUCCESS;
}

void modify_word(char word[M], char res[M])
{
    int len = strlen(word);
    int count = 0;

    char first = word[0];
    res[0] = first;

    for (int i = 1; i < len; i++)
        if (word[i] != first)
            res[++count] = word[i];

    res[++count] = '\0';
}

int calc_string(char matrix[N][M], int size, char res[N])
{
    char last_word[M];
    int count = 0;

    copy_word(last_word, matrix[size - 1], strlen(matrix[size - 1]));

    // printf("last_word %s\n", last_word);
    // printf("[size-1] %s\n", matrix[size - 1]);
    // printf("len %ld\n", strlen(matrix[size - 1]));

    for (int i = size - 2; i >= 0; i--)
    {
        if (is_matched(matrix[i], last_word))
            continue;

        for (int j = 0; j < M && matrix[i][j] != '\0'; j++)
            res[count++] = matrix[i][j];

        res[count++] = ' ';
    }

    res[count] = '\0';

    if (!count)
        return EMPTY_RESULT_ERROR;

    return EXIT_SUCCESS;
}

int calc_res(char words[N][M], int size)
{
    char res[N][M];
    char res_str[N];
    int rc = EXIT_SUCCESS;

    for (int i = 0; i < size; i++)
        modify_word(words[i], res[i]);

    if ((rc = calc_string(res, size, res_str)))
        return rc;

    printf("Result: %s\n", res_str);

    return rc;
}

int main(void)
{
    char str[N];
    char words[N][M];

    int rc = 0;
    int size = 0;

    if ((rc = scan_line(str)))
        return rc;

    if ((rc = split_line(str, words, &size)))
        return rc;

    if ((rc = calc_res(words, size)))
        return rc;

    return EXIT_SUCCESS;
}
