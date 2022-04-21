#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WRONG_INPUT 101
#define ARGUMENTS_OUT_OF_RANGE 102
#define EXPECTED_NUMBER_FROM_INPUT 2

double count_sx(double x, double eps)
{
	double s = x;
	
	double cur = 2;
	for (int i = 1, n = 3; fabs(cur) > eps; i++, n += 2)
	{
		cur = pow(-1, i) * pow(x, n) / n;
		
		s += cur;
	}
	
	return s;
}

void print_errors(double s_x, double f_x)
{
	double delta = fabs(f_x - s_x);
	double sigma = delta / fabs(f_x);
	printf("%lf\n", delta);
	printf("%lf\n", sigma);
}

int main(void)
{
	double x, eps;
	
	printf("Enter x and eps: ");
	if (scanf("%lf%lf", &x, &eps) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
		
	if (eps <= 0 || eps > 1 || fabs(x) > 1)
		return ARGUMENTS_OUT_OF_RANGE;
		
	double f_x = atan(x);
	
	double s_x = count_sx(x, eps);
		
	printf("%lf\n", s_x);
	printf("%lf\n", f_x);
	print_errors(s_x, f_x);
	
	return EXIT_SUCCESS;
}
