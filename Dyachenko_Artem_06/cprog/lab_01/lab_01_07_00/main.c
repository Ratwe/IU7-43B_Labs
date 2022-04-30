#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EXPECTED_INPUT 1

// подсчёт s(x)
double calc_s_x(double x, double e)
{
    double res = 1, cur = 1;

    for (int i = 1; fabs(cur) >= e; i++)
    {
        cur *= x / i;
        res += cur;
    }

    return res;
}

int main(void)
{
    double x, e;
    
    int rc = scanf("%lf", &x);
    
    if (rc < EXPECTED_INPUT)
        return EXIT_FAILURE;
        
    rc = scanf("%lf", &e);
    
    if (rc < 1 || e > 1 || e <= 0)
        return EXIT_FAILURE;

    double f_x, s_x, delta, omega;
    
    f_x = exp(x);
    s_x = calc_s_x(x, e);
    delta = fabs(f_x - s_x);
    omega = fabs(f_x - s_x) / fabs(f_x);

    printf("%.6lf %.6lf %.6lf %.6lf\n", s_x, f_x, delta, omega);

    return EXIT_SUCCESS;
}
