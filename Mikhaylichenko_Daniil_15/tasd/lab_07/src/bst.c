#include "../inc/bst.h"

tree_node_t *bst_insert_node(tree_node_t *tree, char *str)
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
        tree->left = bst_insert_node(tree->left, str);
    else if (compare > 0)
        tree->right = bst_insert_node(tree->right, str);
    else
    {
        printf("Слово \"%s\"\n", str);
        ERROR_LOG("Повтор слова");
        exit(WRONG_STR);
    }

    return tree;
}

int fill_bst(tree_node_t **tree, FILE **file)
{
    fseek(*file, 0, SEEK_SET);

    for (char str[MAX_STR_LEN + 2]; fgets(str, MAX_STR_LEN + 2, *file) != NULL;)
    {
        if (strlen(str) > MAX_STR_LEN || str[0] == '\n')
        {
            ERROR_LOG("Введена недопустимая строка");
            return WRONG_STR;
        }
        char *new_str = strtok(str, "\n");
        *tree = bst_insert_node(*tree, new_str);
    }
    return EXIT_SUCCESS;
}

int bst_push(tree_node_t **tree, char *str)
{
    tree_node_t *new_node;

    if (find_node(*tree, str) != NULL)
    {
        ERROR_LOG("Узел уже существует");
        return EXIT_FAILURE;
    }

    new_node = bst_insert_node(*tree, str);
    if (new_node == NULL)
        return EXIT_FAILURE;

    *tree = new_node;

    return EXIT_SUCCESS;
}


tree_node_t *delete_bst_max(tree_node_t *tree)
{
    if (tree->right == NULL)
        return tree->left;

    tree->right = delete_bst_max(tree->right);
    return tree;
}

tree_node_t *delete_bst_node(tree_node_t *tree, char *str)
{
    if (tree == NULL)
        return NULL;

    int compare = strncmp(str, tree->word, MAX_STR_LEN + 1);
    if (compare < 0)
        tree->left = delete_bst_node(tree->left, str);
    else if (compare > 0)
        tree->right = delete_bst_node(tree->right, str);
    else
    {
        tree_node_t *left = tree->left, *right = tree->right;
        free(tree);

        if (left == NULL)
            return right;

        tree_node_t *max_left = find_max_node(left);
        max_left->left = delete_bst_max(left);
        max_left->right = right;

        return max_left;
    }
    return tree;
}

int bst_pop(tree_node_t **tree, char *str)
{
    if (find_node(*tree, str) == NULL)
    {
        ERROR_LOG("Слово не найдено в дереве");
        return EXIT_FAILURE;
    }

    tree_node_t *new_node = delete_bst_node(*tree, str);

    *tree = new_node;

    return EXIT_SUCCESS;
}
