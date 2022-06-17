#include <string.h>
#include "functions.h"

int enter_string(char str[], size_t max_len)
{
    size_t str_len = 0;

    for (char symbol; (symbol = getchar()) != '\n' && symbol != EOF;)
    {
        if (str_len < max_len - 1)
            str[str_len++] = symbol;
        else
            return TOO_LONG_STR;
    }

    str[str_len] = '\0';

    if (str[0] == '\0')
        return EMPTY_STRING;

    return RIGHT_INPUT;
}

int enter_num(uint32_t *num)
{
    if (scanf("%u", num) != EXPECTED_NUMBER)
        return WRONG_INPUT;

    return RIGHT_INPUT;
}

int get_struct_by_pos(FILE *file, size_t pos, s_product *product)
{
    fseek(file, pos * sizeof(*product), SEEK_SET);

    if (fread(product, sizeof(*product), EXPECTED_NUMBER, file) != EXPECTED_NUMBER)
        return WRONG_STR;

    return RIGHT_STR;
}

void put_struct_by_pos(FILE *file, size_t pos, s_product *product)
{
    fseek(file, pos * sizeof(*product), SEEK_SET);
    fwrite(product, sizeof(*product), EXPECTED_NUMBER, file);
}

bool compare_strings(char str1[], char str2[])
{
    bool is_substr = true;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    for (size_t i = 1; i <= len2; i++)
        if (str1[len1 - i] != str2[len2 - i])
            is_substr = false;

    return is_substr;
}

void print_struct(s_product product)
{
    printf("%s\n%s\n%u\n%u\n", product.name, product.manufacturer, product.price, product.product_counter);
}