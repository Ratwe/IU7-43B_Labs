#include "../inc/tree.h"
#include <stddef.h>

static int tree_compares = 0;

void set_tree_compares(size_t compares)
{
    tree_compares = compares;
}

size_t get_tree_compares(void)
{
    return tree_compares;
}

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
        node->color = 0;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

tree_node_t *find_node(tree_node_t *tree, char *str)
{
    for(tree_node_t *node = tree; node != NULL;)
    {
        int compare = strncmp(str, node->word, 25);
        tree_compares++;

        if (compare < 0)
            node = node->left;
        else if (compare > 0)
            node = node->right;
        else
            return node;
    }

    return NULL;
}

tree_node_t *find_max_node(tree_node_t *tree)
{
    if (tree->right == NULL)
        return tree;

    return find_max_node(tree->right);
}

void search_word(tree_node_t *tree, char *str)
{
    tree_node_t *node = find_node(tree, str);

    (node == NULL) ? FAILURE("    СЛОВО НЕ НАЙДЕНО") : SUCCESS("    СЛОВО НАЙДЕНО");
}

void find_letter(tree_node_t *tree, char *ch, int *counter)
{
    if (tree == NULL)
        return;

    if (!strncmp(ch, tree->word, 1))
    {
        printf("    Найдено слово: ");
        WORD(tree->word);
        (*counter)++;
        tree->color = 1;
    }
    else
        tree->color = 0;

    find_letter(tree->left, ch, counter);
    find_letter(tree->right, ch, counter);
}

int find_letters(tree_node_t **tree, char *ch)
{
    if (*tree == NULL)
    {
        ERROR_LOG("Пустое дерево");
        return EMPTY_TREE;
    }

    int counter = 0;
    find_letter(*tree, ch, &counter);

    printf("    Итог: %d\n", counter);

    return EXIT_SUCCESS;
}

void count_size(tree_node_t *tree, size_t *size)
{
    if (tree == NULL)
        return;

    *size += sizeof(struct tree_node);

    count_size(tree->left, size);
    count_size(tree->right, size);
}

size_t get_tree_size_in_bytes(tree_node_t *tree)
{
    size_t size = 0;
    count_size(tree, &size);
    return size;
}
