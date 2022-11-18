#include "defines.h"
#include "process.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int process(FILE *f, unsigned int *max_len)
{
    int counter = 1;
    int prev_num, temp;

    char pos_seq;

    printf("Enter nums: ");
    if (fscanf(f, "%d", &prev_num) != EXPECTED_NUMBER)
        return WRONG_INPUT;

    if (fscanf(f, "%d", &temp) != EXPECTED_NUMBER)
        return WRONG_INPUT;

    if (temp > prev_num)
        pos_seq = TRUE;
    else if (temp < prev_num)
        pos_seq = FALSE;
    else
    {
        pos_seq = EQUAL;
        --counter;
    }

    counter++;
    prev_num = temp;

    for (;fscanf(f, "%d", &temp) == EXPECTED_NUMBER; prev_num = temp)
    {
        if (temp > prev_num && pos_seq == TRUE)
            counter++;
        else if (temp > prev_num && (pos_seq == FALSE || pos_seq == EQUAL))
        {
            *max_len = max(*max_len, counter);

            counter = 2;
            pos_seq = TRUE;
        }
        else if (temp < prev_num && pos_seq == FALSE)
            counter++;
        else if (temp < prev_num && (pos_seq == TRUE || pos_seq == EQUAL))
        {
            *max_len = max(*max_len, counter);

            counter = 2;
            pos_seq = FALSE;
        }
        else
        {
            *max_len = max(*max_len, counter);
             
            counter = 1;
            pos_seq = EQUAL;
        }
    }

    *max_len = max(*max_len, counter);

    if (*max_len == 1)
        *max_len = 0;

    return RIGHT_INPUT;
}
