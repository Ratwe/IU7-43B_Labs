/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Calculating by formula
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @param[out] res Result value
 * @return Success flag
 * @brief Calc function
 */
int calc_input(double *res)
{ 
    double input, local_res = 0;
    int i = 0;
    
    do
    {
        printf("Enter value: ");
        if (scanf("%lf", &input) < 1)
        {
            return EXIT_FAILURE;
        }
        if (input < 0)
        {
            break;
        }
        i++;
        local_res += input / i;        
    } while (1);
    *res = local_res;
  
    if (i == 0)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}

int main(void)
{
    double res;

    if (calc_input(&res))
    {
        printf("Invalid value\n");
        return EXIT_FAILURE;
    }
    if (res < 0)
    {
        printf("Sum is negative\n");
        return EXIT_FAILURE;
    }
    printf("Result: %.6lf", sqrt(res));
    return EXIT_SUCCESS;
}

