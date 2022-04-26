/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Calc error rate e^x function
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @param[in] x Approximation base
 * @paran[in] e Error rate
 * @return Appoximated value
 * @brief Find approximated value e^x
 */
double approximate(double x, double e)
{
    double result;
    double local_res;

    local_res = 1;
    result = local_res;
    for (int i = 0; fabs(local_res) >= e; i++)
    {
        local_res *= x / (i + 1);
        result += local_res;
    }
    return result;
}

int main(void)
{
    double x, e;
    double real_value, app_value; 
    double absol, rel;

    printf("Enter x: ");
    if (scanf("%lf", &x) < 1)
    {
        printf("Wrong x");
        return EXIT_FAILURE;
    }
    printf("Enter e: ");
    if (scanf("%lf", &e) < 1 || e <= 0 || e > 1)
    {
        printf("Wrong e");
        return EXIT_FAILURE;
    }

    real_value = exp(x);
    app_value = approximate(x, e);
    absol = fabs(real_value - app_value);
    rel = fabs(absol / real_value);
    printf("s(x) = %.6lf\nf(x) = %.6lf\n", app_value, real_value); 
    printf("Absolute: %.6lf\n", absol);
    printf("Relative: %.6lf\n", rel);
    return EXIT_SUCCESS;
}

