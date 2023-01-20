#ifndef __LIST_H__
#define __LIST_H__

#include "../inc/defines.h"

typedef struct node
{
    int num;
    int power;
    struct node *next;
} node_t;

typedef struct
{
    int *data;
    int len;
} array_t;

void free_list(node_t **list);
int convert_to_multipliers(node_t **list, int num);
int convert_to_num(node_t **list, int *num);
node_t *reverse(node_t *head);

#endif // __LIST_H__
