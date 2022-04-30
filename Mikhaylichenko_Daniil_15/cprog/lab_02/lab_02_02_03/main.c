#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WRONG_INPUT 101
#define OUT_OF_ARRAY_RANGE 102
#define NO_ARMSTRONG_NUMBERS 103
#define RIGHT_INPUT 0
#define EXPECTED_NUMBER_FROM_INPUT 1
#define IT_IS_ARMSTRONG 1
#define IT_IS_NOT_ARMSTRONG 0
#define MAX_SIZE 10
#define EPS 1e-7
#define RADIX 10

int enter_len(size_t *plen);
int fill_array(int arr[], size_t len);
size_t fill_arm_array(int arm_arr[], int arr[], size_t len);
int calc_len(int num);
int armstrong(int num);
void print_array(int arm_arr[], size_t arm_len);

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
	
	int arm_arr[MAX_SIZE];
	size_t arm_len = fill_arm_array(arm_arr, arr, len);
	
	if (arm_len <= 0)
		return NO_ARMSTRONG_NUMBERS;
		
	print_array(arm_arr, arm_len);
	
	return EXIT_SUCCESS;
}

int enter_len(size_t *plen)
{
	printf("Enter array's len: ");
	if (scanf("%lu", plen) != EXPECTED_NUMBER_FROM_INPUT)
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

size_t fill_arm_array(int arm_arr[], int arr[], size_t len)
{
	size_t count = 0;
	
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
		num /= RADIX;
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
		number = temp % RADIX;
		sum += pow(number, num_len);
		temp /= RADIX;
	}
	
	if (fabs(sum - num) < EPS)
		return IT_IS_ARMSTRONG;
	
	return IT_IS_NOT_ARMSTRONG;
}

void print_array(int arr[], size_t len)
{
	for (size_t i = 0; i < len; i++)
		printf("%d\n", arr[i]);
}
