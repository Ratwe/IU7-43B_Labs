#include <stdlib.h>
#include "defines.h"
#include "functions.h"
#include "sorting.h"

size_t get_len(FILE *file)
{
    fseek(file, 0, SEEK_END);

    size_t len = ftell(file) / sizeof(s_product);

    fseek(file, 0, SEEK_SET);

    return len;
}

int copy_file(char input_name[], char output_name[])
{
    FILE *file = fopen(input_name, "rb");
    FILE *output_file = fopen(output_name, "wb");

    size_t pos = 0, structures_counter = 0;

    for (s_product product; GET_STRUCT; pos++)
    {
        put_struct_by_pos(output_file, pos, &product);
        structures_counter++;
    }

    fclose(file);
    fclose(output_file);

    if (structures_counter == 0)
        return NO_STRUCTURES;

    return COPY_DONE;
}

void sort_products(FILE *file)
{
    size_t len = get_len(file);
    
    for (size_t i = 0; i < len - 1; i++)
        for (size_t j = 0; j < len - i - 1; j++)
        {
            s_product first_product, second_product;
            get_struct_by_pos(file, j, &first_product);
            get_struct_by_pos(file, j + 1, &second_product);

            uint32_t first_price = first_product.price;
            uint32_t second_price = second_product.price;

            if (first_price < second_price)
            {
                put_struct_by_pos(file, j + 1, &first_product);
                put_struct_by_pos(file, j, &second_product);
            }
            else if (first_price == second_price)
                if (first_product.product_counter < second_product.product_counter)
                {
                    put_struct_by_pos(file, j + 1, &first_product);
                    put_struct_by_pos(file, j, &second_product);
                }
        }
}