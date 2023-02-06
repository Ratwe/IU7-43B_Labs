#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "defines.h"
#include "node.h"

int print_list(node_t *root)
{
    if (root == NULL)
        return EMPTY_LIST_ERR;

    node_t *node = root;

    while (node != NULL && node->data >= 0)
    {
        printf("%d ", node->data);
        node = node->next;
    }

    printf("L\n");

    return EXIT_SUCCESS;
}

int is_prime(int num)
{
    for (int i = 2; i <= num / 2; i++)
        if (num % i == 0)
            return NOT_PRIME;

    return YES_PRIME;
}

int convert_num(node_t **list, int num)
{
    if (num < 2)
        return LITTLE_NUM_ERR;

    int temp = num;

    for (int i = 2; i <= num / 2; i++)
    {
        if (is_prime(i) == NOT_PRIME)
            continue;

        int count = 0;
        while (temp % (int) pow(i, count) == 0)
            count++;

        count--;

        temp /= (int) pow(i, count);

        node_t *node = create_node(count);
        push_back(list, node);

        if (temp == 1)
            break;
    }

    return EXIT_SUCCESS;
}

int print_num()
{
    int num, rc, error_code;

    if ((rc = scanf("%d", &num)) != 1)
        return SCANF_ERR;

    node_t *list = NULL;

    if ((error_code = convert_num(&list, num)))
    {
        free_list(list);
        return error_code;
    }

    if ((error_code = print_list(list)))
    {
        free_list(list);
        return error_code;
    }

    free_list(list);

    return EXIT_SUCCESS;
}

int multiply()
{
    int a, b, rc, error_code;

    if ((rc = scanf("%d", &a)) != 1)
        return SCANF_ERR;

    if ((rc = scanf("%d", &b)) != 1)
        return SCANF_ERR;

    node_t *list = NULL;

    if ((error_code = convert_num(&list, a * b)))
    {
        free_list(list);
        return error_code;
    }

    if ((error_code = print_list(list)))
    {
        free_list(list);
        return error_code;
    }

    free_list(list);

    return EXIT_SUCCESS;
}

int square()
{
    int num, rc, error_code;

    if ((rc = scanf("%d", &num)) != 1)
        return SCANF_ERR;

    node_t *list = NULL;

    if ((error_code = convert_num(&list, num * num)))
    {
        free_list(list);
        return error_code;
    }

    if ((error_code = print_list(list)))
    {
        free_list(list);
        return error_code;
    }

    free_list(list);

    return EXIT_SUCCESS;
}

int division()
{
    int a, b, rc, error_code;

    if ((rc = scanf("%d", &a)) != 1)
        return SCANF_ERR;

    if ((rc = scanf("%d", &b)) != 1)
        return SCANF_ERR;

    if (b == 0)
        return ZERO_DIVISION_ERR;

    if (a % b != 0)
        return DIVISION_MOD_ERR;

    node_t *list = NULL;

    if ((error_code = convert_num(&list, a / b)))
    {
        free_list(list);
        return error_code;
    }

    if ((error_code = print_list(list)))
    {
        free_list(list);
        return error_code;
    }

    free_list(list);

    return EXIT_SUCCESS;
}
