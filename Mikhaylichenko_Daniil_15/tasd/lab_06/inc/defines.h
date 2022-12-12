#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTION_LOG(str) fprintf(stdout, "    \033[34m%s\033[0m\n", str)
#define ERROR_LOG(str)  fprintf(stderr, "\033[31m>>ERROR: %s\033[0m\n", str)
#define SUCCESS(str)    fprintf(stdout, "\033[32m%s\033[0m\n", str)
#define FAILURE(str)    fprintf(stdout, "\033[35m%s\033[0m\n", str)
#define WORD(str)       fprintf(stdout, "\033[33m%s\033[0m\n", str)

#define DATABASE            "./data/text.txt"
#define DOT_FILE            "./out/tree.dot"
#define SVG_FILE            "./out/tree.svg"

#define MIN_COMMAND         0
#define MAX_COMMAND         7

#define MAX_STR_LEN         25

#define FILE_OPEN_ERROR     101
#define FILE_CLOSE_ERROR    102
#define WRONG_INPUT         103
#define WRONG_STR           104
#define EMPTY_TREE          105
#define NODE_EXIST          106
#define FORK_ERROR          107

#endif // __DEFINES_H__
