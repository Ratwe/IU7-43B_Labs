#include "../inc/process.h"

int comparator(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int process(char *fin_name, char *fout_name)
{
    int rc;
    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };

    rc = fill_list(fin_name, &list, &arr);
    if (rc != EXIT_SUCCESS)
    {
        free(arr.data);
        free_list(&list);
        return rc;
    }

    node_t *sorted_list = sort_list(&list, comparator);
    if (!sorted_list)
    {
        free(arr.data);
        free_list(&list);
        return rc;
    }

    node_t *reversed_list = reverse(sorted_list);
    if (!reversed_list)
    {
        free(arr.data);
        free_list(&list);
        return rc;
    }

    rc = swap_edges(&reversed_list);
    if (rc != EXIT_SUCCESS)
    {
        free(arr.data);
        free_list(&reversed_list);
        return rc;
    }

    rc = fwrite_list(fout_name, &reversed_list);
    if (rc != EXIT_SUCCESS)
    {
        free(arr.data);
        free_list(&reversed_list);
        return rc;
    }

    free(arr.data);
    free_list(&reversed_list);

    return EXIT_SUCCESS;
}
