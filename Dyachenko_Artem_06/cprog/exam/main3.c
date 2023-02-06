#include <stdio.h>
#include <stdlib.h>

typedef struct list list_t;

struct list
{
    int val;
    list_t *next;
};

int error(int error_code)
{
    printf("ERROR: %d\n", error_code);

    return error_code;
}

int create_elem(list_t **new, int val)
{
    list_t *ptr = malloc(sizeof(list_t));
    if (ptr == NULL)
        return 2;

    (*new) = ptr;
    (*new)->val = val;
    (*new)->next = NULL;

    return 0;
}

list_t *add_back(list_t *head, list_t *new)
{
    if (head == NULL)
        return new;

    list_t *ptr = head;

    while (ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = new;

    return head;
}

void print_list(list_t *head)
{
    list_t *ptr = head;

    while (ptr != NULL)
    {
        printf("%d ", ptr->val);
        ptr = ptr->next;
    }

    printf("\n");
}

void free_list(list_t *head)
{
    if (head == NULL)
        return;

    list_t *ptr = head;
    list_t *last = head;

    while (ptr != NULL)
    {
        last = ptr;
        ptr = ptr->next;
        free(last);
    }
}

list_t *reverse_list(list_t *head)
{
    list_t *last = NULL, *cur = head, *next = head->next;

    while (cur != NULL)
    {
        next = cur->next;
        cur->next = last;
        last = cur;
        cur = next;
    }

    return last;
}

int main(void)
{
    int val = 1, error_code;
    list_t *head = NULL, *new;

    while (scanf("%d", &val) == 1)
    {
        if (val == 0)
            break;

        if ((error_code = create_elem(&new, val)))
        {
            free_list(head);
            return error(error_code);
        }

        head = add_back(head, new);
    }

    if (val != 0)
    {
        free_list(head);
        return error(1);
    }

    if (head == NULL)
    {
        free_list(head);
        return error(3);
    }

    head = reverse_list(head);

    print_list(head);
    free_list(head);
}
