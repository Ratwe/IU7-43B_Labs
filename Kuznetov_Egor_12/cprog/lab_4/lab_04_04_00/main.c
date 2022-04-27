/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Check line for compliance to IP
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LEN        256
#define MAX_WORD_COUNT      128
#define MAX_WORD_LEN        16

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
    
    if (strlen(destination) == (max_count - 1) && destination[max_count - 2] != '\n')
        return INCORRECT_LINE_LEN;
    
    strip_line(destination);

    return EXIT_SUCCESS;
}

/**
 * @param[in] source Source string
 * @return  Striped source string
 * @breif   Remove spaces from start and from end
 */
char *clear_space(char *source)
{
    while (isspace(*source))
        source++;
    
    char *temp_source = source;
    
    source = source + strlen(source) - 1;
    
    while (isspace(*source))
        source--;
   
    *(source + 1) = '\0';

    return temp_source;
}

/**
 * @param[in] source Source string
 * @return `true` if `source` have ONLY IP adress, else `false`
 * @breif Check `source` to IP
 */
bool have_ip(const char *source)
{
    int value = 0;
    size_t count_mask = 0;
    size_t count_value = 0;

    while (*source != '\0')
    {
        if (isdigit(*source))
        {
            count_value++;
            value *= 10;
            value += (*source) - '0';
            
            if (value > 255 || count_value > 3)
                return false;
        }
        else if (*source == '.')
        {
            if (!count_value)
                return false;

            count_value = 0;
            count_mask++;
            value = 0;
        }
        else
            return false;

        source++;
    }

    if (count_value)
        count_mask++;

    if (count_mask != 4)
        return false;
    
    return true;
}

int main(void)
{
    int return_code = EXIT_SUCCESS;
    char line[MAX_LINE_LEN + 1] = "";

    if ((return_code = get_line(line, MAX_LINE_LEN)))
        return return_code;
    
    printf(have_ip(clear_space(line)) ? "YES\n" : "NO\n");

    return return_code;
}
