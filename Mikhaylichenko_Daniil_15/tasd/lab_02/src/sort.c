#include "../inc/sort.h"

void swap_elems(car_info_t first_record, car_info_t second_record)
{
}

void TableBubbleSort(table_t table)
{
    if (table.size == 0)
    {
        FAILURE("    Таблица пуста!");
        return;
    }

    for (size_t i = 0; i < table.size; i++)
        for (size_t j = 0; j < table.size - i - 1; j++)
            if (strcmp(table.cars_arr[j].country, table.cars_arr[j + 1].country) > 0)
            {
                car_info_t temp = table.cars_arr[j];
                table.cars_arr[j] = table.cars_arr[j + 1];
                table.cars_arr[j + 1] = temp;
            }
}

void KeysBubbleSort(table_t table)
{
    if (table.size == 0)
    {
        FAILURE("    Таблица пуста!");
        return;
    }

    for (size_t i = 0; i < table.size; i++)
        for (size_t j = 0; j < table.size - i - 1; j++)
            if (strcmp(table.keys[j].country, table.keys[j + 1].country) > 0)
            {
                keys_t temp = table.keys[j];
                table.keys[j] = table.keys[j + 1];
                table.keys[j + 1] = temp;
            }
}

int table_qcmp(void const *a, void const *b)
{
    char const *aa = ((car_info_t*)(a))->country;
    char const *bb = ((car_info_t*)(b))->country;

    return strcmp(aa, bb);
}

int keys_qcmp(void const *a, void const *b)
{
    char const *aa = ((keys_t*)(a))->country;
    char const *bb = ((keys_t*)(b))->country;

    return strcmp(aa, bb);
}

void TableQsort(table_t table)
{
    if (table.size == 0)
    {
        FAILURE("    Таблица пуста!");
        return;
    }

    qsort(table.cars_arr, table.size, sizeof(car_info_t), table_qcmp);
}

void KeysQsort(table_t table)
{
    if (table.size == 0)
    {
        FAILURE("    Таблица пуста!");
        return;
    }

    qsort(table.keys, table.size, sizeof(keys_t), keys_qcmp);

}
