#ifndef __STRUCT_H__
#define __STRUCT_H__

#define MAX_MODEL_NAME_LEN      15
#define MAX_COUNTRY_NAME_LEN    16
#define MAX_COLOR_NAME_LEN      12
#define NEW                     0
#define OLD                     1

typedef struct
{
    int guarantee;
} new_condition_t;

typedef struct
{
    int year;
    int mileage;
    int repairs;
    int owners;
} old_condition_t;

typedef union
{
    new_condition_t new_car;
    old_condition_t old_car;
} condition_check_t;

typedef struct
{
    char model[MAX_MODEL_NAME_LEN + 1];
    char country[MAX_COUNTRY_NAME_LEN + 1];
    int price;
    char color[MAX_COLOR_NAME_LEN + 1];
    int condition_flag;
    condition_check_t condition;
} car_info_t;

typedef struct keys
{
    char *country;
    size_t index;
} keys_t;

typedef struct table
{
    car_info_t *cars_arr;
    keys_t *keys;
    size_t size;
    size_t max_size;
} table_t;

#endif // __STRUCT_H__
