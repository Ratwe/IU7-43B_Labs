/**
 * @file
 * @author Kuznetov Egor IU7-23B
 * @brief Find count bottles by count coins
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int coins;
    int bottles;

    printf("Enter count coins: ");
    scanf("%d", &coins);
    
    if (coins >= 45)
    {
        bottles = coins / 25 - 1;
        if (coins % 25 >= 20)
        {
            bottles++;
        }
    }
    else
    {
        bottles = 0;
    }
    printf("Count bottles: %d\n", bottles);
    return EXIT_SUCCESS;
}

