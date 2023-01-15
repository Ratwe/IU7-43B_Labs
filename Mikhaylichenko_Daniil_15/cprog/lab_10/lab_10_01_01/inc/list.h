#ifndef __LIST_H__
#define __LIST_H__

#include "../inc/defines.h"
#include "../inc/files.h"

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

void free_list(node_t **list);
int fill_list(char *fname, node_t **list);
void *pop_front(node_t **head);
void *pop_back(node_t **head);
int swap_edges(node_t **list);
node_t *reverse(node_t *head);
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));
node_t *sort_list(node_t **list, int (*comparator)(const void *, const void *));

#endif // __LIST_H__
