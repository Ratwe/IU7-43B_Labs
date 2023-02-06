#include <stdio.h>
#include <stdbool.h>

#include "defines.h"
#include "products.h"
#include "utils.h"
#include "utils_products.h"

int sort_products(char *filename_src, char *filename_dest)
{
    FILE *f_src = fopen(filename_src, "rb+");
    FILE *f_dest = fopen(filename_dest, "wb+");

    if (!f_src || !f_dest)
        return OPEN_FILE_ERROR;

    int n;
    int rc;

    if (get_size(f_src, &n) || !n)
        return NO_ELEMS_ERROR;

    if ((rc = copy_file(f_src, f_dest)))
        return rc;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if ((rc = swap_products(f_dest, j, j + 1)))
                return rc;

    if (fclose(f_src) || fclose(f_dest))
        return FCLOSE_ERROR;

    return EXIT_SUCCESS;
}

int print_products(char *filename, char *substr)
{
    FILE *f = fopen(filename, "rb");

    if (!f)
        return OPEN_FILE_ERROR;

    product_t product;
    int flag = 0;

    while (fread(&product, SIZE, 1, f) == READ_ELEM_COUNT)
    {
        if (same_end(product.name, substr))
        {
            print_product(product);
            flag = 1;
        }
    }

    if (fclose(f))
        return FCLOSE_ERROR;

    if (!flag)
        return NOTHING_TO_PRINT_ERROR;

    return EXIT_SUCCESS;
}

int insert_product(char *filename)
{
    FILE *f = fopen(filename, "rb+");

    product_t product = { 0 };
    int rc;
    int n;

    if (!f)
        return OPEN_FILE_ERROR;

    if (get_size(f, &n) || !n)
        return NO_ELEMS_ERROR;

    if ((rc = scan_product(&product)))
        return rc;

    int pos = find_place_to_insert(f, product);

    if ((rc = move_products_right(f, pos)))
        return rc;

    if ((rc = put_product_by_pos(f, product, pos)))
        return rc;

    if (fclose(f))
        return FCLOSE_ERROR;

    return EXIT_SUCCESS;
}
