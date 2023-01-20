#include "../inc/list.h"

void free_list(node_t **list)
{
    for (node_t *temp; *list; *list = temp)
    {
        temp = (*list)->next;
        free(*list);
    }
}

node_t *create_node(int num, int power)
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->num = num;
        node->power = power;
        node->next = NULL;
    }

    return node;
}

node_t *add_node(node_t **head, int num, int power)
{
    node_t *new_node = create_node(num, power);
    if (!new_node)
    {
        ERROR_LOG("NEW NODE ALLOCATION ERROR");
        return NULL;
    }

    if (!(*head))
        return new_node;

    node_t *cur = *head;
    for (; cur->next; cur = cur->next);

    cur->next = new_node;

    return *head;
}

int convert_to_multipliers(node_t **list, int num)
{
    if (num <= 0)
    {
        ERROR_LOG("WRONG INPUT");
        return WRONG_INPUT;
    }

    if (num == 1)
    {
        (*list) = add_node(list, 1, 1);
        return EXIT_SUCCESS;
    }

    for (int divider = 2; divider * divider <= num; divider++)
    {
        int power = 0;
        for (; num % divider == 0; power++, num /= divider);
        if (power > 0)
            (*list) = add_node(list, divider, power);
    }
    if (num > 1)
        (*list) = add_node(list, num, 1);

    return EXIT_SUCCESS;
}

int convert_to_num(node_t **list, int *num)
{
    if (!(*list))
    {
        ERROR_LOG("EMPTY LIST");
        return EMPTY_LIST;
    }

    *num = 1;
    for (node_t *cur = *list; cur != NULL; cur = cur->next)
    {
        int temp = cur->num;
        for (int i = 1; i < cur->power; i++)
            temp *= cur->num;
        *num *= temp;
    }

    return EXIT_SUCCESS;
}

void pop_front(node_t **head, int *num, int *power)
{
    *num = (*head)->num;
    *power = (*head)->power;

    node_t *temp = *head;
    *head = (*head)->next;
    free(temp);
}

int move_to_start(node_t **list, int num, int power)
{
    node_t *temp = create_node(num, power);
    if (!temp)
        return ALLOCATE_ERROR;

    if (!(*list))
    {
        *list = temp;
        return EXIT_SUCCESS;
    }

    temp->next = *list;
    *list = temp;

    return EXIT_SUCCESS;
}

node_t *reverse(node_t *head)
{
    if (!head)
        return NULL;

    node_t *new_head = NULL;

    for (node_t *temp = head; temp != NULL;)
    {
        int num, power;
        pop_front(&temp, &num, &power);
        if (move_to_start(&new_head, num, power) != EXIT_SUCCESS)
            return NULL;
    }

    return new_head;
}
