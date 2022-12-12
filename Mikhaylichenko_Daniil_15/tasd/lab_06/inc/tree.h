#ifndef __TREE_H__
#define __TREE_H__

#include "../inc/defines.h"

typedef struct tree_node
{
    char word[MAX_STR_LEN + 1];
    unsigned char height;
    unsigned char color;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

void free_tree(tree_node_t **tree);
int fill_tree(tree_node_t **tree, FILE **file);
int tree_push(tree_node_t **tree, char *str);
int tree_pop(tree_node_t **tree, char *str);
void search_word(tree_node_t *tree, char *str);
int find_letters(tree_node_t **tree, char *ch);

#endif // __TREE_H__
