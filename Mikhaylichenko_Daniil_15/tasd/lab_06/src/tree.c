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

tree_node_t *find_max_node(tree_node_t *tree)
{
    if (tree->right == NULL)
        return tree;

    return find_max_node(tree->right);
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
        printf("Слово \"%s\"\n", str);
        ERROR_LOG("Повтор слова");
        exit(WRONG_STR);
    }

    return tree;
}

tree_node_t *delete_max(tree_node_t *tree)
{
    if (tree->right == NULL)
        return tree->left;

    tree->right = delete_max(tree->right);
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

int tree_push(tree_node_t **tree, char *str)
{
    tree_node_t *new_node;

    if (find_node(*tree, str) != NULL)
    {
        ERROR_LOG("Узел уже существует");
        return EXIT_FAILURE;
    }

    new_node = insert_node(*tree, str);
    if (new_node == NULL)
        return EXIT_FAILURE;

    *tree = new_node;

    return EXIT_SUCCESS;
}

tree_node_t *delete_node(tree_node_t *tree, char *str)
{
    if (tree == NULL)
        return NULL;

    int compare = strncmp(str, tree->word, MAX_STR_LEN + 1);
    if (compare < 0)
        tree->left = delete_node(tree->left, str);
    else if (compare > 0)
        tree->right = delete_node(tree->right, str);
    else
    {
        tree_node_t *left = tree->left, *right = tree->right;
        free(tree);

        if (left == NULL)
            return right;

        tree_node_t *max_left = find_max_node(left);
        max_left->left = delete_max(left);
        max_left->right = right;

        return max_left;
    }
    return tree;
}

int tree_pop(tree_node_t **tree, char *str)
{
    if (find_node(*tree, str) == NULL)
    {
        ERROR_LOG("Слово не найдено в дереве");
        return EXIT_FAILURE;
    }

    tree_node_t *new_node = delete_node(*tree, str);

    *tree = new_node;

    return EXIT_SUCCESS;
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

void tree_sort(tree_node_t *tree, char **array, int *index)
{
    if (tree != NULL)
    {
        tree_sort(tree->left, array, index);
        array[*index] = malloc(sizeof(char) + (MAX_STR_LEN + 1));
        strcpy(array[*index], tree->word);
        (*index)++;
        tree_sort(tree->right, array, index);
    }
}
