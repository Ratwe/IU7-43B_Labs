#ifndef __DEFINES__H__
#define __DEFINES__H__

#define ALLOCATE_MATRIX_ERR 101
#define READ_MATRIX_ERR 102

#ifdef DEBUG
#define LOG_DEBUG(...) { printf("[DB]: " __VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif

#endif
