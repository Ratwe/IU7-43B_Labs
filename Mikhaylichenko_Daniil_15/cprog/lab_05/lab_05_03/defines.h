#ifndef __DEFINES_H__
#define __DEFINES_H__

#define EXPECTED_NUMBER 1
#define MIN_ARGS        3
#define MAX_ARGS        4

#define NUMBER_WERE_PRINTED 0

#define WRONG_ARGS 101
#define EMPTY_FILE 102

#define READ_NUM fread(&num, sizeof(num), 1, file) == EXPECTED_NUMBER

#endif // __DEFINES_H__