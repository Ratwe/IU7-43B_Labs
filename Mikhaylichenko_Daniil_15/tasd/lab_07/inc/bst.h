#ifndef __BST_H__
#define __BST_H__

#include "../inc/defines.h"
#include "../inc/tree.h"

int fill_bst(tree_node_t **tree, FILE **file);
int bst_push(tree_node_t **tree, char *str);
int bst_pop(tree_node_t **tree, char *str);

#endif // __TREE_H__
