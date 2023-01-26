#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTION_LOG(str)     fprintf(stdout, "\033[34m    %s\033[0m\n", str)
#define ENTER(str)          fprintf(stdout, "\033[33m    %s\033[0m", str)
#define ERROR_LOG(str)      fprintf(stderr, "\033[31m>>ERROR: %s\033[0m\n", str)
#define SUCCESS(str)        fprintf(stdout, "\033[32m%s\033[0m\n", str)
#define FAILURE(str)        fprintf(stdout, "\033[35m%s\033[0m\n", str)
#define WORD(str)           fprintf(stdout, "\033[33m%s\033[0m", str)

#define SHORT_DATA_FNAME    "./data/data10.txt"
#define FULL_DATA_FNAME     "./data/data1000.txt"

#define MIN_COMMAND         0
#define MAX_COMMAND         12

#define MAX_RECORDS         1000

#define NUMBER_OF_COMPARES  100

#define FILE_OPEN_ERROR     101
#define FILE_CLOSE_ERROR    102
#define WRONG_INPUT         103
#define WRONG_STR           104
#define WRONG_DATA          105
#define TOO_MANY_RECORDS    106
#define EMPTY_TABLE         107
#define NO_RECORDS          108

#define BORDER              "+-------------------------------------------------------------------------------------------------------------------------------------------------+"
#define TITLES              "|№   |     Марку     |     Cтрана     |  Цена  |    Цвет    | "\
                            "Состояние | " \
                            "Гарантия  | "\
                            "Год выпуска  | Пробег | Кол-во ремонтов | Кол-во владельцев |"
#define SEPARATOR           "+----+---------------+----------------+--------+------------+-----------+-----------+-------------+---------+-----------------+-------------------+"


#endif // __DEFINES_H__
