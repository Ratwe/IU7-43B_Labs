 /*
 * Вариант №3
 * В текстовом файле хранится информация о продуктах, которая включает в себя на-
 * звание продукта и цену. В названии продукта не более двадцати пяти символов.
 * Цена задается целым числом. Количество продуктов указано в первой строке файла.
 * Требуется написать программу, которая, будучи вызванной из командной строки:
 * app.exe FILE P
 * где FILE — имя файла, P — значение цены;
 *
 * 1. считывает информацию о продуктах в массив.
 * 2. Выводит на экран информацию о продуктах, цена которых ниже значения P.
 *
 * Примечания
 * 1. Каждое поле структуры в файле записано в отдельной строке.
 * 2. Каждое поле выводимой на экран структуры выводится в отдельной строке.
 * 3. После последнего поля последней структуры на экран печатается символ новой
 * строки ради единообразия вывода.
 * 4. Количество структур в статическом массиве не превышает пятнадцати.
 * 5. Все алгоритмы сортировки должны обладать устойчивостью.
 * 6. Регистр в строках учитывается.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PROD_NAME_SIZE 26
#define MAX_PRODS_COUNT 15
#define ARG_COUNT 3
#define PROD_FIELD_COUNT 2
#define MAX_PROD_COST_SIZE 10

#define OPEN_FILE_ERROR 101
#define ARG_COUNT_ERROR 102
#define NEG_NUM_ERROR 103
#define NOT_NUM_ERROR 104
#define WRONG_FORMAT_PRODS_COUNT 105
#define PROD_FIELD_COUNT_ERROR 106
#define WRONG_PRICE_ERROR 107
#define PRODS_COUNT_ERROR 108
#define PROD_NAME_ERROR 109
#define PROD_COST_SIZE_ERROR 110
#define LIMIT_REACH_ERROR 111
#define PROD_NAME_SIZE_ERROR 112

#ifdef DEBUG
#define LOG_DEBUG(...) { printf(__VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif

typedef struct
{
    char name[MAX_PROD_NAME_SIZE];
    int cost;
} product_t;

int check_open_file(char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);

    if (exist == 0)
        return EXIT_SUCCESS;
    else
        return OPEN_FILE_ERROR;
}

int get_price(char *potential_price, double *real_price)
{
    int rc = sscanf(potential_price, "%lf", real_price);

    if (rc != 1)
        return NOT_NUM_ERROR;

    if (*real_price < 1)
        return WRONG_PRICE_ERROR;

    return EXIT_SUCCESS;
}

int get_prods_array(char *filename, product_t *products, int *prods_count)
{
    if (check_open_file(filename))
        return OPEN_FILE_ERROR;

    FILE *f = fopen(filename, "r");
    product_t product = { 0 };
    int rc = fscanf(f, "%d\n", prods_count);

    if (rc != 1)
    {
        fclose(f);
        return WRONG_FORMAT_PRODS_COUNT;
    }

    if (*prods_count > MAX_PRODS_COUNT || *prods_count < 1)
    {
        fclose(f);
        return PRODS_COUNT_ERROR;
    }

    for (int i = 0; i < *prods_count; i++)
    {
        char s_cost[MAX_PROD_COST_SIZE];

        if (fgets(product.name, MAX_PROD_NAME_SIZE, f) == NULL)
        {
            fclose(f);
            return PROD_NAME_ERROR;
        }

        if (strlen(product.name) == 1)
        {
            fclose(f);
            return PROD_NAME_ERROR;
        }

        if (fgets(s_cost, MAX_PROD_COST_SIZE, f) == NULL)
        {
            fclose(f);
            return PROD_COST_SIZE_ERROR;
        }

        if (sscanf(s_cost, "%d", &product.cost) != 1)
        {
            fclose(f);
            return NOT_NUM_ERROR;
        }

        LOG_DEBUG("%s %d\n", product.name, product.cost);

        if (product.cost < 1)
        {
            fclose(f);
            return WRONG_PRICE_ERROR;
        }

        products[i] = product;
    }

    if (fgets(product.name, MAX_PROD_NAME_SIZE, f) != NULL)
    {
        fclose(f);
        return LIMIT_REACH_ERROR;
    }

    fclose(f);
    return EXIT_SUCCESS;
}

void print_prods_array(product_t *products, double real_price, int prods_count)
{
    for (int i = 0; i < prods_count; i++)
        if (products[i].cost < real_price)
            printf("%s%d\n", products[i].name, products[i].cost);
}

int process_file(char *filename, char *potential_price)
{
    int error_code = EXIT_SUCCESS;
    double real_price = 0;
    int prods_count = 0;
    product_t products[MAX_PRODS_COUNT];

    if ((error_code = get_price(potential_price, &real_price)))
        return error_code;

    if ((error_code = get_prods_array(filename, products, &prods_count)))
        return error_code;

    print_prods_array(products, real_price, prods_count);

    return error_code;
}

int main(int argc, char **argv)
{
    int error_code = EXIT_SUCCESS;

    if (argc != ARG_COUNT)
        return ARG_COUNT_ERROR;

    error_code = process_file(argv[1], argv[2]);

    return error_code;
}
