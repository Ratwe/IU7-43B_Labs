#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define EXPECTED_NUMBER_FROM_LENS_INPUT 2
#define EXPECTED_NUMBER_FOM_INPUT 2

int enter_lens(size_t *const prows, size_t *const pcolumns);
void fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
void print_matrix(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);

enum codes
{
    RIGHT_INPUT,
    WRONG_INPUT = 101,
    OUT_OF_RANGE
};

int main(void)
{
    int matrix[MAX_ROWS][MAX_COLUMNS];

    size_t rows, columns;
    int check = enter_lens(&rows, &columns);
    if (check != EXIT_SUCCESS)
        return check;
    
    fill_matrix(matrix, rows, columns);

    print_matrix((const int (*)[MAX_COLUMNS])matrix, rows, columns);

    return EXIT_SUCCESS;
}

int enter_lens(size_t *const prows, size_t *const pcolumns)
{
    printf("Enter rows and columns: ");
    if (scanf("%zu%zu", prows, pcolumns) != EXPECTED_NUMBER_FROM_LENS_INPUT)
        return WRONG_INPUT;

    if (*prows > MAX_ROWS || *prows <= 0 || *prows != *pcolumns)
        return OUT_OF_RANGE;

    return RIGHT_INPUT;
}

void fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    size_t ibeg = 0, iend = 0, jbeg = 0, jend = 0;
    size_t k = 1;
    size_t i = 0, j = 0;

    while (k <= m * m)
    {
        matrix[i][j] = k;
        
        if (j == jbeg && i < n - iend - 1)
            i++;
        else if (i == n - iend - 1 && j < m - jend - 1)
            j++;
        else if (j == m - jend - 1 && i > ibeg)
            i--;
        else
            j--;

        if ((j == jbeg + 1) && (i == ibeg) && (ibeg != n - iend - 1))
        {
            ibeg++;
            iend++;
            jbeg++;
            jend++;
        }

        k++;
    }
}

void print_matrix(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

