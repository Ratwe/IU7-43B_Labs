#include <stdio.h>

#include "defines.h"
#include "products.h"

int get_size(FILE *f, int *size)
{
    if (fseek(f, 0L, SEEK_END))
        return SEEK_ERROR;

    long pos = ftell(f);

    if (fseek(f, 0L, SEEK_SET))
        return SEEK_ERROR;

    if (pos % SIZE)
        return FILE_SIZE_ERROR;

    *size = pos / SIZE;

    return EXIT_SUCCESS;
}

int put_product_by_pos(FILE *f, product_t product, int pos)
{
    if (fseek(f, SIZE * pos, SEEK_SET))
        return SEEK_ERROR;

    if (fwrite(&product, SIZE, 1, f) != WRITE_ELEM_COUNT)
        return WRITE_ERROR;

    return EXIT_SUCCESS;
}

int get_product_by_pos(FILE *f, int pos, product_t *product)
{
    int n;
    if (get_size(f, &n) || pos >= n)
        return EXIT_FAILURE;

    if (fseek(f, SIZE * pos, SEEK_SET))
        return SEEK_ERROR;

    if (fread(product, SIZE, 1, f) != READ_ELEM_COUNT)
        return READ_ERROR;

    rewind(f);

    return EXIT_SUCCESS;
}

int copy_file(FILE *f_src, FILE *f_dest)
{
    int n;
    int rc;
    product_t cur_product;

    if ((rc = get_size(f_src, &n)))
        return rc;

    for (int i = 0; i < n; i++)
    {
        if (get_product_by_pos(f_src, i, &cur_product))
            break;

        if ((rc = put_product_by_pos(f_dest, cur_product, i)))
            return rc;
    }

    return EXIT_SUCCESS;
}
