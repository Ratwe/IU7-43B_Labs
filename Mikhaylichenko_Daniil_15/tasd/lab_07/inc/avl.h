#ifndef __AVL_H__
#define __AVL_H__

#include "../inc/defines.h"
#include "../inc/tree.h"

int fill_avl(tree_node_t **tree, FILE **file);
int avl_push(tree_node_t **tree, char *str);
int avl_pop(tree_node_t **tree, char *str);

#endif // __TREE_H__
