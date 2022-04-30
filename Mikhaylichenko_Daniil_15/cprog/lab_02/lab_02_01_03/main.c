#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WRONG_INPUT 101
#define OUT_OF_ARRAY_RANGE 102
#define NO_POSITIVE_NUMBERS 103
#define RIGHT_INPUT 0
#define EXPECTED_NUMBER_FROM_INPUT 1
#define MAX_SIZE 10
#define EPS 1e-7

int enter_len(size_t *plen)
{
	printf("Enter array's len: ");
	if (scanf("%zu", plen) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
		
	if (*plen > MAX_SIZE || *plen <= 0)
		return OUT_OF_ARRAY_RANGE;
	
	return RIGHT_INPUT;
}

int fill_array(int arr[], size_t len)
{
	int num;
	
	for (size_t i = 0; i < len; i++)
	{
		printf("Enter new num: ");
		if (scanf("%d", &num) != EXPECTED_NUMBER_FROM_INPUT)
			return WRONG_INPUT;
			
		arr[i] = num;
	}
	
	return RIGHT_INPUT;
}

double calc_geometric_mean(int arr[], size_t len)
{
	int g = 1;
	int count = 0;
	
	for (size_t i = 0; i < len; i++)
	{
		if (arr[i] > 0)
		{
			g *= arr[i];
			count++;
		}
	}
	
	if (count == 0)
		return 0;
		
	return pow(g, 1.0f / count);
}

int main(void)
{
	int arr[MAX_SIZE];
	
	size_t len;
	int check = enter_len(&len);
	if (check != EXIT_SUCCESS)
		return check;
		
	check = fill_array(arr, len);
	if (check != EXIT_SUCCESS)
		return WRONG_INPUT;
		
	double geom_mean = calc_geometric_mean(arr, len);
	if (geom_mean <= EPS)
		return NO_POSITIVE_NUMBERS;
		
	printf("%lf\n", geom_mean);
	
	return EXIT_SUCCESS;
}
