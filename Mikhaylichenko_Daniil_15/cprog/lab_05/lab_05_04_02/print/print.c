#include <stdio.h>
#include <stdint.h>

#define EXPECTED_NUMBER     1
#define MIN_ARGS            2
#define MAX_ARGS            2
#define MANUFACTURER_LEN    15
#define NAME_LEN            30

#define COPY_DONE   0
#define SORT_DONE   0
#define RIGHT_INPUT 0
#define RIGHT_STR   1

#define WRONG_ARGS      53
#define TOO_LONG_STR    101
#define WRONG_INPUT     102
#define WRONG_STR       103
#define NO_STRUCTURES   104

#define GET_STRUCT get_struct_by_pos(file, pos, &product) == RIGHT_STR

typedef struct
{
    char name[NAME_LEN + 1];
    char manufacturer[MANUFACTURER_LEN + 1];
    uint32_t price;
    uint32_t product_counter;
} s_product;

int get_struct_by_pos(FILE *file, size_t pos, s_product *product)
{
    fseek(file, pos * sizeof(*product), SEEK_SET);

    if (fread(product, sizeof(*product), 1, file) != EXPECTED_NUMBER)
        return WRONG_STR;

    return RIGHT_STR;
}

int main(int argc, char **argv)
{
	if (argc < MIN_ARGS || argc > MAX_ARGS)
		return WRONG_ARGS;

	FILE *file = fopen(argv[1], "rb");
	size_t pos = 0;
	for (s_product product; GET_STRUCT; pos++)
	{
		printf("%s %s %u %u\n", product.name, product.manufacturer, product.price, product.product_counter);
	}

	return 0;
}
