#include "../inc/menu.h"
#include <stdlib.h>

void print_menu()
{
    puts("+--------------------------------------------------------------------------------------------------------------------+");
    puts("|Главное меню:                                                                                                       |");
    puts("| 1.  Загрузить базу данных                                                                                          |");
    puts("| 2.  Добавить запись в таблицу                                                                                      |");
    puts("| 3.  Удалить запись по номеру                                                                                       |");
    puts("| 4.  Вывести таблицу                                                                                                |");
    puts("| 5.  Вывести массив ключей                                                                                          |");
    puts("| 6.  Вывести массив с помощью массива ключей                                                                        |");
    puts("| 7.  Вывести цены неновых авто конкретной марки с 1 предыдущим собственником, без ремонта в указанном диапазоне цен |");
    puts("| 8.  Отсортировать таблицу пузырьком по стране-производителю                                                        |");
    puts("| 9.  Отсортировать массив ключей пузырьком                                                                          |");
    puts("| 10. Отсортировать qsort'ом по стране-производителю                                                                 |");
    puts("| 11. Отсортировать массив ключей qsort'ом                                                                           |");
    puts("| 12. Сравнить эффективность двух алгоритмов сортировки                                                              |");
    puts("| 13. Очистить таблицу                                                                                               |");
    puts("| 0.  Выход                                                                                                          |");
    puts("+--------------------------------------------------------------------------------------------------------------------+");
}

int menu(void)
{
    int rc = EXIT_SUCCESS;
    int command;
    FILE *file = NULL;

    car_info_t cars_arr[MAX_RECORDS];
    keys_t keys[MAX_RECORDS];
    table_t table = { .size = 0, .max_size = MAX_RECORDS };

    do
    {
        printf("\n");
        print_menu();
        printf("\n");

        rc = scan_command(&command);
        if (rc != EXIT_SUCCESS)
            continue;

        switch (command)
        {
            case 0:
                break;
            case 1:
                ACTION_LOG("Открытие файла...");
                rc = file_open((const FILE **const)&file, SHORT_DATA_FNAME, READ_MODE);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Ошибка открытия файла");
                    break;
                }

                ACTION_LOG("Считывание записей...");
                rc = fill_table(&file, cars_arr, keys, &table.size);
                if (rc != EXIT_SUCCESS)
                {
                    if (file_close(&file) != EXIT_SUCCESS)
                    {
                        ERROR_LOG("Ошибка закрытия файла");
                        rc = FILE_CLOSE_ERROR;
                    }
                    return rc;;
                }

                table.keys = keys;
                table.cars_arr = cars_arr;

                ACTION_LOG("Закрытие файла...");
                rc = file_close(&file);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Ошибка закрытия файла");
                    return rc;;
                }

                SUCCESS(">>Операция заверщена.");
                break;
            case 2:
                rc = add_record(cars_arr, keys, &table.size);
                if (rc != EXIT_SUCCESS)
                    break;

                table.keys = keys;
                table.cars_arr = cars_arr;

                SUCCESS(">>Операция заверщена.");
                break;
            case 3:
                rc = del_record(cars_arr, keys, &table.size);
                if (rc != EXIT_SUCCESS)
                    break;

                table.keys = keys;
                table.cars_arr = cars_arr;

                SUCCESS(">>Операция заверщена.");
                break;
            case 4:
                print_table(table);
                SUCCESS(">>Операция заверщена.");
                break;
            case 5:
                print_keys(table);
                SUCCESS(">>Операция заверщена.");
                break;
            case 6:
                print_table_by_keys(table);
                SUCCESS(">>Операция заверщена.");
                break;
            case 7:
                search_cars(table);
                SUCCESS(">>Операция заверщена.");
                break;
            case 8:
                ACTION_LOG("Идёт процесс сортировки...");
                TableBubbleSort(table);
                SUCCESS(">>Операция завершена.");
                break;
            case 9:
                ACTION_LOG("Идёт процесс сортировки...");
                KeysBubbleSort(table);
                SUCCESS(">>Операция завершена.");
                break;
            case 10:
                ACTION_LOG("Идёт процесс сортировки...");
                TableQsort(table);
                SUCCESS(">>Операция завершена.");
                break;
            case 11:
                ACTION_LOG("Идёт процесс сортировки...");
                KeysQsort(table);
                SUCCESS(">>Операция завершена.");
                break;
            case 12:
                ACTION_LOG("Сравнение алгоритмов...");
                run_efficiency();
                SUCCESS(">>Операция завершена.");
                break;
            case 13:
                ACTION_LOG("Очистка таблицы...");
                table.size = 0;
                SUCCESS(">>Операция завершена.");
                break;
        }
        printf("\n");
    }
    while (command);

    return rc;
}
