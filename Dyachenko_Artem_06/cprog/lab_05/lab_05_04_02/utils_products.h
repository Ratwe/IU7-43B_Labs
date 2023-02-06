#ifndef __UTILS__PRODUCTS__H__
#define __UTILS__PRODUCTS__H__

#include "products.h"

void print_product(product_t product);

int scan_product(product_t *product);

int find_place_to_insert(FILE *f, product_t product);

int swap_products(FILE *f, int pos1, int pos2);

int move_products_right(FILE *f, int pos);

int same_end(char *name, char *substr);

#endif
