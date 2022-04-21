#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535
#define RADIANS_PER_DEEGREE 180
#define TO_RADIANS PI / RADIANS_PER_DEEGREE

int main(void)
{
	double first_side, second_side, angle;
	
	printf("Enter first side: ");
	scanf("%lf", &first_side);
	
	printf("Enter second side: ");
	scanf("%lf", &second_side);
	
	printf("Enter angle: ");
	scanf("%lf", &angle);
	
	angle *= TO_RADIANS;
	
	double square = 0.5 * first_side * second_side * sin(angle);
	
	printf("Square = %.6lf\n", square);
	
	return EXIT_SUCCESS;
}
