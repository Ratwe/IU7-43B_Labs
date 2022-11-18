#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define EXPECTED_NUMBER_FROM_LENS_INPUT 2
#define EXPECTED_NUMBER_FROM_NUM_INPUT 1
#define RADIX 10

int enter_lens(size_t *const prows, size_t *const pcolumns);
int enter_num(int *const pnum);
int fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
int in_num(int num, const int num_flag);
int is_needed_column(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t j, const int num_flag);
void move_elements(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, const size_t col);
size_t delete_columns(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, const int num_flag);
void print_matrix(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);

enum codes
{
    IT_IS_NOT_SEQUENCE,
    IT_IS_SEQUENCE,
    NOT_DELETED_COLUMN = 0,
    DELETED_COLUMN,
    NOT_INCLUDING_NUM_FLAG = 0,
    INCLUDING_NUM_FLAG,
    RIGHT_INPUT = 0,
    WRONG_INPUT = 101,
    OUT_OF_RANGE,
    EMPTY_MATRIX
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

    int num;
    check = enter_num(&num);
    if (check != EXIT_SUCCESS)
        return check;

    columns = delete_columns(matrix, rows, columns, num);
    if (columns == 0)
        return EMPTY_MATRIX;

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

int enter_num(int *const pnum)
{
    printf("Enter num_flag: ");
    if (scanf("%d", pnum) != EXPECTED_NUMBER_FROM_NUM_INPUT)
        return WRONG_INPUT;

    if (*pnum < 0 || *pnum > 9)
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

int in_num(int num, const int num_flag)
{
    if (num == 0 && num_flag == 0)
        return INCLUDING_NUM_FLAG;
        
    while (num > 0)
    {
        if (num % RADIX == num_flag)
            return INCLUDING_NUM_FLAG;
        
        num /= RADIX;
    }
    
    return NOT_INCLUDING_NUM_FLAG;
}

int is_needed_column(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t j, const int num_flag)
{
    for (size_t i = 0; i < n; i++)
        if (in_num(abs(matrix[i][j]), num_flag))
            return DELETED_COLUMN;

    return NOT_DELETED_COLUMN;
}

void move_elements(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, const size_t col)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = col; j < m - 1; j++)
            matrix[i][j] = matrix[i][j + 1];
}

size_t delete_columns(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, const int num_flag)
{
    size_t new_len = m;

    for (size_t j = 0; j < new_len; j++)
        if (is_needed_column((const int (*)[MAX_COLUMNS])matrix, n, j, num_flag))
        {
            move_elements(matrix, n, m, j);
            new_len--;

            j--;
        }

    return new_len;
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
