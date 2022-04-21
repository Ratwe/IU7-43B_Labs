#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	double velocity, acceleration, time;
	
	printf("Enter start speed: ");
	scanf("%lf", &velocity);
	
	printf("Enter acceleration: ");
	scanf("%lf", &acceleration);
	
	printf("Enter time: ");
	scanf("%lf", &time);
	
	double movement = (velocity * time) + (acceleration * pow(time, 2) / 2);
	printf("Movement = %.6lf\n", movement);
	
	return EXIT_SUCCESS;
}
