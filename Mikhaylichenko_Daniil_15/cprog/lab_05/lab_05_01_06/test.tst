#include "defines.h"
#include "process.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int process(FILE *f, unsigned int *max_len)
{
	int counter = 0, pos_counter = 0, neg_counter = 0;



	for (int temp; fscanf(f, "%d", &temp) == EXPECTED_NUMBER; prev_num2 = prev_num1, prev_num1 = temp)
	{
		if (counter == 0)
		{
			
		}
	}

    return RIGHT_INPUT;
}
