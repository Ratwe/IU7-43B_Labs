#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define EXPECTED_NUMBER_FROM_LENS_INPUT 2
#define EXPECTED_NUMBER_FROM_NUM_INPUT 1

int enter_lens(size_t *const prows, size_t *const pcolumns);
int fill_matrix(int matrix[][MAX_COLUMNS], const size_t n, const size_t m);
int get_min_num(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
void swap_two_elements(int *const first, int *const second);    
void swap_rows(int (*const matrix)[MAX_COLUMNS], const size_t row_1, const size_t row_2, const size_t m);
void sort_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
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

    check = fill_matrix(matrix, rows, columns);
    if (check != EXIT_SUCCESS)
        return check;
        
    sort_matrix(matrix, rows, columns);

    print_matrix((const int (*)[MAX_COLUMNS])matrix, rows, columns);

    return EXIT_SUCCESS;
}

int enter_lens(size_t *const prows, size_t *const pcolumns)
{
    printf("Enter rows and columns: ");
    if (scanf("%zu%zu", prows, pcolumns) != EXPECTED_NUMBER_FROM_LENS_INPUT)
        return WRONG_INPUT;

    if (*prows > MAX_ROWS || *prows <= 0 || *pcolumns > MAX_COLUMNS || *pcolumns <= 0)
        return OUT_OF_RANGE;

    return RIGHT_INPUT;
}

int fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            int num;
            printf("Enter next_num: ");
            if (scanf("%d", &num) != EXPECTED_NUMBER_FROM_NUM_INPUT)
                return WRONG_INPUT;

            matrix[i][j] = num;
        }
    return RIGHT_INPUT;
}

int get_min_num(const int (*const matrix)[MAX_COLUMNS], const size_t i, const size_t m)
{
    int min = matrix[i][0];
    
    for (size_t j = 0; j < m; j++)
        if (matrix[i][j] < min)
            min = matrix[i][j];
    
    return min;
}

void swap_two_elements(int *const first, int *const second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

void swap_rows(int (*const matrix)[MAX_COLUMNS], const size_t row_1, const size_t row_2, const size_t m)
{
    for (size_t j = 0; j < m; j++)
        swap_two_elements(&matrix[row_1][j], &matrix[row_2][j]);
}

void sort_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    int min_nums[MAX_ROWS];
    
    for (size_t i = 0; i < n; i++)
        min_nums[i] = get_min_num((const int (*)[MAX_COLUMNS])matrix, i, m);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (min_nums[j] < min_nums[j + 1])
            {
                swap_rows(matrix, j, j + 1, m);
                swap_two_elements(&min_nums[j], &min_nums[j + 1]);
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
