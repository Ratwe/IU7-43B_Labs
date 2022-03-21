#include <stdio.h>

#define EVEN_NUMBER 0
#define ODD_NUMBER 1

int global_initialised = 1;
int global_non_initialised;

int main(void)
{
	int a;
	printf("Введите число: ");
	scanf("%d", &a);
	
	if (a % 2 == 0)
	{
		printf("Число чётное.\n");
		return EVEN_NUMBER;
	}
	else
	{
		printf("Число нечётное.\n");
		return ODD_NUMBER;
	}
}
