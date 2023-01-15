#ifndef __UNIT_TESTS_H__
#define __UNIT_TESTS_H__

#include <check.h>

int compare_arrs(movie_t *first, movie_t *second, size_t len);

Suite *get_files_suite(void);

#endif // __UNIT_TESTS_H__
