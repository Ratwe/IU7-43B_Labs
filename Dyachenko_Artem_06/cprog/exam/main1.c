#include <stdio.h>
#include <stdlib.h>

typedef struct list list_t;

struct list {
    list_t *next;
    int val;
};

int create_elem(list_t **elem, int val)
{
    list_t* ptr = malloc(sizeof(list_t));

    if (!ptr)
        return 2;

    (*elem) = ptr;
    (*elem)->val = val;

    return 0;
}

list_t* add_front(list_t *head, list_t *new)
{
    // list_t *temp = head;

    // while (temp->next != NULL)
    //     temp = temp->next;

    new->next = head;
    return new;
}

void print_list(list_t *head)
{
    list_t *temp = head;

    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }

    printf("\n");
}

void free_list(list_t *head)
{
    list_t *cur = head->next;
    list_t *last = head;

    while (cur->next != NULL)
    {
        free(last);
        last = cur;
        cur = cur->next;
    }

    free(cur);
}

int main(void)
{
    int scan_rc, num;
    list_t *head_neg = NULL, *head_pos = NULL;

    scan_rc = scanf("%d", &num);
    if (scan_rc != 1)
    {
        printf("ERROR: 1\n");
        return 1;
    }

    if (num == 0)
    {
        printf("ERROR: 3\n");
        return 3;
    }

    list_t *new;
    int rc;
    if ((rc = create_elem(&new, num)))
    {
        printf("ERROR: %d", rc);
        return rc;
    }

    if (num < 0)
        head_neg = add_front(head_neg, new);
    else
        head_pos = add_front(head_pos, new);

    while (scanf("%d", &num) == 1) {
        if (num == 0)
            break;

        if ((rc = create_elem(&new, num)))
        {
            printf("ERROR: %d", rc);
            return rc;
        }

        if (num < 0)
            head_neg = add_front(head_neg, new);
        else
            head_pos = add_front(head_pos, new);
    }

    if (num != 0)
    {
        printf("ERROR: 1\n");
        return 1;
    }

    // print_list(head_neg);
    // print_list(head_pos);

    list_t *temp = head_pos;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = head_neg;

    print_list(head_pos);
    free_list(head_pos);

    return 0;
}
