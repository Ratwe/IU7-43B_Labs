#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "defines.h"

typedef struct
{
    char name[NAME_LEN + 1];
    char manufacturer[MANUFACTURER_LEN + 1];
    uint32_t price;
    uint32_t product_counter;
} s_product;

int enter_string(char str[], size_t max_len);
int enter_num(uint32_t *num);
int get_struct_by_pos(FILE *file, size_t pos, s_product *product);
void put_struct_by_pos(FILE *file, size_t pos, s_product *product);
bool compare_strings(char str1[], char str2[]);
void print_struct(s_product product);

#endif // __FUNCTIONS_H__