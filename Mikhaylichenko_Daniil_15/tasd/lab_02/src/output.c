#include "../inc/output.h"

void print_record(car_info_t car, size_t i)
{
    puts(SEPARATOR);
    printf("|%-4zu|%-15s|%-16s|%8d|%-12s|",
            i + 1, car.model, car.country, car.price, car.color);

    if (car.condition_flag == NEW)
        printf("    NEW    |%11d|      -      |    -    |        -        |         -         |\n",
                car.condition.new_car.guarantee);

    if (car.condition_flag == OLD)
        printf("    OLD    |     -     |%13d|%9d|%17d|%19d|\n",
                car.condition.old_car.year, car.condition.old_car.mileage,
                car.condition.old_car.repairs, car.condition.old_car.owners);
}

void print_table(table_t table)
{
    int size = table.size;
    if (size == 0)
    {
        FAILURE("    Таблица пуста");
        return;
    }

    car_info_t *cars_arr = table.cars_arr;

    puts(BORDER);
    puts(TITLES);
    for (size_t i = 0; i < size; i++)
        print_record(cars_arr[i], i);
    puts(BORDER);

}

void print_keys(table_t table)
{
    if (table.size == 0)
    {
        FAILURE("Таблица пуста");
        return;
    }

    puts("+----+----------------+");
    puts("|№   |     Cтрана     |");
    for (size_t i = 0; i < table.size; i++)
    {
        puts("+----+----------------+");
        printf("|%-4zu|%-16s|\n", table.keys[i].index + 1, table.keys[i].country);
    }
    puts("+----+----------------+");
}

void print_table_by_keys(table_t table)
{
    if (table.size == 0)
    {
        FAILURE("Таблица пуста");
        return;
    }

    puts(BORDER);
    puts(TITLES);
    for (size_t i = 0; i < table.size; i++)
        print_record(table.cars_arr[table.keys[i].index], i);
    puts(BORDER);
}

int search_cars(table_t table)
{
    if (table.size == 0)
    {
        FAILURE("Таблица пуста");
        return EMPTY_TABLE;
    }

    int rc;
    char model[MAX_MODEL_NAME_LEN + 1];
    int start_price, end_price;

    ENTER("Введите марку модели: ");
    rc = enter_string(model, MAX_MODEL_NAME_LEN);
    if (rc != EXIT_SUCCESS)
        return rc;
    size_t str_len = strlen(model);

    ENTER("Введите диапазон цен (2 числа): ");
    if (scanf("%d%d", &start_price, &end_price) != 2)
    {
        ERROR_LOG("Ошибка ввода диапазона цен");
        return WRONG_INPUT;
    }

    if (start_price < 0 || end_price < 0 || start_price > end_price)
    {
        ERROR_LOG("Ошибка ввода диапазона цен");
        return WRONG_INPUT;
    }

    int counter = 0;

    puts(BORDER);
    puts(TITLES);
    for (size_t i = 0; i < table.size; i++)
    {
        if (table.cars_arr[i].condition_flag == OLD &&
                !strncmp(table.cars_arr[i].model, model, str_len) &&
                table.cars_arr[i].price >= start_price &&
                table.cars_arr[i].price <= end_price &&
                table.cars_arr[i].condition.old_car.owners == 1 &&
                table.cars_arr[i].condition.old_car.repairs == 0)
        {
            print_record(table.cars_arr[i], counter++);
        }
    }
    puts(BORDER);

    if (counter == 0)
    {
        FAILURE("Не найдено нужных записей");
        return NO_RECORDS;
    }

    return EXIT_SUCCESS;
}
