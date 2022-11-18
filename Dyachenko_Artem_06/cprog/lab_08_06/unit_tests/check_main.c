#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "essential_matrix.h"
#include "actions_matrix.h"

int main(void)
{
    int m, n, p, q;

    printf("Введите размерность матрицы А: ");
    scanf("%d %d", &m, &n);

    int **buff = allocate_matrix(m, n);

    if (!buff)
        return ALLOCATE_MATRIX_ERR;

    int **A = buff;
    int error_code = EXIT_SUCCESS;

    if ((error_code = read_matrix(A, m, n)))
        return error_code;

    printf("Введите размерность матрицы B: ");
    scanf("%d %d", &p, &q);

    buff = allocate_matrix(p, q);

    if (!buff)
        return ALLOCATE_MATRIX_ERR;

    int **B = buff;

    if ((error_code = read_matrix(B, p, q)))
        return error_code;

#ifdef DEBUG
LOG_DEBUG("initial tables: \n")
print_matrix(A, m, n);
print_matrix(B, p, q);
#endif

    int k = (m < n) ? m : n;
    A = square_down(A, &m, &n, k);

    int s = (p < q) ? p : q;
    B = square_down(B, &p, &q, s);

#ifdef DEBUG
LOG_DEBUG("square_down: \n");
print_matrix(A, m, n);
print_matrix(B, p, q);
LOG_DEBUG("m n = {%d %d}\n[DB]: p q = {%d %d}\n", m, n, p, q);
LOG_DEBUG("k, s = %d, %d\n", k, s);
#endif

    int z = (k > s) ? k : s;
    A = square_up(A, &m, &n, z);
    B = square_up(B, &p, &q, z);

#ifdef DEBUG
LOG_DEBUG("square_up: \n");
print_matrix(A, m, n);
print_matrix(B, p, q);
#endif

    int r, y;

    printf("Введите r: ");
    scanf("%d", &r);

    printf("Введите y: ");
    scanf("%d", &y);

    int **res = multi_multiply(A, B, z, r, y);

    print_matrix(res, z, z);

    free_matrix(A, z);
    free_matrix(B, z);
    free_matrix(res, z);

    return EXIT_SUCCESS;
}
