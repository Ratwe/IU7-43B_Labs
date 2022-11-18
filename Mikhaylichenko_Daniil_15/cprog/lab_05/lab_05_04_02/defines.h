#ifndef __DEFINES_H__
#define __DEFINES_H__

#define EXPECTED_NUMBER     1
#define MIN_ARGS            3
#define MAX_ARGS            4
#define MANUFACTURER_LEN    15
#define NAME_LEN            30

#define COPY_DONE   0
#define SORT_DONE   0
#define RIGHT_INPUT 0
#define RIGHT_STR   1

#define WRONG_ARGS      53
#define TOO_LONG_STR    101
#define WRONG_INPUT     102
#define WRONG_STR       103
#define EMPTY_STRING	104
#define NO_STRUCTURES   105

#define GET_STRUCT get_struct_by_pos(file, pos, &product) == RIGHT_STR

#endif // __DEFINES_H__