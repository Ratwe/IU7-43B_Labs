#define DIVIDER 60

#include <stdio.h>
#include <stdlib.h>

#define SECS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60

int main(void)
{
    int secs;
    int minutes, hours;
    
    scanf("%i", &secs);

    minutes = secs / SECS_PER_MINUTE;
    secs %= SECS_PER_MINUTE;
    hours = minutes / MINUTES_PER_HOUR;
    minutes %= MINUTES_PER_HOUR;

    printf("%i %i %i \n", hours, minutes, secs);
    
    return EXIT_SUCCESS;
}
