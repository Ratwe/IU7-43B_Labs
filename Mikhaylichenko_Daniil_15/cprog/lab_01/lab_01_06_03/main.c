#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WRONG_INPUT 101
#define VERTICAL_LINE 102
#define EXPECTED_NUMBER_FROM_INPUT 6
#define EPS 1e-7
#define ABOVE_THE_LINE 0
#define ON_THE_LINE 1
#define UNDER_THE_LINE 2


double calc_pseudoinner_product(double x_q, double y_q, double x_r, double y_r, double x_p, double y_p)
{
	double x_qr, y_qr, x_qp, y_qp;
	x_qr = x_q - x_r;
	y_qr = y_q - y_r;
	x_qp = x_q - x_p;
	y_qp = y_q - y_p;
	
	return (x_qr * y_qp) - (x_qp * y_qr);
}

int find_position(double x_q, double y_q, double x_r, double y_r, double x_p, double y_p)
{
	if (fabs(x_q - x_r) < EPS && fabs(x_q - x_p) > 0)
		return VERTICAL_LINE;
		
	double pseudoinner_product = calc_pseudoinner_product(x_q, y_q, x_r, y_r, x_p, y_p);
	
	if (fabs(pseudoinner_product) < EPS)
		return ON_THE_LINE;
		
	if (pseudoinner_product > 0)
		return ABOVE_THE_LINE;
		
	return UNDER_THE_LINE;
}

int main(void)
{
	double x_q, y_q, x_r, y_r, x_p, y_p;
	printf("Enter xq, yq, xr, yr, xp, yp: ");
	if (scanf("%lf%lf%lf%lf%lf%lf", &x_q, &y_q, &x_r, &y_r, &x_p, &y_p) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
		
	int position = find_position(x_q, y_q, x_r, y_r, x_p, y_p);
	if (position == VERTICAL_LINE)
		return VERTICAL_LINE;
		
	printf("%d\n", position);
	
	return EXIT_SUCCESS;
}
