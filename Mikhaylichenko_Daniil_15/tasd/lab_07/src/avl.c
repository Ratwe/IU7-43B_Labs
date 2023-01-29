#include "../inc/avl.h"

unsigned char get_height(tree_node_t *node)
{
    return node == NULL ? 0 : node->height;
}

void new_height(tree_node_t* node)
{
    unsigned char left_height = get_height(node->left);
    unsigned char right_height = get_height(node->right);
    node->height = ((left_height > right_height) ? left_height : right_height) + 1;
}

int get_balance_flag(tree_node_t *node)
{
    return get_height(node->right) - get_height(node->left);
}

tree_node_t *rotate_left(tree_node_t *node)
{
    tree_node_t *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;

    new_height(node);
    new_height(new_root);

    return new_root;
}

tree_node_t *rotate_right(tree_node_t *node)
{
    tree_node_t *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    new_height(node);
    new_height(new_root);

    return new_root;
}

tree_node_t *avl_balance(tree_node_t *node)
{
    new_height(node);

    if (get_balance_flag(node) == 2)
    {
        if (get_balance_flag(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    if (get_balance_flag(node) == -2)
    {
        if (get_balance_flag(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    /* switch (get_balance_flag(node)) */
    /* { */
    /*     case 2: */
    /*         if (get_balance_flag(node->right) < 0) */
    /*             node->right = rotate_right(node->right); */
    /*         return rotate_left(node); */
    /*     case -2: */
    /*         if (get_balance_flag(node->left) > 0) */
    /*             node->left = rotate_left(node->left); */
    /*         return rotate_right(node); */
    /* } */

    return node;
}

tree_node_t *avl_insert_node(tree_node_t *tree, char *str)
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
        tree->left = avl_insert_node(tree->left, str);
    else if (compare > 0)
        tree->right = avl_insert_node(tree->right, str);
    else
    {
        printf("Слово \"%s\"\n", str);
        ERROR_LOG("Повтор слова");
        exit(WRONG_STR);
    }

    tree_node_t *node = avl_balance(tree);

    return node;
}

int fill_avl(tree_node_t **tree, FILE **file)
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
        *tree = avl_insert_node(*tree, new_str);
    }

    return EXIT_SUCCESS;
}

int avl_push(tree_node_t **tree, char *str)
{
    tree_node_t *new_node;

    if (find_node(*tree, str) != NULL)
    {
        ERROR_LOG("Узел уже существует");
        return EXIT_FAILURE;
    }

    new_node = avl_insert_node(*tree, str);
    if (new_node == NULL)
        return EXIT_FAILURE;

    *tree = new_node;

    return EXIT_SUCCESS;
}

tree_node_t *delete_avl_max(tree_node_t *tree)
{
    if (tree->right == NULL)
        return tree->left;

    tree->right = delete_avl_max(tree->right);
    return avl_balance(tree);
}

tree_node_t *delete_avl_node(tree_node_t *tree, char *str)
{
    if (tree == NULL)
        return NULL;

    int compare = strncmp(str, tree->word, MAX_STR_LEN + 1);
    if (compare < 0)
        tree->left = delete_avl_node(tree->left, str);
    else if (compare > 0)
        tree->right = delete_avl_node(tree->right, str);
    else
    {
        tree_node_t *left = tree->left, *right = tree->right;
        free(tree);

        if (left == NULL)
            return right;

        tree_node_t *max_left = find_max_node(left);
        max_left->left = delete_avl_max(left);
        max_left->right = right;

        return avl_balance(max_left);
    }
    return avl_balance(tree);
}

int avl_pop(tree_node_t **tree, char *str)
{
    if (find_node(*tree, str) == NULL)
    {
        ERROR_LOG("Слово не найдено в дереве");
        return EXIT_FAILURE;
    }

    tree_node_t *new_node = delete_avl_node(*tree, str);

    *tree = new_node;

    return EXIT_SUCCESS;
}
