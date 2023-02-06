#ifndef __DEFINES__H__
#define __DEFINES__H__

#define EXIT_SUCCESS 0
#define ARGS_COUNT_ERR 1
#define OPEN_FILE_ERR 2
#define SCANF_ERR 3
#define ALLOC_ERR 4

#ifdef DEBUG
#define LOG_DEBUG(...) { printf(__VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif

#endif
