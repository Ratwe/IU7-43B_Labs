/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Print count for every word
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_LEN        256
#define MAX_WORD_COUNT      128
#define MAX_WORD_LEN        16

#define INCORRECT_INPUT     1
#define INCORRECT_WORD_LEN  2
#define INCORRECT_LINE_LEN  3


typedef struct
{
    const char *word;
    size_t count;
} words_t;

/**
 * @param[out] array Result word array
 * @return Word count or error code 
 * @breif Get words from sdtin
 */
int get_words(char array[][MAX_WORD_LEN + 1], size_t *word_count)
{
    size_t line_len = 0;
    size_t word_len = 0;
    char word[MAX_WORD_LEN] = "";

    *word_count = 0;
    for (char elem; (elem = getchar()) != '\n'; line_len++)
    {
        if (line_len >= MAX_LINE_LEN)
            return INCORRECT_LINE_LEN;
        else if (ispunct(elem) || isspace(elem))
        {
            if (word_len > MAX_WORD_LEN)
                return INCORRECT_WORD_LEN;
            
            if (word_len)
            {
                strncpy(array[*word_count], word, MAX_WORD_LEN);
                array[(*word_count)++][word_len] = '\0';
                word_len = 0;
            }
        }
        else if (isalpha(elem))
        {
            if (word_len >= MAX_WORD_LEN)
                return INCORRECT_WORD_LEN;
            
            word[word_len++] = elem;
        }
    }
    
    if (word_len)
    {
        strncpy(array[*word_count], word, MAX_WORD_LEN);
        array[(*word_count)++][word_len] = '\0';
        word_len = 0;
    }

    return *word_count == 0;
}

/**
 * @param[out]  result      Array of pair { word, count }
 * @param[in]   word_array  Array of words
 * @param[in]   word_count  Count words
 * @return  Lenght `result`
 * @breif   Fill `result` array and return lenght
 */
size_t find_word_count(words_t *result, 
char word_array[][MAX_WORD_LEN + 1], 
const size_t word_count)
{
    size_t result_count = 0;
    size_t count_same;
    bool in_result;
    
    for (size_t i = 0; i < word_count; i++)
    {
        in_result = false;
        
        for (size_t j = 0; j < result_count && !in_result; j++)
            if (!strncmp(word_array[i], result[j].word, MAX_WORD_LEN))
                in_result = true;

        count_same = 0;
    
        for (size_t j = i; j < word_count && !in_result; j++)
            if (!strncmp(word_array[i], word_array[j], MAX_WORD_LEN))
                count_same++;

        if (!in_result)
        {
            words_t new = { word_array[i], count_same };
            result[result_count++] = new;
        }
    }

    return result_count;
}

/**
 * @param[in] result        Array of pair { word, count }
 * @param[in] word_count    Count of result
 * @breif Print result array
 */
void print_result(const words_t *result, const size_t word_count)
{
    printf("Result: ");
   
    for (size_t i = 0; i < word_count; i++)
        printf("%s %zu\n", result[i].word, result[i].count);
}

int main(void)
{
    int return_code = EXIT_SUCCESS;
    char word_array[MAX_WORD_COUNT][MAX_WORD_LEN + 1] = { '\0' };
    words_t result[MAX_WORD_COUNT];
    size_t word_count;

    if ((return_code = get_words(word_array, &word_count)))
        return return_code;

    size_t result_count = find_word_count(result, word_array, word_count);
    print_result(result, result_count);

    return return_code;
}
