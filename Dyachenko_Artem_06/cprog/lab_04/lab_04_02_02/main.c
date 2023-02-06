#include <stdio.h>
#include <stdlib.h>

#define N 256
#define M 16
#define S 8

#define YES_DUPLICATE 1
#define NO_DUPLICATE 0
#define NOT_MATCHED 0
#define YES_MATCHED 1
#define YES_SEPARATOR 1
#define NO_SEPARATOR 0

#define LINE_SIZE_ERROR 2
#define WORD_SIZE_ERROR 3
#define NO_WORDS_ERROR 4

int scan_line(char str[N])
{
    char t = getchar();
    int count = 0;

    if (t == EOF)
        return NO_WORDS_ERROR;

    while (t != '\n' && t != EOF)
    {
        str[count++] = t;
        t = getchar();

        if (count == N)
            return LINE_SIZE_ERROR;
    }

    str[count] = '\0';

    return EXIT_SUCCESS;
}

int is_separator(char c)
{
    char separators[S] = { ' ', ',', ';', ':', '-', '.', '!', '?' };

    for (int i = 0; i < S; i++)
        if (c == separators[i])
            return YES_SEPARATOR;

    return NO_SEPARATOR;
}

int get_words(char s[N], char words[N][M], int *size)
{
    int k = 0;
    int l = 0;

    for (int i = 0; s[i] != '\0' && s[i] != '\n'; i++)
    {
        if (l && is_separator(s[i]))
        {
            words[k++][l] = '\0';
            l = 0;
        }
        else if (!is_separator(s[i]))
        {
            words[k][l++] = s[i];

            if (l >= M)
                return WORD_SIZE_ERROR;
        }
    }

    if (k == 0 && l == 0)
        return NO_WORDS_ERROR;

    if (l)
        words[k++][l] = '\0';

    *size = k;

    return EXIT_SUCCESS;
}

void copy_word(char *copy_to, char *copy_from)
{
    int i = 0;

    for (; copy_from[i] != '\0'; i++)
        copy_to[i] = copy_from[i];

    copy_to[i] = '\0';
}

// Одинаковые ли слова
int is_matched(char a[M], char b[M])
{
    int i = 0;

    for (; a[i] != '\0'; i++)
        if (a[i] != b[i])
            return NOT_MATCHED;

    if (b[i] != '\0')
        return NOT_MATCHED;

    return YES_MATCHED;
}

// Было ли уже это слово в строке
int is_duplicate(char word[M], int pos, char words[N][M])
{
    for (int i = 0; i < pos; i++)
        if (is_matched(word, words[i]))
            return YES_DUPLICATE;

    return NO_DUPLICATE;
}

// Есть ли слово из первой строки во второй
int check_word(char word1[M], char words2[N][M], int size2)
{
    char word2[N] = { 0 };

    for (int i = 0; i < size2; i++)
    {
        copy_word(word2, words2[i]);

        if (is_matched(word1, word2))
            return YES_MATCHED;
    }

    return NOT_MATCHED;
}

void calc_res(char words1[N][M], int size1, char words2[N][M], int size2)
{
    printf("Result: ");

    for (int i = 0; i < size1; i++)
    {
        char word1[N] = { 0 };

        copy_word(word1, words1[i]);

        if (is_duplicate(word1, i, words1))
            continue;

        printf("%s %s\n", word1, check_word(word1, words2, size2) ? "yes" : "no");
    }
}

int main(void)
{
    char str1[N], str2[N];
    int rc = 0;

    if ((rc = scan_line(str1)))
        return rc;

    if ((rc = scan_line(str2)))
        return rc;

    char words1[N][M], words2[N][M];

    int size1 = 0, size2 = 0;

    if ((rc = get_words(str1, words1, &size1)))
        return rc;

    if ((rc = get_words(str2, words2, &size2)))
        return rc;

    calc_res(words1, size1, words2, size2);

    return EXIT_SUCCESS;
}
