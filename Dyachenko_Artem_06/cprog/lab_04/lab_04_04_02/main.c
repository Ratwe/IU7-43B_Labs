#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define N 256
#define M 16
#define S 12
#define WORDS_COUNT 3

#define NOT_MATCHED 0
#define YES_MATCHED 1

#define LINE_SIZE_ERROR 2
#define WORD_SIZE_ERROR 3
#define NO_WORDS_ERROR 4
#define WORDS_COUNT_LIMIT_ERROR 5

#define DAY_SIZE_ERROR 11
#define NO_DAY_ERROR 12
#define CORRECT_DAY 0
#define INCORRECT_DAY 10
#define DAY_NO_DIGIT_ERROR 13

#define MONTH_SIZE_ERROR 21
#define NO_MONTH_ERROR 22
#define CORRECT_MONTH 0
#define INCORRECT_MONTH 20

#define YEAR_SIZE_ERROR 31
#define NO_YEAR_ERROR 32
#define WRONG_YEAR 33
#define YEAR_NO_DIGIT_ERROR 44
#define CORRECT_YEAR 0


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

int check_line(char s[N])
{
    int words = 0;

    for (int i = 1; s[i] != '\0'; i++)
    {
        if (isspace(s[i]) && !isspace(s[i - 1]))
            words++;

        if (words == WORDS_COUNT && !isspace(s[i]))
            return WORDS_COUNT_LIMIT_ERROR;
    }

    return EXIT_SUCCESS;
}

int get_day(char s[N], char day[N], int *pos)
{
    int i = *pos;
    int count = 0;

    while (s[i] != '\0' && s[i] != '\n')
    {
        if (!isspace(s[i]))
            day[count++] = s[i];

        if (count >= M)
            return DAY_SIZE_ERROR;

        if (isspace(s[i]) && count)
            break;

        i++;
    }

    day[count] = '\0';
    *pos = i;

    if (!count)
        return NO_DAY_ERROR;

    return EXIT_SUCCESS;
}

int get_month(char s[N], char month[N], int *pos)
{
    int i = *pos;
    int count = 0;

    while (s[i] != '\0' && s[i] != '\n')
    {
        if (!isspace(s[i]))
            month[count++] = tolower(s[i]);

        if (count >= M)
            return MONTH_SIZE_ERROR;

        if (isspace(s[i]) && count)
            break;

        i++;
    }

    month[count] = '\0';
    *pos = i;

    if (!count)
        return NO_MONTH_ERROR;

    return EXIT_SUCCESS;
}

int get_year(char s[N], char year[N], int *pos)
{
    int i = *pos;
    int count = 0;

    while (s[i] != '\0' && s[i] != '\n')
    {
        if (!isspace(s[i]))
            year[count++] = s[i];

        if (count >= M)
            return YEAR_SIZE_ERROR;

        if (isspace(s[i]) && count)
            break;

        i++;
    }

    year[count] = '\0';
    *pos = i;

    if (!count)
        return NO_YEAR_ERROR;

    return EXIT_SUCCESS;
}

int get_num_year(char year[N], int *num)
{
    int i = 0;
    int temp = 0;
    int pw = 0;

    while (year[i] != '\0' && year[i++]);
    // теперь year[i] == '\0'

    for (i--; i >= 0; i--, pw++)
    {
        if (!isdigit(year[i]))
            return YEAR_NO_DIGIT_ERROR;

        temp += (year[i] - '0') * (int)pow(10, pw);
    }

    *num = temp;

    return CORRECT_YEAR;
}

int get_num_day(char day[N], int *num)
{
    int i = 0;
    int temp = 0;
    int pw = 0;

    while (day[i] != '\0' && day[i++]);
    // теперь day[i] == '\0'

    for (i--; i >= 0; i--, pw++)
    {
        if (!isdigit(day[i]))
            return DAY_NO_DIGIT_ERROR;

        temp += (day[i] - '0') * (int)pow(10, pw);
    }

    *num = temp;

    return CORRECT_DAY;
}

int check_year(int num_year)
{
    if (num_year <= 0)
        return WRONG_YEAR;

    return EXIT_SUCCESS;
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

int check_month(char month[N])
{
    char monthes[S][M] = { "january", "february", "march", "april", "may", "june",
        "july", "august", "september", "october", "november", "december" };

    for (int i = 0; i < S; i++)
        if (is_matched(monthes[i], month))
            return CORRECT_MONTH;

    return INCORRECT_MONTH;
}

int check_day(int num_day, char month[M], int num_year)
{
    if (is_matched("january", month))
        return ((num_day <= 31) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("february", month))
    {
        if (((num_year % 4 == 0) && (num_year % 100)) || (num_year % 400 == 0))
            return ((num_day <= 29) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

        return ((num_day <= 28) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;
    }

    if (is_matched("march", month))
        return ((num_day <= 31) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("april", month))
        return ((num_day <= 30) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("may", month))
        return ((num_day <= 31) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("june", month))
        return ((num_day <= 30) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("july", month))
        return ((num_day <= 31) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("august", month))
        return ((num_day <= 31) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("september", month))
        return ((num_day <= 30) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("october", month))
        return ((num_day <= 31) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("november", month))
        return ((num_day <= 30) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    if (is_matched("december", month))
        return ((num_day <= 31) && (num_day >= 1)) ? CORRECT_DAY : INCORRECT_DAY;

    return INCORRECT_DAY;
}

int calc_res(char s[N])
{
    char day[M], month[M], year[M];

    int rc;
    int pos = 0;

    if ((rc = check_line(s)))
        return rc;

    if ((rc = get_day(s, day, &pos)))
        return rc;

    if ((rc = get_month(s, month, &pos)))
        return rc;

    if ((rc = get_year(s, year, &pos)))
        return rc;

    int num_year, num_day;

    if ((rc = get_num_year(year, &num_year)))
        return rc;

    if ((rc = get_num_day(day, &num_day)))
        return rc;

    #ifdef DEBUG
    printf("num_day = %d\n", num_day);
    printf("num_year = %d\n", num_year);
    #endif

    if ((rc = check_year(num_year)))
        return rc;

    if ((rc = check_month(month)))
        return rc;

    if ((rc = check_day(num_day, month, num_year)))
        return rc;

    return EXIT_SUCCESS;
}

int main(void)
{
    char str[N];

    int rc = scan_line(str);

    if (rc == NO_WORDS_ERROR)
    {
        printf("NO\n");
        return EXIT_SUCCESS;
    }
    else if (rc)
        return rc;

    if ((rc = calc_res(str)))
        printf("NO\n");
    else
        printf("YES\n");

    return EXIT_SUCCESS;
}
