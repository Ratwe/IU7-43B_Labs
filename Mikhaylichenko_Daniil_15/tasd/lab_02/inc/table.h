#ifndef __TABLE_H__
#define __TABLE_H__

#include "../inc/defines.h"
#include "../inc/struct.h"

#include "../inc/scan.h"

int fill_table(FILE **file, car_info_t cars_arr[], keys_t keys[], size_t *table_size);
int add_record(car_info_t cars_arrp[], keys_t keys[], size_t *table_size);
int del_record(car_info_t cars_arr[], keys_t keys[], size_t *table_size);

#endif // __TABLE_H__
