#ifndef __DEFINES__H__
#define __DEFINES__H__

#define OUT 11
#define MUL 22
#define SQR 33
#define DIV 44

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define ARGS_COUNT_ERR 1
#define OPEN_FILE_ERR 2
#define SCANF_ERR 3
#define ALLOC_ERR 4
#define GETLINE_ERR 5
#define WRONG_TYPE_ERR 6
#define EMPTY_LIST_ERR 7
#define LITTLE_NUM_ERR 8
#define ZERO_DIVISION_ERR 9
#define DIVISION_MOD_ERR 10

#define YES_PRIME 0
#define NOT_PRIME 1

#ifdef DEBUG
#define LOG_DEBUG(...) { printf(__VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif

#endif
