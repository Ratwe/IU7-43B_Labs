#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define WRONG_INPUT 101
#define EXPECTED_NUMBER_FROM_INPUT 1
#define N 32

uint32_t swap_bits(uint32_t num)
{
	return ((num & 0x55555555) << 1 | ((num & 0xAAAAAAAA) >> 1));
}

void print_bin(uint32_t num)
{
	uint32_t last = (UINT_MAX >> 1) + 1;
	for (int i = 0; i < N; i++)
	{
		printf("%u", (num & last) != 0);
		last >>= 1;
	}
	printf("\n");
}

int main(void)
{
	uint32_t num;
	printf("Enter num: ");
	if (scanf("%u", &num) != EXPECTED_NUMBER_FROM_INPUT)
	{
		printf("Error: ");
		return WRONG_INPUT;
	}
		
	printf("Result: ");
	print_bin(swap_bits(num));
	
	return EXIT_SUCCESS;
}
