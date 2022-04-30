#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT 101
#define OUT_OF_ARRAY_RANGE 102
#define EXPECTED_NUMBER_FROM_INPUT 1
#define RIGHT_INPUT 0
#define MAX_SIZE 20
#define RADIX 10

int enter_len(size_t *plen);
int fill_array(int arr[], size_t len);
size_t add_reverse(int arr[], size_t len);
void move_elements(int arr[], size_t index);
int reverse(int num);
void print_array(int arr[], size_t arm_len);

int main(void)
{
	int arr[MAX_SIZE] = { 0 };
	
	size_t len;
	int check = enter_len(&len);
	if (check != EXIT_SUCCESS)
		return check;
	
	check = fill_array(arr, len);
	if (check != EXIT_SUCCESS)
		return check;
	
	size_t new_len = add_reverse(arr, len);
	print_array(arr, new_len);
	
	return EXIT_SUCCESS;
}

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

size_t add_reverse(int arr[], size_t len)
{
	size_t count = len;
	
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		if (arr[i] > 0)
		{
			move_elements(arr, i + 1);
			count++;
		}
	}
	
	size_t i = 0;
	
	while (i < count)
	{
		if (arr[i] > 0)
		{
			arr[i + 1] = reverse(arr[i]);
			i++;
		}
		i++;
	}
	
	return count;
}

void move_elements(int arr[], size_t index)
{
	for (size_t i = MAX_SIZE; i > index; i--)
		arr[i] = arr[i - 1];
		
	arr[index] = 0;
}

int reverse(int num)
{
	int reverse_num = 0;
	
	while (num > 0)
	{
		reverse_num = RADIX * reverse_num + (num % RADIX);
		num /= RADIX;
	}
	
	return reverse_num;
}

void print_array(int arr[], size_t len)
{
	for (size_t i = 0; i < len; i++)
		printf("%d\n", arr[i]);
}
