#ifndef __UNIT_TESTS_H__
#define __UNIT_TESTS_H__

#include <check.h>

#include "../inc/output.h"
#include "../inc/list.h"
#include "../inc/process.h"

int compare_lists(node_t **first, node_t **second);

Suite *get_output_suite(void);
Suite *get_list_suite(void);
Suite *get_process_suite(void);

#endif // __UNIT_TESTS_H__
