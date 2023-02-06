#include <stdio.h>
#include <stdlib.h>

typedef struct list list_t;

struct list
{
    list_t *next;
    int val;
};

int create_elem(list_t **new, int val)
{
    list_t *temp = malloc(sizeof(list_t));
    if (temp == NULL)
    {
        printf("ERROR: 2\n");
        return 2;
    }

    *new = temp;
    (*new)->val = val;

    return 0;
}

list_t* add_front(list_t *head, list_t *new)
{
    new->next = head;
    return new;
}

list_t* add_back(list_t *head, list_t *new)
{
    if (head == NULL)
        return new;

    list_t *cur = head;

    while (cur->next != NULL)
        cur = cur->next;

    cur->next = new;

    return head;
}

void print_list(list_t *head)
{
    list_t *cur = head;

    while (cur != NULL)
    {
        printf("%d ", cur->val);
        cur = cur->next;
    }

    printf("\n");
}

list_t* find_min(list_t *head)
{
    list_t *cur = head;
    list_t *min = head;

    while (cur != NULL)
    {
        if (cur->val < min->val)
            min = cur;

        cur = cur->next;
    }

    return min;
}

int count_min(list_t *head, int min)
{
    list_t *cur = head;
    int count = 0;

    while (cur != NULL)
    {
        if (cur->val == min)
            count++;

        cur = cur->next;
    }

    return count;
}

void free_list(list_t *head)
{
    if (head == NULL)
        return;

    list_t *cur = head;
    list_t *last = head;

    while (cur->next != NULL)
    {
        last = cur;
        cur = cur->next;
        free(last);
    }

    free(cur);
}

int main(void)
{
    int val = 1, error_code;
    list_t *head = NULL, *new;
    int rc = scanf("%d", &val);

    while (val != 0)
    {
        if (rc != 1)
        {
            printf("ERROR: 1\n");
            free_list(head);
            return 1;
        }

        if ((error_code = create_elem(&new, val)))
        {
            printf("ERROR: %d\n", error_code);
            free_list(head);
            return error_code;
        }

        head = add_front(head, new);

        rc = scanf("%d", &val);
    }

    if (head == NULL)
    {
        printf("ERROR: 3\n");
        free_list(head);
        return 3;
    }

    list_t *min = find_min(head);
    int min_count = count_min(head, min->val);

    if ((error_code = create_elem(&new, min_count)))
    {
        printf("ERROR: %d\n", error_code);
        free_list(head);
        return error_code;
    }

    new->next = min->next;
    min->next = new;

    print_list(head);
    free_list(head);
}
