#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    float x = 0;
    float sum = 0;
    int n = 0;

    while (1)
    {
        scanf("%f", &x);
        if (x < 0)
            break;

        sum += sqrtf(++n + x);
        #ifdef DEBUG
            printf("[DB]: sum = %f\n", sum);
        #endif
    }

    if (n == 0)
        return EXIT_FAILURE;

    float g_x = sum / n;
    printf("%f\n", g_x);

    return EXIT_SUCCESS;
}
