/**
 * @file
 * @author  Kuznetsov Egor IU7-23B
 * @breif   Edit input line
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LEN        256
#define MAX_WORD_COUNT      128
#define MAX_WORD_LEN        16
#define SPLITERS            ",.-:;!?"

#define EMPTY_RESULT        4
#define INCORRECT_WORD_LEN  3
#define INCORRECT_LINE_LEN  2
#define INCORRECT_INPUT     1

/**
 * @param[out] str String to strip
 * @breif Sprip `str`
 */
void strip_line(char *const str)
{
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}
/**
 * @param[out]  destination String to fill
 * @param[in]   max_count   Max line lenght
 * @return  Error code
 * @breif   Fill `destination` line
 */
int get_line(char *const destination, const size_t max_count)
{
    if (fgets(destination, max_count, stdin) == NULL)
        return INCORRECT_INPUT;
    
    if (strlen(destination) > MAX_LINE_LEN || strlen(destination) < 1)
        return INCORRECT_LINE_LEN;
    
    if (destination[0] == '\n')
        return INCORRECT_LINE_LEN;
    
    strip_line(destination);

    return EXIT_SUCCESS;
}

/**
 * @param[out]  words   Result word array
 * @param[out]  count   Word count
 * @param[in]   source  Source line
 * @return  Error code 
 * @breif   Get words from sdtin
 */
int split_words(char words[][MAX_WORD_LEN + 1], size_t *const count, const char *source)
{
    size_t word_len = 0;
    
    *count = 0;
    for (const char *w = source; *w; w++)
    {
        if (strchr(SPLITERS, *w) != NULL || isspace(*w))
        {
            if (word_len > MAX_WORD_LEN)
                return INCORRECT_WORD_LEN;
            
            if (word_len)
            {
                words[(*count)++][word_len] = '\0';
                word_len = 0;
            }
        }
        else
            words[*count][word_len++] = *w;
    }
    
    if (word_len)
        words[(*count)++][word_len] = '\0';

    return EXIT_SUCCESS;
}

/**
 * @param[in]   words       Words array
 * @param[in]   word_count  Lenght words array
 * @param[out]  new_str     Destination strings
 * @breif Fill `new_str` from `words`
 */
void form_new_string(char words[][MAX_WORD_LEN + 1], const size_t word_count, char *new_str)
{
    strncpy(new_str, "", MAX_LINE_LEN);

    for (int i = word_count - 2; i >= 0; i--)
        if (strncmp(words[i], words[word_count - 1], MAX_WORD_LEN))
        {
            char new_word[MAX_WORD_LEN] = "";
            size_t new_word_len = 1;

            new_word[0] = words[i][0];
            
            for (size_t j = 1; words[i][j] != '\0'; j++)
                if (words[i][0] != words[i][j])
                    new_word[new_word_len++] = words[i][j];
            
            new_word[new_word_len] = '\0';
   
            if (strlen(new_str))
                strncat(new_str, " ", MAX_WORD_LEN);
            
            strncat(new_str, new_word, MAX_WORD_LEN);
        }
}

int main(void)
{
    int return_code = EXIT_SUCCESS;
    char input_line[MAX_LINE_LEN + 2] = "";
    char words[MAX_WORD_COUNT][MAX_WORD_LEN + 1] = { '\0' };
    char new_str[MAX_LINE_LEN];
    size_t word_count = 0;

    if ((return_code = get_line(input_line, MAX_LINE_LEN + 2)))
        return return_code;
    
    if ((return_code = split_words(words, &word_count, input_line)))
        return return_code;

    if (word_count == 0)
        return INCORRECT_INPUT;

    form_new_string(words, word_count, new_str);
        
    if (!strlen(new_str))
        return EMPTY_RESULT;

    printf("Result: %s\n", new_str);

    return return_code;
}
