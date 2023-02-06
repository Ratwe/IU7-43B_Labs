#ifndef __PRODUCTS__H__
#define __PRODUCTS__H__

#define NAME_SIZE 30
#define MANU_SIZE 15

#include <stdint.h>

typedef struct
{
    char name[NAME_SIZE + 1];
    char manu[MANU_SIZE + 1];
    uint32_t cost;
    uint32_t count;
} product_t;

int sort_products(char *filename_src, char *filename_dest);

int print_products(char *filename, char *substr);

int print_all_products(char *filename);

int insert_product(char *filename);

#endif
