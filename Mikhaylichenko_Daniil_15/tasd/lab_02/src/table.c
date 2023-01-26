#include "../inc/table.h"
#include <stdio.h>
#include <stdlib.h>

int fill_table(FILE **file, car_info_t cars_arr[], keys_t keys[], size_t *table_size)
{
    fseek(*file, 0, SEEK_SET);

    int rc;
    size_t idx = *table_size = 0;

    for (; !feof(*file); idx++)
    {
        if (idx > MAX_RECORDS)
        {
            ERROR_LOG("Слишком много записей в файле");
            return TOO_MANY_RECORDS;
        }

        // NOTE: Считывание модели, страны, цены, цвета и состояния
        rc = fscanf(*file, "%15s %16s %d %12s %d",
                cars_arr[idx].model, cars_arr[idx].country, &cars_arr[idx].price,
                cars_arr[idx].color, &cars_arr[idx].condition_flag);

        if (rc != 5)
        {
            ERROR_LOG("Ошибка при считывании");
            return WRONG_DATA;
        }

        keys[idx].country = cars_arr[idx].country;
        keys[idx].index = idx;

        if (cars_arr[idx].condition_flag == NEW)
        {
            new_condition_t new_car;
            if (fscanf(*file, "%d", &new_car.guarantee) != 1)
            {
                ERROR_LOG("Ошибка при считывание гарантии");
                return WRONG_DATA;
            }

            cars_arr[idx].condition.new_car = new_car;
        }
        else if (cars_arr[idx].condition_flag == OLD)
        {
            old_condition_t old_car;
            rc = fscanf(*file, "%d %d %d %d",
                    &old_car.year, &old_car.mileage,
                    &old_car.repairs, &old_car.owners);

            if (rc != 4)
            {
                ERROR_LOG("Ошибка при считывании характеристи старой машины");
                return WRONG_DATA;
            }

            cars_arr[idx].condition.old_car = old_car;
        }
        else
        {
            ERROR_LOG("Ошибка при считывания флага состояния");
            return WRONG_DATA;
        }
    }

    *table_size = idx;

    return EXIT_SUCCESS;
}

int add_record(car_info_t cars_arr[], keys_t keys[], size_t *table_size)
{
    if (*table_size == MAX_RECORDS)
    {
        FAILURE("Таблица уже полность заполнена!");
        return TOO_MANY_RECORDS;
    }

    int rc;
    car_info_t new_record;

    ENTER("Введите марку модели (строка до 15 символов без пробелов): ");
    rc = enter_string(new_record.model, MAX_MODEL_NAME_LEN);
    if (rc != EXIT_SUCCESS)
        return rc;

    ENTER("Введите страну-производитель (строка до 16 символов без пробелов): ");
    rc = enter_string(new_record.country, MAX_COUNTRY_NAME_LEN);
    if (rc != EXIT_SUCCESS)
        return rc;

    ENTER("Введите цену новой машины (больше 0): ");
    if (scanf("%d", &new_record.price) != 1 || new_record.price <= 1)
    {
        ERROR_LOG("Ошибка ввода цены");
        return WRONG_INPUT;
    }

    fgetc(stdin); // Пропуск '\n'

    ENTER("Введите цвет модели (строка до 12 символов без прбелов): ");
    rc = enter_string(new_record.color, MAX_COLOR_NAME_LEN);
    if (rc != EXIT_SUCCESS)
        return rc;

    ENTER("Выберите состояние машины (0 - новая, 1 - старая): ");
    if (scanf("%d", &new_record.condition_flag) != 1)
    {
        ERROR_LOG("Ошибка ввода состония");
        return WRONG_INPUT;
    }

    if (new_record.condition_flag == NEW)
    {
        ENTER("Введите гарантию в годах: ");
        if (scanf("%d", &new_record.condition.new_car.guarantee) != 1 ||
                new_record.condition.new_car.guarantee <= 0)
        {
            ERROR_LOG("Ошибка ввода гарантии");
            return WRONG_INPUT;
        }
    }
    else if(new_record.condition_flag == OLD)
    {
        ENTER("Введите год выпуска (первая машина появилась в 1886): ");
        if (scanf("%d", &new_record.condition.old_car.year) != 1 ||
                new_record.condition.old_car.year < 1886)
        {
            ERROR_LOG("Ошибка ввода года выпуска");
            return WRONG_INPUT;
        }

        ENTER("Введите пробег: ");
        if (scanf("%d", &new_record.condition.old_car.mileage) != 1 ||
                new_record.condition.old_car.mileage < 0)
        {
            ERROR_LOG("Ошибка ввода пробега");
            return WRONG_INPUT;
        }

        ENTER("Введите кол-во ремонтов: ");
        if (scanf("%d", &new_record.condition.old_car.repairs) != 1 ||
                new_record.condition.old_car.repairs < 0)
        {
            ERROR_LOG("Ошибка ввода кол-ва ремонтов");
            return WRONG_INPUT;
        }

        ENTER("Введите кол-во владельцев: ");
        if (scanf("%d", &new_record.condition.old_car.owners) != 1 ||
                new_record.condition.old_car.owners < 0)
        {
            ERROR_LOG("Ошибка ввода кол-ва владельцев");
            return WRONG_INPUT;
        }
    }
    else
    {
        ERROR_LOG("Ошибка ввода состояния");
        return WRONG_INPUT;
    }

    keys[*table_size].country = new_record.country;
    keys[*table_size].index = *table_size;
    cars_arr[*table_size] = new_record;

    (*table_size)++;

    return EXIT_SUCCESS;
}

int del_record(car_info_t cars_arr[], keys_t keys[], size_t *table_size)
{
    if (*table_size == 0)
    {
        FAILURE("    Таблица пуста!");
        return EMPTY_TABLE;
    }

    int index;

    ENTER("Введите номер удаляемой записи: ");
    if (scanf("%d", &index) != 1 || index < 1 || index > *table_size)
    {
        ERROR_LOG("Ошибка ввода номера записи");
        return WRONG_INPUT;
    }

    for (int i = index - 1; i < *table_size - 1; i++)
    {
        cars_arr[i] = cars_arr[i + 1];
        keys[i] = keys[i + 1];
        keys[i].index--;
    }

    (*table_size)--;

    return EXIT_SUCCESS;
}

