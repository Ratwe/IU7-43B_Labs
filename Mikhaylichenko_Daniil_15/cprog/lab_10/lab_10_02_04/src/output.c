#include "../inc/output.h"

int print_mults(node_t **list)
{
    if (!(*list))
    {
        ERROR_LOG("EMPTY LIST");
        return EMPTY_LIST;
    }

    *list = reverse(*list);

    if ((*list)->num != 1)
    {
        for (node_t *cur = *list; cur != NULL; cur = cur->next)
            fprintf(stdout, "%d %d ", cur->num, cur->power);
    }
    fprintf(stdout, "1\n");

    return EXIT_SUCCESS;
}
