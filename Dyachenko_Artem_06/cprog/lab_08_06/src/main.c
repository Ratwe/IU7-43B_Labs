#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "essential_matrix.h"
#include "actions_matrix.h"

int main(void)
{
    int m, n, p, q, rc = 0;

    int **am = NULL;
    int **bm = NULL;

    printf("Введите размерность матрицы А: ");
    if ((rc = scanf("%d %d", &m, &n) != RC))
    {
        free_matrix(am, m);
        return SCANF_ERR;
    }

    if (m < 1 || n < 1)
    {
        free_matrix(am, m);
        return MATRIX_SIZE_ERR;
    }

    int **buff = allocate_matrix(m, n);

    if (!buff)
    {
        free_matrix(am, m);
        return ALLOCATE_MATRIX_ERR;
    }

    am = buff;
    int error_code = EXIT_SUCCESS;

    if ((error_code = read_matrix(am, m, n)))
    {
        free_matrix(am, m);
        return error_code;
    }

    printf("Введите размерность матрицы B: ");
    if ((rc = scanf("%d %d", &p, &q) != RC))
    {
        free_matrix(am, m);
        return SCANF_ERR;
    }

    if (p < 1 || q < 1)
    {
        free_matrix(am, m);
        return MATRIX_SIZE_ERR;
    }

    buff = allocate_matrix(p, q);

    if (!buff)
    {
        free_matrix(am, m);
        return ALLOCATE_MATRIX_ERR;
    }

    bm = buff;

    if ((error_code = read_matrix(bm, p, q)))
    {
        free_matrix(am, m);
        free_matrix(bm, p);
        return error_code;
    }

#ifdef DEBUG
LOG_DEBUG("initial tables: \n")
print_matrix(am, m, n);
print_matrix(bm, p, q);
#endif

    int k = (m < n) ? m : n;
    if ((error_code = square_down(am, &m, &n, k)))
    {
        free_matrix(am, m);
        free_matrix(bm, p);
        return error_code;
    }

    int s = (p < q) ? p : q;
    if ((error_code = square_down(bm, &p, &q, s)))
    {
        free_matrix(am, m);
        free_matrix(bm, p);
        return error_code;
    }

#ifdef DEBUG
LOG_DEBUG("square_down: \n");
print_matrix(am, m, n);
print_matrix(bm, p, q);
LOG_DEBUG("m n = {%d %d}\n[DB]: p q = {%d %d}\n", m, n, p, q);
LOG_DEBUG("k, s = %d, %d\n", k, s);
#endif

    int z = (k > s) ? k : s;
    if ((error_code = square_up(am, &m, &n, z)))
    {
        free_matrix(am, m);
        free_matrix(bm, p);

        return error_code;
    }

    if ((error_code = square_up(bm, &p, &q, z)))
    {
        free_matrix(am, m);
        free_matrix(bm, p);

        return error_code;
    }

#ifdef DEBUG
LOG_DEBUG("square_up: \n");
print_matrix(am, m, n);
print_matrix(bm, p, q);
#endif

    int r, y;

    printf("Введите r: ");
    if ((rc = scanf("%d", &r) != 1))
    {
        free_matrix(am, z);
        free_matrix(bm, z);
        return SCANF_ERR;
    }

    printf("Введите y: ");
    if ((rc = scanf("%d", &y) != 1))
    {
        free_matrix(am, z);
        free_matrix(bm, z);
        return SCANF_ERR;
    }

    if (r < 0 || y < 0)
    {
        free_matrix(am, z);
        free_matrix(bm, z);
        return WRONG_POW_ERR;
    }

    buff = allocate_matrix(z, z);

    if (!buff)
    {
        free_matrix(am, z);
        free_matrix(bm, z);
        return ALLOCATE_MATRIX_ERR;
    }

    int **res = buff;
    if ((error_code = multi_multiply(am, bm, res, z, r, y)))
    {
        free_matrix(am, z);
        free_matrix(bm, z);
        free_matrix(res, z);
        return error_code;
    }

    print_matrix(res, z, z);

    free_matrix(am, z);
    free_matrix(bm, z);
    free_matrix(res, z);

    return EXIT_SUCCESS;
}
