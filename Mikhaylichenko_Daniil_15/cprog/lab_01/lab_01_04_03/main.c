#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define S 10

int mult(int num)
{
	int mult_of_nums = 1;
	
	for (int i = 0; i < N; i++)
	{
		mult_of_nums *= (num % S);
		num /= S;
	}
	
	return mult_of_nums;
}

int main(void)
{
	int num;
	printf("Enter number: ");
	scanf("%d", &num);
		
	printf("%d\n", mult(fabs(num)));
	
	return EXIT_SUCCESS;
}
