#ifndef __TREE_H__
#define __TREE_H__

#include "../inc/defines.h"

typedef struct tree_node
{
    char word[MAX_STR_LEN + 1];
    unsigned char color;
    unsigned char height;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

void set_tree_compares(size_t compares);
size_t get_tree_compares(void);

void free_tree(tree_node_t **tree);
tree_node_t *create_node(char *str);
tree_node_t *find_node(tree_node_t *tree, char *str);
tree_node_t *find_max_node(tree_node_t *tree);
void search_word(tree_node_t *tree, char *str);
int find_letters(tree_node_t **tree, char *ch);
void tree_sort(tree_node_t *tree, char **array, int *index);
size_t get_tree_size_in_bytes(tree_node_t *tree);

#endif // __TREE_H__
