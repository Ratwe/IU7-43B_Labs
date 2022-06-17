#include "defines.h"
#include "file_functions.h"
#include "functions.h"
#include "sorting.h"

int sort_products_to_new_file(char input_name[], char output_name[])
{
    int check;

    check = copy_file(input_name, output_name);
    if (check != EXIT_SUCCESS)
        return check;

    FILE *file = fopen(output_name, "rb+");

    sort_products(file);

    fclose(file);

    return SORT_DONE;
}

int print_certain_product(char file_name[], char subname[])
{
    FILE *file = fopen(file_name, "rb");

    size_t pos = 0, structures_counter = 0;

    for (s_product product; GET_STRUCT; pos++)
        if (compare_strings(product.name, subname))
        {
            print_struct(product);
            structures_counter++;
        }

    fclose(file);

    if (structures_counter == 0)
        return NO_STRUCTURES;

    return RIGHT_INPUT;
}

int add_to_data(char file_name[])
{
    int check;

    FILE *file = fopen(file_name, "ab");

    s_product new_product = { 0 };

    printf("Enter product's name: ");
    check = enter_string(new_product.name, NAME_LEN + 1);
    if (check != EXIT_SUCCESS)
        return check;

    printf("Enter manufacturer's name: ");
    check = enter_string(new_product.manufacturer, MANUFACTURER_LEN + 1);
    if (check != EXIT_SUCCESS)
        return check;

    printf("Enter price: ");
    check = enter_num(&new_product.price);
    if (check != EXIT_SUCCESS)
        return check;

    printf("Enter number of products: ");
    check = enter_num(&new_product.product_counter);
    if (check != EXIT_SUCCESS)
        return check;

    fwrite(&new_product, sizeof(new_product), EXPECTED_NUMBER, file);

    fclose(file);

    file = fopen(file_name, "rb+");

    sort_products(file);

    fclose(file);

    return RIGHT_INPUT;
}