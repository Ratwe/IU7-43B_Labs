#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "node.h"

void free_list(node_t *root)
{
    node_t *next;

    while (root->next != NULL)
    {
        next = root->next;
        free(root);
        root = next;
    }

    free(root);
}

node_t *create_node(int num)
{
    node_t *node = malloc(sizeof(node_t));

    if (node == NULL)
        return NULL;

    node->data = num;
    node->next = NULL;

    return node;
}

void push_back(node_t **list, node_t *node)
{
    if (*list == NULL)
    {
        *list = node;
        return;
    }

    node_t *runner = *list;

    while (runner && runner->next != NULL)
    {
        runner = runner->next;
        // printf("runner->next = %p\n", (void *)runner->next);
    }

    runner->next = node;
}
