#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "products.h"
#include "utils.h"

void print_product(product_t product)
{
    printf("%s\n", product.name);
    printf("%s\n", product.manu);
    printf("%u\n", product.cost);
    printf("%u\n", product.count);
}

int scan_product(product_t *product)
{
    return scanf("%s%s%u%u", product->name, product->manu, &product->cost, &product->count) != STRUCT_FIELDS;
}

// Возвращает индекс, с которого нужно сдвинуть все продукты направо
int find_place_to_insert(FILE *f, product_t product)
{
    int i = 0;
    product_t cur_product;

    while (!get_product_by_pos(f, i, &cur_product))
    {
        if (cur_product.cost < product.cost)
            return i;
        else if (cur_product.cost == product.cost && cur_product.count < product.count)
            return i;
        i++;
    }

    return i;
}

int swap_products(FILE *f, int pos1, int pos2)
{
    product_t a, b;
    int rc;

    if ((rc = get_product_by_pos(f, pos1, &a)))
        return rc;

    if ((rc = get_product_by_pos(f, pos2, &b)))
        return rc;

    if (a.cost < b.cost)
    {
        if ((rc = put_product_by_pos(f, b, pos1)))
            return rc;

        if ((rc = put_product_by_pos(f, a, pos2)))
            return rc;
    }
    else if (a.cost == b.cost && a.count < b.count)
    {
        if ((rc = put_product_by_pos(f, b, pos1)))
            return rc;

        if ((rc = put_product_by_pos(f, a, pos2)))
            return rc;
    }

    return EXIT_SUCCESS;
}

int move_products_right(FILE *f, int pos)
{
    int rc;
    int n;

    product_t a = { 0 };

    if ((rc = get_size(f, &n)))
        return rc;

    if (fseek(f, 0, SEEK_END))
        return SEEK_ERROR;

    if (fwrite(&a, SIZE, 1, f) != WRITE_ELEM_COUNT)
        return WRITE_ERROR;

    if (fseek(f, SIZE * pos, SEEK_SET))
        return SEEK_ERROR;

    for (int i = n; i > pos && i; i--)
    {
        if ((rc = get_product_by_pos(f, i - 1, &a)))
            return rc;

        if ((rc = put_product_by_pos(f, a, i)))
            return rc;
    }

    return EXIT_SUCCESS;
}

int same_end(char *name, char *substr)
{
    int name_len = strlen(name);
    int substr_len = strlen(substr);

    if (substr_len > name_len)
        return FALSE;

    for (int i = 0; i < substr_len; i++)
        if (name[name_len - i - 1] != substr[substr_len - i - 1])
            return FALSE;

    return TRUE;
}
