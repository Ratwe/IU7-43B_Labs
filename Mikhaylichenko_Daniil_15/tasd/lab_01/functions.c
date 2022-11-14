#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "defines.h"
#include "functions.h"

void print_d(my_double num)
{
    printf("Double:\n");
    printf("Sign = %d\n", num.sign);
    //printf("Sign = %d, exp sign = %d\n", num.sign, num.exp_sign);
    printf("Exp = %d\n", num.exp);
    printf("LEN = %zu\n", num.str_len); 
    for (uint8_t i = 0; i < MANTISSA_LEN * 2; i++)
        printf("%u|", num.mantissa[i]);
    printf("\n\n");
}

// Функция проверки, что число равно нулю (массив из нулей)
bool is_zero(uint8_t num[])
{
    int counter = 0;
    for (int i = 0; i < MANTISSA_LEN * 2; i++)
        if (num[i] == 0)
            counter++;

    if (counter == MANTISSA_LEN * 2)
        return true;

    return false;
}

// Функция сравнения двух чисе: >= или <
bool is_bigger(uint8_t first_num[], uint8_t second_num[])
{
    for (int i = 0; i < MANTISSA_LEN * 2 - 1; i++)
        if (first_num[i] < second_num[i])
            return false;
        else if (first_num[i] > second_num[i])
            break;

    return true;
}

// Функция вычитания двух чисел
void substract_nums(uint8_t first_num[], uint8_t second_num[])
{
    for (int i = MANTISSA_LEN * 2 - 1; i >= 0; i--)
    {
        if (first_num[i] >= second_num[i])
            first_num[i] -= second_num[i];
        else
        {
            first_num[i - 1]--;
            first_num[i] = first_num[i] + 10 - second_num[i];
        }
    }        
}

// Функция сдвига всех чисел в массиве на одну позицию
void shift_num(uint8_t num[])
{
    for (int i = MANTISSA_LEN * 2 - 1; i >= 0; i--)
        num[i] = num[i - 1];

    num[0] = 0;
}

// Функция округления числа
void round_num(my_double *result)
{
    if (result->mantissa[MANTISSA_LEN] >= 5)
    {
        result->mantissa[MANTISSA_LEN - 1]++;

        for (int i = MANTISSA_LEN - 1; i > 0; i--)
            if (result->mantissa[i] >= 10)
            {
                result->mantissa[i - 1]++;
                result->mantissa[i] -= 10;
            }

        if (result->mantissa[0] >= 10)
        {
            result->mantissa[0] -= 10;
            shift_num(result->mantissa);
            result->mantissa[0] = 1;
            result->exp++;
        }
    }
}

// Функция деления действительного числа на целое
int divide(my_double *first_num, my_double *second_num, my_double *result)
{
    print_d(*first_num);
    print_d(*second_num);

    if (is_zero(second_num->mantissa))
    {
        ERROR_LOG("DIVISION BY ZERO");
        return DIVISION_BY_ZERO;
    }

    memset(result->mantissa, 0, sizeof(uint8_t) * (MANTISSA_LEN + 1));
    
    result->sign = first_num->sign * second_num->sign;
    result->exp = first_num->exp - second_num->exp + 1;

    if (is_bigger(second_num->mantissa, first_num->mantissa))
    {
        shift_num(second_num->mantissa);
        result->exp--;
    }

    for (int i = 0; i < MANTISSA_LEN + 1; i++)
    {
        for (; is_bigger(first_num->mantissa, second_num->mantissa); result->mantissa[i]++)
            substract_nums(first_num->mantissa, second_num->mantissa);

        shift_num(second_num->mantissa);
    }

    round_num(result);
      
    return EXIT_SUCCESS;
}

// Функция вывода числа
void print_result(my_double *result)
{
    print_d(*result);

    printf("Result = ");

    if (is_zero(result->mantissa))
    {
        printf("0\n");
        return;
    }

    switch (result->sign)
    {
        case IS_POSITIVE:
            printf("+");
            break;
        case IS_NEGATIVE:
            printf("-");
            break;
    }

    printf("0.");

    int real_len = 0;

    for (int i = 0; i < MANTISSA_LEN; i++)
        if (result->mantissa[i] > 0)
            real_len++;

    for (int i = 0; i < real_len + 1; i++)
        printf("%d", result->mantissa[i]);

    if (result->exp != 0)
        printf("%s%d", (result->exp > 0) ? "E+" : "E", result->exp);

    printf("\n");
}
