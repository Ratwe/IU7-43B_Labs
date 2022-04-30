#include <stdio.h>
#include <stdlib.h>

#define OUT_OF_ARRAY_RANGE 101
#define TOO_MANY_VALUES 100
#define EXPECTED_NUMBER_FROM_INPUT 1
#define MAX_SIZE 10

int fill_array(int arr[]);
void bubble_sort(int arr[], size_t len);
void print_array(int arr[], size_t len);

int main(void)
{
	int arr[MAX_SIZE];
	
	size_t len = fill_array(arr);

	if (len == 0)
		return OUT_OF_ARRAY_RANGE;
		
	if (len > MAX_SIZE)
	{
		bubble_sort(arr, len - 1);
		print_array(arr, len - 1);
		return TOO_MANY_VALUES;
	}
	
	bubble_sort(arr, len);
	print_array(arr, len);
	return EXIT_SUCCESS;
}

int fill_array(int arr[])
{
	int count = 0;
	int num;
	while (count <= MAX_SIZE)
	{
		printf("Enter new num: ");
		if (scanf("%d", &num) != EXPECTED_NUMBER_FROM_INPUT)
			return count;
		
		count++;
		
		if (count > MAX_SIZE)
			break;
			
		arr[count - 1] = num;
	}
	
	return count;
}

void bubble_sort(int arr[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		for (size_t j = 0; j < len - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void print_array(int arr[], size_t len)
{
	for (size_t i = 0; i < len; i++)
		printf("%d\n", arr[i]);
}
