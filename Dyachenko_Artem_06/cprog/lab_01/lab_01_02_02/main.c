#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    double x1, y1, x2, y2, x3, y3;
    double a, b, c, p;
    
    scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);

    a = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    b = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
    c = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
    p = a + b + c;

    printf("%.6lf\n", p);

    return EXIT_SUCCESS;
}

