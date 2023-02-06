#include <stdio.h>
#include <stdlib.h>

typedef struct list list_t;

struct list
{
    int val;
    list_t *next;
};

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

int error(int error_code)
{
    printf("ERROR: %d\n", error_code);

    return error_code;
}

list_t *add_front(list_t *head, list_t *new)
{
    if (head == NULL)
        return new;

    new->next = head;
    return new;
}

int find_max_val(list_t *head)
{
    int max = head->val;
    list_t *ptr = head;

    while (ptr != NULL)
    {
        max = (ptr->val > max) ? ptr->val : max;
        ptr = ptr->next;
    }

    return max;
}

list_t *remove_max_vals(list_t *head, int max)
{
    list_t *new_head = head;

    while (new_head != NULL && new_head->val == max)
        new_head = new_head->next;

    if (new_head == NULL)
        return NULL;

    list_t *last = new_head, *ptr = new_head->next;

    while (ptr != NULL)
    {
        if (ptr->val == max)
            last->next = ptr->next;
        else
            last = ptr;

        ptr = ptr->next;
    }

    return new_head;
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

    list_t *last = head, *cur = head->next;
    while (cur != NULL)
    {
        free(last);
        last = cur;
        cur = cur->next;
    }

    free(last);
}

int main(void)
{
    list_t *head = NULL, *new;
    int val = 1, error_code = 0;

    while (val != 0)
    {
        if (scanf("%d", &val) != 1)
        {
            free_list(head);
            return error(1);
        }

        if (val == 0)
            break;

        if ((error_code = create_elem(&new, val)))
        {
            free_list(head);
            return error(error_code);
        }

        head = add_front(head, new);
    }

    if (head == NULL)
    {
        free_list(head);
        return error(3);
    }

    int max_val = find_max_val(head);
    head = remove_max_vals(head, max_val);

    if (head == NULL)
    {
        free_list(head);
        return error(3);
    }

    print_list(head);
    free_list(head);

    return 0;
}
