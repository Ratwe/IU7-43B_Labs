#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "defines.h"
#include "node.h"

int check_open_file(char *filename)
{
    struct stat buffer;
    return stat(filename, &buffer) ? OPEN_FILE_ERR : EXIT_SUCCESS;
}

void free_list_node(node_t *root)
{
    node_t *node_old = root, *node_new;

    while (node_old && node_old->next != NULL)
    {
        if (node_old)
        {
            node_new = node_old->next;

            free(node_old->data);
            free(node_old);

            node_old = node_new;
        }
    }

    // free(node_old->data);
    free(node_old);
}

void free_list_data(node_t *root)
{
    node_t *node_old = root, *node_new;

    while (node_old && node_old->next != NULL)
    {
        if (node_old)
        {
            node_new = node_old->next;

            free(node_old->data);

            node_old = node_new;
        }
    }
}

void print_list(node_t *root)
{
    node_t *node = root;

    while (node != NULL)
    {
        // printf("%p-> %d\n", node, *((int*) node->data));
        printf("%d ", *((int *) node->data));
        node = node->next;
    }

    printf("\n\n");
}

int read_file(FILE *f, node_t *root, int *n)
{
    if (fscanf(f, "%d", n) != 1)
        return SCANF_ERR;

    // скан первого элемента

    node_t *node_old = root;
    int *p_temp = malloc(sizeof(int));

    if (fscanf(f, "%d", p_temp) != 1)
        return SCANF_ERR;

    node_old->data = p_temp;

    for (int i = 1; i < *n; i++)
    {

        node_t *node_new = malloc(sizeof(node_t));
        if (node_new == NULL)
            return ALLOC_ERR;

        p_temp = malloc(sizeof(int));

        if (fscanf(f, "%d", p_temp) != 1)
            return SCANF_ERR;

        node_new->data = p_temp;
        node_new->next = NULL;
        node_old->next = node_new;

        node_old = node_new;
    }

    return EXIT_SUCCESS;
}

int comparator(const void *a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

node_t* find(node_t *head, const void *data, int (*comparator)(const void*, const void *))
{
    node_t *node = head;

    while (node != NULL)
    {
        if (comparator(node->data, data) == 0)
            return node;

        node = node->next;
    }

    return node;
}

int find_min_data(node_t *head, int (*comparator)(const void*, const void *))
{
    node_t *node = head, *res_node = head;

    while (node != NULL)
    {
        if (comparator(node->data, res_node->data) < 0)
            res_node = node;

        node = node->next;
    }

    return *((int *)res_node->data);
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (!head || !elem)
        return;

    if (*head == before)
    {
        elem->next = *head;
        *head = elem;

        return;
    }

    node_t *node = *head;

    while (node && node->next != before)
        node = node->next;

    if (node == NULL)
        return;

    node->next = elem;
    elem->next = before;
}

node_t *reverse(node_t *head)
{
    node_t *node = head;
    node_t *old_node = NULL;

    while (node)
    {
        node_t *next_node = node->next;
        node->next = old_node;
        old_node = node;
        node = next_node;
    }

    return old_node;
}

int list_length(node_t *head)
{
    int count = 0;
    node_t *node = head;

    while (node)
    {
        node = node->next;
        count++;
    }

    return count;
}

void front_back_split(node_t *head, node_t **back)
{
    int len = list_length(head);
    node_t *node = head;

    for (int i = 0; node && i < len / 2 + len % 2 - 1; i++, node = node->next);

    *back = node ? node->next : NULL;
    node ? (node->next = NULL) : NULL;
}

void move_node(node_t **from, node_t **result, node_t **end)
{
    node_t *node = *from;
    *from = (*from)->next;
    node->next = NULL;
    (*end) ? ((*end)->next = node) : (*result = node);
    *end = node;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    if (!head_a || !head_b || !comparator)
        return NULL;

    node_t *result = NULL;
    node_t *end = NULL;

    while (*head_a || *head_b)
    {
        if (!*head_a)
            move_node(head_b, &result, &end);
        else if (!*head_b)
            move_node(head_a, &result, &end);
        else if (comparator((*head_a)->data, (*head_b)->data) < 0)
            move_node(head_a, &result, &end);
        else
            move_node(head_b, &result, &end);
    }

    return result;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (head == NULL)
        return NULL;

    if (head->next == NULL)
        return head;

    node_t *back;

    front_back_split(head, &back);

    head = sort(head, comparator);
    back = sort(back, comparator);

    return sorted_merge(&head, &back, comparator);
}

int do_task(char *filename_in, char *filename_out)
{
    if (check_open_file(filename_in) || check_open_file(filename_out))
        return OPEN_FILE_ERR;

    FILE *f = fopen(filename_in, "r");
    int error_code = 0, n = 0;

    node_t *root = malloc(sizeof(node_t));
    if (root == NULL)
        return ALLOC_ERR;

    if ((error_code = read_file(f, root, &n)))
    {
        free_list_data(root);
        free_list_node(root);
        return error_code;
    }

    int min_data = find_min_data(root, (*comparator));
    node_t *min_node = find(root, &min_data, (*comparator));

    // printf("min_val = %d\nmin_node = %p\n\n", min_data, min_node);

    node_t *duplicate = malloc(sizeof(node_t));
    if (duplicate == NULL)
    {
        // free(duplicate);
        // free_list(root);
        return ALLOC_ERR;
    }

    int *p_temp = malloc(sizeof(int));
    *p_temp = *((int *) min_node->data);
    duplicate->data = p_temp;
    duplicate->next = NULL;

    insert(&root, duplicate, root);

#ifdef DEBUG
print_list(root);
#endif

    root = reverse(root);

#ifdef DEBUG
print_list(root);
#endif



    // free(duplicate);
    // free_list_data(root);
    // free_list_node(root);
    // free_list_data(root2);
    return EXIT_SUCCESS;
}
