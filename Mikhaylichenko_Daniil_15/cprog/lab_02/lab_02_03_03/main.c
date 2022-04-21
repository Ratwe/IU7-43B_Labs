#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT 101
#define OUT_OF_ARRAY_RANGE 102
#define EXPECTED_NUMBER_FROM_INPUT 1
#define CHECK_FAIL 0
#define CHECK_PASS 1
#define N 20

int fill_array(int arr[], size_t len);
int add_reverse(int arr[], size_t len);
void move_elements(int arr[], size_t index);
int reverse(int num);

int main(void)
{
	int arr[N] = { 0 };
	
	size_t len;
	printf("Enter array's len: ");
	if (scanf("%lu", &len) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
	if (len > 10 || len <= 0)
		return OUT_OF_ARRAY_RANGE;
	
	char check = fill_array(arr, len);
	if (check != 1)
		return WRONG_INPUT;
	
	int new_len = add_reverse(arr, len);
	for (int i = 0; i < new_len; i++)
		printf("%d\n", arr[i]);
	
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

int add_reverse(int arr[], size_t len)
{
	int count = len;
	
	for (size_t i = 0; i < 20; i++)
	{
		if (arr[i] > 0)
		{
			move_elements(arr, i + 1);
			count++;
		}
	}
	
	int i = 0;
	
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
	for (size_t i = 20; i > index; i--)
		arr[i] = arr[i - 1];
		
	arr[index] = 0;
}

int reverse(int num)
{
	int reverse_num = 0;
	
	while (num > 0)
	{
		reverse_num = 10 * reverse_num + (num % 10);
		num /= 10;
	}
	
	return reverse_num;
}
