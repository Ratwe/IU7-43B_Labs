#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT 101
#define NOT_NATURAL_NUMBER 102
#define EXPECTED_NUMBER_FROM_INPUT 2

int find_min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

int calc_greatest_common_divisor(int first_number, int second_number)
{
	int min_num = find_min(first_number, second_number);
	
	while ((first_number % min_num != 0) || (second_number % min_num != 0))
		min_num--;
		
	return min_num;
}

int main(void)
{
	int first_number, second_number;
	
	printf("Enter first and second numbers: ");
	if (scanf("%d%d", &first_number, &second_number) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
		
	if (first_number <= 0 || second_number <= 0)
		return NOT_NATURAL_NUMBER;
		
	printf("greatest_common_divisor = %d\n", calc_greatest_common_divisor(first_number, second_number));
	
	return EXIT_SUCCESS;
}
