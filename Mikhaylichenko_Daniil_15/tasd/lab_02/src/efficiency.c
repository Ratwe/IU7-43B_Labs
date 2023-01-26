#include "../inc/efficiency.h"
#include <stddef.h>

void print_time(clock_t start, clock_t end)
{
    printf("%zu (мс)\n", (end - start) / (CLOCKS_PER_SEC / 1000000));
}

void print_results(results_t results, table_t table)
{
    WORD("\n    Сортировка таблицы пузырьком: ");
    printf("\t\t%6zu (мс)\n", results.bubble_table_time);

    WORD("    Сортировка массива ключей пузырьком: ");
    printf("\t%6zu (мс)\n", results.bubble_keys_time);

    WORD("    Сортировка таблицы qsort'ом: ");
    printf("\t\t%6zu (мс)\n", results.qsort_table_time);

    WORD("    Сортировка массива ключей qsort'ом: ");
    printf("\t%6zu (мс)\n", results.qsort_keys_time);

    printf("\n\033[33m    Размер таблицы: \033[0m\t\t\t\t%6zu (байт)\n", sizeof(*(table.cars_arr)) * table.size);
    printf("\033[33m    Размер массива ключей: \033[0m\t\t\t%6zu (байт)\n\n", sizeof(*(table.keys)) * table.size);
}

void run_efficiency(void)
{
    int rc;

    clock_t start, end;

    results_t results =
    {
        .bubble_table_time = 0,
        .bubble_keys_time = 0,
        .qsort_table_time = 0,
        .qsort_keys_time = 0
    };
    car_info_t cars_arr[MAX_RECORDS];
    keys_t keys[MAX_RECORDS];
    table_t table = { .size = 0, .max_size = MAX_RECORDS };

    FILE *file = NULL;
    rc = file_open((const FILE **const)&file, FULL_DATA_FNAME, READ_MODE);
    if (rc != EXIT_SUCCESS)
    {
        ERROR_LOG("Ошибка открытия файла");
        return;
    }

    for (size_t i = 0; i < NUMBER_OF_COMPARES; i++)
    {
        // Сортировка таблицы пузырьком
        rc = fill_table(&file, cars_arr, keys, &table.size);
        if (rc != EXIT_SUCCESS)
        {
            file_close(&file);
            return;
        }
        table.cars_arr = cars_arr;
        table.keys = keys;

        start = clock();
        TableBubbleSort(table);
        end = clock();

        results.bubble_table_time += (end - start) / (CLOCKS_PER_SEC / 1000000);

        // Сортировка массива ключей пузырьком
        rc = fill_table(&file, cars_arr, keys, &table.size);
        if (rc != EXIT_SUCCESS)
        {
            file_close(&file);
            return;
        }
        table.cars_arr = cars_arr;
        table.keys = keys;

        start = clock();
        KeysBubbleSort(table);
        end = clock();

        results.bubble_keys_time += (end - start) / (CLOCKS_PER_SEC / 1000000);

        // Сортировка таблицы qsort'ом
        rc = fill_table(&file, cars_arr, keys, &table.size);
        if (rc != EXIT_SUCCESS)
        {
            file_close(&file);
            return;
        }
        table.cars_arr = cars_arr;
        table.keys = keys;

        start = clock();
        TableQsort(table);
        end = clock();

        results.qsort_table_time += (end - start) / (CLOCKS_PER_SEC / 1000000);

        // Сортировка массива ключей qsort'ом
        rc = fill_table(&file, cars_arr, keys, &table.size);
        if (rc != EXIT_SUCCESS)
        {
            file_close(&file);
            return;
        }
        table.cars_arr = cars_arr;
        table.keys = keys;

        start = clock();
        KeysQsort(table);
        end = clock();

        results.qsort_keys_time += (end - start) / (CLOCKS_PER_SEC / 1000000);
    }

    results.bubble_table_time /= NUMBER_OF_COMPARES;
    results.bubble_keys_time /= NUMBER_OF_COMPARES;
    results.qsort_table_time /= NUMBER_OF_COMPARES;
    results.qsort_keys_time /= NUMBER_OF_COMPARES;

    print_results(results, table);

    file_close(&file);
}
