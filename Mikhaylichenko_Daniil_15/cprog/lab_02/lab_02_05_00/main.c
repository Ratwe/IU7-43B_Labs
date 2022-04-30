#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT 101
#define OUT_OF_ARRAY_RANGE 102
#define RIGHT_INPUT 0
#define EXPECTED_NUMBER_FROM_INPUT 1
#define MAX_SIZE 10

int enter_len(size_t *plen);
int fill_array(int *pbeg, int *pend);
int find_max(int *pbeg, int *pend);

int main(void)
{
	int arr[MAX_SIZE];
	
	size_t len;
	int check = enter_len(&len);
	if (check != EXIT_SUCCESS)
		return check;
		
	int *pbeg = arr;
	int *pend = pbeg + len;
	
	check = fill_array(pbeg, pend);
	if (check != EXIT_SUCCESS)
		return WRONG_INPUT;
	
	printf("%d\n", find_max(pbeg, pend));
	
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

int fill_array(int *pbeg, int *pend)
{
	do
	{
		int num;
		printf("Enter new num: ");
		if (scanf("%d", &num) != EXPECTED_NUMBER_FROM_INPUT)
			return WRONG_INPUT;
		
		*pbeg = num;
		pbeg++;
	}
	while (pbeg != pend);
	
	return RIGHT_INPUT;
}

int find_max(int *pbeg, int *pend)
{
	int max = *pbeg + *(pend - 1);
	
	do
	{
		int temp = *pbeg + *(pend - 1);
		
		if (temp > max)
			max = temp;
		
		pbeg++;
		pend--;
	}
	while (pbeg <= pend);
	
	return max;
}
