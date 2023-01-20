#include "../inc/process.h"

int mult_lists(node_t **first_mults, node_t **second_mults, node_t **result)
{
    if (!(*first_mults) || !(*(second_mults)))
    {
        ERROR_LOG("EMPTY LIST");
        return EMPTY_LIST;
    }

    int rc;
    int first_num, second_num;

    rc = convert_to_num(first_mults, &first_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    rc = convert_to_num(second_mults, &second_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    rc = convert_to_multipliers(result, first_num * second_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

int sqr_list(node_t **list)
{
    if (!(*list))
    {
        ERROR_LOG("EMPTY LIST");
        return EMPTY_LIST;
    }

    for (node_t *cur = *list; cur != NULL; cur = cur->next)
        cur->power *= 2;

    return EXIT_SUCCESS;
}

int divide_lists(node_t **first_mults, node_t **second_mults, node_t **result)
{
    if (!(*first_mults) || !(*(second_mults)))
    {
        ERROR_LOG("EMPTY LIST");
        return EMPTY_LIST;
    }

    int rc;
    int first_num, second_num;

    rc = convert_to_num(first_mults, &first_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    rc = convert_to_num(second_mults, &second_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    if (second_num == 0)
    {
        ERROR_LOG("DIVISION BY ZERO");
        return DIVISION_BY_ZERO;
    }

    rc = convert_to_multipliers(result, first_num / second_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

int process(int mode)
{
    int rc;
    node_t *first_mults = NULL, *second_mults = NULL;
    int first_num, second_num;

    if (fscanf(stdin, "%d", &first_num) != EXPECTED_INPUT || first_num <= 0)
    {
        ERROR_LOG("WRONG FIRST NUM INPUT");
        return WRONG_INPUT;
    }

    rc = convert_to_multipliers(&first_mults, first_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    if (mode == MUL_MODE || mode == DIV_MODE)
    {
        if (fscanf(stdin, "%d", &second_num) != EXPECTED_INPUT || second_num <= 0)
        {
            ERROR_LOG("WRONG SECOND NUM INPUT");
            free_list(&first_mults);
            return WRONG_INPUT;
        }

        rc = convert_to_multipliers(&second_mults, second_num);
        if (rc != EXIT_SUCCESS)
        {
            free_list(&first_mults);
            return rc;
        }
    }

    node_t *result = NULL;

    switch (mode)
    {
        case OUT_MODE:
            result = first_mults;
            break;
        case MUL_MODE:
            rc = mult_lists(&first_mults, &second_mults, &result);
            if (rc != EXIT_SUCCESS)
            {
                free_list(&first_mults);
                free_list(&second_mults);
                free_list(&result);
                return rc;
            }
            free_list(&first_mults);
            free_list(&second_mults);
            break;
        case SQR_MODE:
            rc = sqr_list(&first_mults);
            if (rc != EXIT_SUCCESS)
            {
                free_list(&first_mults);
                free_list(&result);
                return rc;
            }
            result = first_mults;
            break;
        case DIV_MODE:
            rc = divide_lists(&first_mults, &second_mults, &result);
            if (rc != EXIT_SUCCESS)
            {
                free_list(&first_mults);
                free_list(&second_mults);
                free_list(&result);
                return rc;
            }
            free_list(&first_mults);
            free_list(&second_mults);
            break;
        default:
            ERROR_LOG("WRONG MODE");
            free_list(&first_mults);
            return WRONG_MODE;
            break;
    }

    rc = print_mults(&result);

    free_list(&result);

    return rc;
}
