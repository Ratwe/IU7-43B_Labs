#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "../inc/defines.h"
#include "../inc/list.h"
#include "../inc/output.h"

int mult_lists(node_t **first_mults, node_t **second_mults, node_t **result);
int sqr_list(node_t **list);
int divide_lists(node_t **first_mults, node_t **second_mults, node_t **result);
int process(int mode);

#endif // __PROCESS_H__
