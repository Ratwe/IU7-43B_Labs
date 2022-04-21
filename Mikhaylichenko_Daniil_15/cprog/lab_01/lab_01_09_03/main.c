#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define WRONG_SEQUENCE 101
#define EXPECTED_NUMBER_FROM_INPUT 1
#define EPS 1e-7f

double calc_sequence_function(void)
{
	double value = 1;
	for (int i = 1; ; i++)
	{
		double x;
		printf("Enter new value: ");
		if (scanf("%lf", &x) != EXPECTED_NUMBER_FROM_INPUT || (x < 0 && i == 1))
			return -1;
			
		if (x < 0)
			return value;
			
		value *= (x + i);
	}
}

int main(void)
{
	double value = calc_sequence_function();
	
	if (value < 0)
		return WRONG_SEQUENCE;
	
	printf("%lf\n", exp(1 / value));
	
	return EXIT_SUCCESS;
}

