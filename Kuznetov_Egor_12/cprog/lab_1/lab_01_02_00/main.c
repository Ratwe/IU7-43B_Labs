/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Calculating perimeter by sides and heigth
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double a, b, h;
    double p;
    double temp;
    
    printf("Enter length base a: ");
    scanf("%lf", &a);
    printf("Enter length base b: ");
    scanf("%lf", &b);
    printf("Enter height: ");
    scanf("%lf", &h);
    
    temp = (b - a) / 2;
    p = a + b + 2 * sqrt(temp * temp + h * h); 
    printf("Perimeter: %.6lf\n", p);
    return EXIT_SUCCESS;
}

