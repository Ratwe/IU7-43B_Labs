#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "matrix.h"

int main(void)
{
    int rc = 0, error_code = 0;

    matrix_t matrix_a;
    matrix_a.matrix = NULL;

    if ((rc = read_matrix(&matrix_a)))
        return rc;

    matrix_t matrix_b;
    matrix_b.matrix = NULL;

    if ((rc = read_matrix(&matrix_b)))
    {
        free_matrix(&matrix_a);
        return rc;
    }

#ifdef DEBUG
LOG_DEBUG("initial tables: \n")
print_matrix(matrix_t);
print_matrix(matrix_t);
#endif

    if ((error_code = square_down(&matrix_a)))
    {
        // free_matrix(matrix_a);
        free_matrix(&matrix_b);
        return error_code;
    }

    if ((error_code = square_down(&matrix_b)))
    {
        free_matrix(&matrix_a);
        // free_matrix(matrix_b);
        return error_code;
    }

#ifdef DEBUG
LOG_DEBUG("square_down: \n");
print_matrix(matrix_a);
print_matrix(matrix_b);
#endif

    if ((error_code = square_up(&matrix_a, &matrix_b)))
    {
        free_matrix(&matrix_b);
        free_matrix(&matrix_a);

        return error_code;
    }

#ifdef DEBUG
LOG_DEBUG("square_up: \n");
print_matrix(matrix_a);
print_matrix(matrix_b);
#endif

    matrix_t matrix_res;
    matrix_res.matrix = NULL;

    if ((error_code = multi_multiply(&matrix_a, &matrix_b, &matrix_res)))
    {
        free_matrix(&matrix_a);
        free_matrix(&matrix_b);

        return error_code;
    }

    print_matrix(matrix_res);

    free_matrix(&matrix_a);
    free_matrix(&matrix_b);
    free_matrix(&matrix_res);

    return EXIT_SUCCESS;
}
