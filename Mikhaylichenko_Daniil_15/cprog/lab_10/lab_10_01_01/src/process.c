#include "../inc/process.h"
#include <stdlib.h>

int comparator(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

void PRINT(node_t **list) {
    printf("---------------------------------\n");
    for (; (*list)->next != NULL; *list = (*list)->next)
        printf("%d\n", *(int*)((*list)->data));
}

int process(char *fin_name, char *fout_name)
{
    int rc;
    node_t *list = NULL;

    rc = fill_list(fin_name, &list);
    if (rc != EXIT_SUCCESS)
    {
        free_list(&list);
        return rc;
    }
    PRINT(&list);

    node_t *sorted_list = sort_list(&list, comparator);
    if (!sorted_list)
    {
        free_list(&list);
        return rc;
    }
    PRINT(&sorted_list);

    rc = swap_edges(&sorted_list);
    if (rc != EXIT_SUCCESS)
    {
        free_list(&sorted_list);
        return rc;
    }
    PRINT(&sorted_list);

    node_t *reversed_list = reverse(sorted_list);
    if (!reversed_list)
    {
        free_list(&list);
        return rc;
    }
    PRINT(&reversed_list);

    rc = fwrite_list(fout_name, &reversed_list);
    if (rc != EXIT_SUCCESS)
    {
        free_list(&list);
        free_list(&reversed_list);
        return rc;
    }

    free_list(&reversed_list);

    return EXIT_SUCCESS;
}
