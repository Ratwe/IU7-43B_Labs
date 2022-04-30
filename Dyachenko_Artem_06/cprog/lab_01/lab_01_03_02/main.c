#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float r1, r2, r3, r;
    
    scanf("%f%f%f", &r1, &r2, &r3);

    r = 1 / (1 / r1 + 1 / r2 + 1 / r3);

    printf("%f\n", r);
    
    return EXIT_SUCCESS;
}
