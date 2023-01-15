#include "../inc/output.h"
#include <stdio.h>
#include <stdlib.h>

int fwrite_list(char *fname, node_t **list)
{
    if (!(*list))
        return EMPTY_LIST;

    int rc;

    FILE *file = NULL;
    rc = file_open((const FILE **const)&file, fname, WRITE_MODE);
    if (rc != EXIT_SUCCESS)
        return rc;

    for (; *list != NULL; *list = (*list)->next)
        fprintf(file, "%d\n", *(int*)(*list)->data);

    rc = file_close(&file);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}
