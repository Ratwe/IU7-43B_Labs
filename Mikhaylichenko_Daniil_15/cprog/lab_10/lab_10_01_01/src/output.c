#include "../inc/output.h"

int fwrite_list(char *fname, node_t **list)
{
    if (!(*list))
        return EMPTY_LIST;

    int rc;

    FILE *file = NULL;
    rc = file_open((const FILE **const)&file, fname, WRITE_MODE);
    if (rc != EXIT_SUCCESS)
        return rc;

    node_t *temp = *list;
    for (; temp != NULL; temp = temp->next)
        fprintf(file, "%d\n", *(int*)temp->data);

    rc = file_close(&file);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}
