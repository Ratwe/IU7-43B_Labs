#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define ACTION_LOG(str)     fprintf(stdout, "    \033[34m%s\033[0m\n", str)
#define ERROR_LOG(str)      fprintf(stderr, "\033[31m>>ERROR: %s\033[0m\n", str)
#define SUCCESS(str)        fprintf(stdout, "\033[32m%s\033[0m\n", str)
#define FAILURE(str)        fprintf(stdout, "\033[35m%s\033[0m\n", str)
#define WORD(str)           fprintf(stdout, "\033[33m%s\033[0m\n", str)

#define MIN(x, y) x > y ? y : x;
#define MAX(x, y) x > y ? x : y;

#define MATRIX_DOT_FILE     "./out/matrix_graph.dot"
#define MATRIX_SVG_FILE     "./out/matrix_graph.svg"
#define LIST_DOT_FILE       "./out/list_graph.dot"
#define LIST_SVG_FILE       "./out/list_graph.svg"

#define MIN_COMMAND         0
#define MAX_COMMAND         8

#define MAX_STR_LEN         25
#define PATH_STR_LEN        100

#define FILE_OPEN_ERROR     101
#define FILE_CLOSE_ERROR    102
#define WRONG_DATA          103
#define WRONG_STR           104
#define WRONG_INPUT         105
#define EMPTY_TREE          106
#define NODE_EXIST          107
#define FORK_ERROR          108
#define ALLOCATE_ERROR      109

#endif // __DEFINES_H__
