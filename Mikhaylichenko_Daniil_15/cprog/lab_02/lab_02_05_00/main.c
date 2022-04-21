#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT 101
#define OUT_OF_ARRAY_RANGE 102
#define EXPECTED_NUMBER_FROM_INPUT 1
#define CHECK_PASS 1
#define CHECK_FAIL 0
#define N 10

int fill_array(int *pbeg, int *pend);
int find_max(int *pbeg, int *pend);

int main(void)
{
	int a[N];
	
	size_t len;
	printf("Enter array's len: ");
	if (scanf("%lu", &len) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
	if (len > 10 || len <= 0)
		return OUT_OF_ARRAY_RANGE;
		
	int *pbeg = a;
	int *pend = pbeg + len;
	
	int check = fill_array(pbeg, pend);
	if (check != 1)
		return WRONG_INPUT;
	
	printf("%d\n", find_max(pbeg, pend));
	
	return EXIT_SUCCESS;
}

int fill_array(int *pbeg, int *pend)
{
	do
	{
		int num;
		printf("Enter new num: ");
		if (scanf("%d", &num) != EXPECTED_NUMBER_FROM_INPUT)
			return CHECK_FAIL;
		
		*pbeg = num;
		pbeg++;
	}
	while (pbeg != pend);
	
	return CHECK_PASS;
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
