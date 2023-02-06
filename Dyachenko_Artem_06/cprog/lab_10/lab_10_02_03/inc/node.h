#ifndef __NODE__H__
#define __NODE__H__

typedef struct node node_t;

struct node
{
    int data;
    node_t *next;
};

void free_list(node_t *root);

node_t *create_node(int num);

void push_back(node_t **list, node_t *node);

#endif
