#ifndef __DEFINES__H__
#define __DEFINES__H__

#define RC 2

#define ALLOCATE_MATRIX_ERR 101
#define READ_MATRIX_ERR 102
#define MATRIX_SIZE_ERR 103
#define REALLOC_ERROR 104
#define SCANF_ERR 105
#define WRONG_POW_ERR 106

#ifdef DEBUG
#define LOG_DEBUG(...) { printf("[DB]: " __VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif

#endif
