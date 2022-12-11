#include "../inc/tree.h"
#include <stdio.h>
#include <stdlib.h>

void free_node(tree_node_t *tree)
{
    if (tree == NULL)
        return;

    free_node(tree->left);
    free_node(tree->right);

    free(tree);
}

void free_tree(tree_node_t **tree)
{
    free_node(*tree);
    *tree = NULL;
}

tree_node_t *create_node(char *str)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    if (node != NULL)
    {
        strncpy(node->word, str, MAX_STR_LEN);
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

tree_node_t *insert_node(tree_node_t *tree, char *str)
{
    if (tree == NULL)
    {
        tree_node_t *node = create_node(str);
        if (node == NULL)
            ERROR_LOG("Ошибка выделения памяти");
        return node;
    }

    int compare = strcmp(str, tree->word);

    if (compare < 0)
        tree->left = insert_node(tree->left, str);
    else if (compare > 0)
        tree->right = insert_node(tree->right, str);
    else
    {
        ERROR_LOG("Повтор слова");
        exit(WRONG_STR);
    }

    return tree;
}

int fill_tree(tree_node_t **tree, FILE **file)
{
    for (char str[MAX_STR_LEN + 2]; fgets(str, MAX_STR_LEN + 2, *file) != NULL;)
    {
        if (strlen(str) > MAX_STR_LEN || str[0] == '\n')
        {
            ERROR_LOG("Введена недопустимая строка");
            return WRONG_STR;
        }
        char *new_str = strtok(str, "\n");
        *tree = insert_node(*tree, new_str);
    }
    return EXIT_SUCCESS;
}

tree_node_t *find_node(tree_node_t *tree, char *str)
{
    for(tree_node_t *node = tree; node != NULL;)
    {
        int compare = strncmp(str, node->word, 25);

        if (compare < 0)
            node = node->left;
        else if (compare > 0)
            node = node->right;
        else
            return node;
    }

    return NULL;
}

void search_word(tree_node_t *tree, char *str)
{
    tree_node_t *node = find_node(tree, str);

    (node == NULL) ? FAILURE("СЛОВО НЕ НАЙДЕНО") : SUCCESS("СЛОВО НАЙДЕНО");
}
