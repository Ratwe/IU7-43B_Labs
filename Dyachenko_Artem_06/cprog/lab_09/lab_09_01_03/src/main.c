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

#define  _POSIX_C_SOURCE 200809L

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
#define ALLOCATE_ERROR 113

#ifdef DEBUG
#define LOG_DEBUG(...) { printf(__VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif

typedef struct
{
   char *name;
   int cost;
} product_t;

int check_open_file(char *filename)
{
   struct stat buffer;
   return stat(filename, &buffer);
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

void free_products(product_t *products, int prods_count)
{
   for (int i = 0; i < prods_count; i++)
       free(products[i].name);

   free(products);
}

void print_prods_array(product_t *products, double real_price, int prods_count)
{
   // LOG_DEBUG("print_prods_array\n");

   for (int i = 0; i < prods_count; i++)
   {
       // LOG_DEBUG("i = %d\n", i);
       if (products[i].cost < real_price)
       {
           // LOG_DEBUG("product[%d] = %s, %d\n", i, products[i].name, products[i].cost);
           printf("%s%d\n", products[i].name, products[i].cost);
       }
   }
}

int get_prods_count(char *filename, int *prods_count)
{
   if (check_open_file(filename))
       return OPEN_FILE_ERROR;

   FILE *f = fopen(filename, "r");
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

   fclose(f);
   return EXIT_SUCCESS;
}

int get_prods_array(char *filename, product_t *products, int prods_count)
{
   if (check_open_file(filename))
       return OPEN_FILE_ERROR;

   FILE *f = fopen(filename, "r");
   fscanf(f, "%d\n", &prods_count);

   for (int i = 0; i < prods_count; i++)
   {
       product_t product = { .cost = 0 };
       size_t len = 0;
       int rc = 0;

       // LOG_DEBUG("getline\n");

       if ((rc = getline(&product.name, &len, f)) == 0)
       {
           fclose(f);
           LOG_DEBUG("rc = %d\n", rc);
           return PROD_NAME_ERROR;
       }

       // LOG_DEBUG("got line: %s\n", product.name);

       if (len == 1)
       {
           fclose(f);
           return PROD_NAME_ERROR;
       }

       if ((rc = fscanf(f, "%d\n", &product.cost)) != 1)
       {
           fclose(f);
           free(product.name);
           return PROD_COST_SIZE_ERROR;
       }

       // LOG_DEBUG("-->%s %d\n", product.name, product.cost);

       if (product.cost < 1)
       {
           fclose(f);
           free(product.name);
           return WRONG_PRICE_ERROR;
       }

       *(products + i) = product;
       // LOG_DEBUG("product[%d] = %s%d\n", i, products[i].name, products[i].cost);
   }

   // LOG_DEBUG("&3products = %p\n", (void *)products);
   // LOG_DEBUG("&4products = %p\n", (void *)products);

   fclose(f);
   return EXIT_SUCCESS;
}

int process_file(char *filename, char *potential_price)
{
   int error_code = EXIT_SUCCESS;
   double real_price = 0;
   int prods_count = 0;
   product_t *products = NULL;

   // LOG_DEBUG("&products = %p\n", (void *)products);  // здесь NULL

   if ((error_code = get_price(potential_price, &real_price)))
       return error_code;

   if ((error_code = get_prods_count(filename, &prods_count)))
       return error_code;

   products = calloc(prods_count, sizeof(product_t));

   if (products == NULL)
       return ALLOCATE_ERROR;

   // LOG_DEBUG("&products = %p\n", (void *)products);  // опять NULL

   if ((error_code = get_prods_array(filename, products, prods_count)))
   {
       free_products(products, prods_count);
       return error_code;
   }

   // LOG_DEBUG("&products = %p\n", (void *)products);  // опять NULL

   // LOG_DEBUG("products[0] = %s%d\n", products[1].name, products[1].cost);

   print_prods_array(products, real_price, prods_count);
   free_products(products, prods_count);

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
