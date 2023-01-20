#include "../inc/list.h"

void free_list(node_t **list)
{
    for (node_t *temp; *list; *list = temp)
    {
        temp = (*list)->next;
        free(*list);
    }
}

node_t *create_node(void *num)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
    {
        ERROR_LOG("NEW NODE ALLOCATION ERROR");
        return NULL;
    }

    new_node->data = num;
    new_node->next = NULL;

    return new_node;
}

int move_to_start(node_t **list, void *num)
{
    node_t *temp = create_node(num);
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

int move_to_end(node_t **list, void *num)
{
    node_t *temp = create_node(num);
    if (!temp)
        return ALLOCATE_ERROR;

    if (!(*list))
    {
        *list = temp;
        return EXIT_SUCCESS;
    }

    node_t *cur = *list;
    for (; cur->next != NULL; cur = cur->next);
    cur->next = temp;

    return EXIT_SUCCESS;
}

int fill_list(char *fname, node_t **list, array_t *arr)
{
    int rc;

    FILE *file = NULL;
    rc = file_open((const FILE **const)&file, fname, READ_MODE);
    if (rc != EXIT_SUCCESS)
        return rc;

    int len;
    if (fscanf(file, "%d", &len) != EXPECTED_INPUT || len <= 1)
    {
        ERROR_LOG("WRONG_DATA");

        rc = file_close(&file);
        if (rc != EXIT_SUCCESS)
            return rc;

        return WRONG_DATA;
    }
    arr->data = calloc(len * sizeof(int), sizeof(int));
    arr->len = len;

    for (int i = 0; i < arr->len; i++)
    {
        int num;
        if (fscanf(file, "%d", &num) != EXPECTED_INPUT)
        {
            ERROR_LOG("WRONG DATA");

            rc = file_close(&file);
            if (rc != EXIT_SUCCESS)
                return rc;

            return WRONG_DATA;
        }
        arr->data[i] = num;
    }

    rc = file_close(&file);
    if (rc != EXIT_SUCCESS)
        return rc;

    for (int i = 0; i < arr->len; i++)
    {
        rc = move_to_end(list, &arr->data[i]);
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    return EXIT_SUCCESS;
}

void *pop_front(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    void *data = (*head)->data;

    node_t *temp = *head;
    *head = (*head)->next;
    free(temp);

    return data;
}

void *pop_back(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    if ((*head)->next == NULL)
    {
        void *data = (*head)->data;
        *head = NULL;

        return data;
    }

    node_t *temp = *head;
    for (; temp->next->next != NULL; temp = temp->next);

    void *data = temp->next->data;

    node_t *end = temp->next;
    temp->next = NULL;
    free(end);

    return data;
}

int swap_edges(node_t **list)
{
    void *back_num = pop_back(list);
    if (!back_num)
        return EMPTY_LIST;

    void *front_num = pop_front(list);
    if (!front_num)
        return EMPTY_LIST;

    int rc;

    rc = move_to_end(list, front_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    rc = move_to_start(list, back_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

node_t *reverse(node_t *head)
{
    if (!head)
        return NULL;

    node_t *new_head = NULL;

    for (node_t *temp = head; temp != NULL;)
    {
        void *data = pop_front(&temp);
        if (move_to_start(&new_head, data) != EXIT_SUCCESS)
            return NULL;
    }

    return new_head;
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    element->next = NULL;

    if (!(*head))
    {
        *head = element;
        return;
    }

    if (comparator((*head)->data, element->data) > 0)
    {
        node_t *temp_element = *head;
        *head = element;
        element->next = temp_element;
        return;
    }

    node_t *temp = *head;
    for (; temp->next != NULL; temp = temp->next)
    {
        if (comparator(temp->next->data, element->data) > 0)
        {
            node_t *temp_element = temp->next;
            temp->next = element;
            element->next = temp_element;
            return;
        }
    }
    temp->next = element;
}

node_t *sort_list(node_t **list, int (*comparator)(const void *, const void *))
{
    if (!(*list))
    {
        ERROR_LOG("EMPTY LIST");
        return NULL;
    }

    node_t *new_head = NULL;
    for (node_t *temp; *list != NULL;)
    {
        temp = (*list)->next;
        sorted_insert(&new_head, *list, comparator);
        (*list) = temp;
    }
    return new_head;
}
