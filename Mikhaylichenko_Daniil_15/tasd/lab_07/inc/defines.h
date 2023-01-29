#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTION_LOG(str)     fprintf(stdout, "    \033[34m%s\033[0m\n", str)
#define ERROR_LOG(str)      fprintf(stderr, "\033[31m>>ERROR: %s\033[0m\n", str)
#define SUCCESS(str)        fprintf(stdout, "\033[32m%s\033[0m\n", str)
#define FAILURE(str)        fprintf(stdout, "\033[35m%s\033[0m\n", str)
#define WORD(str)           fprintf(stdout, "\033[33m%s\033[0m\n", str)

#define DATABASE            "./data/text.txt"
#define WORDS_FILE          "./data/words.txt"
#define BST_DOT_FILE        "./out/bst.dot"
#define AVL_DOT_FILE        "./out/avl.dot"
#define BST_SVG_FILE        "./out/bst.svg"
#define AVL_SVG_FILE        "./out/avl.svg"

#define NOT_EXIST           0
#define EXIST               1
#define EMPTY               0
#define DELETED             2

#define OPENED_COEF         0.72
#define CLOSED_COEF         1.5
#define HASH_DIV            10
#define RESTRUCT            2

#define MIN_COMPARES        1.0f
#define MAX_COMPARES        100.0f

#define MIN_COMMAND         0
#define MAX_COMMAND         100

#define MAX_STR_LEN         25

#define FILE_OPEN_ERROR     101
#define FILE_CLOSE_ERROR    102
#define WRONG_INPUT         103
#define WRONG_STR           104
#define EMPTY_TREE          105
#define NODE_EXIST          106
#define FORK_ERROR          107
#define EMPTY_FILE          108
#define ALLOCATE_ERROR      109
#define OVERFLOW            110

#endif // __DEFINES_H__
