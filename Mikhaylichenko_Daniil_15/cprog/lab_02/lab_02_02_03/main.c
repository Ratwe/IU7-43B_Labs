#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WRONG_INPUT 101
#define OUT_OF_ARRAY_RANGE 102
#define NO_ARMSTRONG_NUMBERS 103
#define EXPECTED_NUMBER_FROM_INPUT 1
#define IT_IS_ARMSTRONG 1
#define IT_IS_NOT_ARMSTRONG 0
#define CHECK_FAIL 0
#define CHECK_PASS 1
#define N 10
#define EPS 1e-7

int fill_array(int arr[], size_t len);
int fill_arm_array(int arm_arr[], int arr[], size_t len);
int calc_len(int num);
int armstrong(int num);

int main(void)
{
	int arr[N];
	
	size_t len;
	printf("Enter array's len: ");
	if (scanf("%lu", &len) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
	if (len > N || len <= 0)
		return OUT_OF_ARRAY_RANGE;
	
	char check = fill_array(arr, len);
	if (check != 1)
		return WRONG_INPUT;
	
	int arm_arr[N];
	int arm_len = fill_arm_array(arm_arr, arr, len);
	
	if (arm_len > 0)
	{
		for (int i = 0; i < arm_len; i++)
			printf("%d\n", arm_arr[i]);
	}
	else
		return NO_ARMSTRONG_NUMBERS;
	
	return EXIT_SUCCESS;
}

int fill_array(int arr[], size_t len)
{
	int num;
	
	for (size_t i = 0; i < len; i++)
	{
		printf("Enter new num: ");
		if (scanf("%d", &num) != EXPECTED_NUMBER_FROM_INPUT)
			return CHECK_FAIL;
			
		arr[i] = num;
	}
	
	return CHECK_PASS;
}

int fill_arm_array(int arm_arr[], int arr[], size_t len)
{
	int count = 0;
	
	for (size_t i = 0; i < len; i++)
	{
		if (armstrong(arr[i]) && arr[i] > 0)
		{
			arm_arr[count] = arr[i];
			count++;
		}
	}
	
	return count;
}

int calc_len(int num)
{
	int count = 0;
	
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	
	return count;
}

int armstrong(int num)
{
	int num_len;
	num_len = calc_len(num);
	
	double sum = 0;
	int number, temp = num;
	
	while (temp != 0)
	{
		number = temp % 10;
		sum += pow(number, num_len);
		temp /= 10;
	}
	
	if (fabs(sum - num) < EPS)
		return IT_IS_ARMSTRONG;
	else
		return IT_IS_NOT_ARMSTRONG;
}
